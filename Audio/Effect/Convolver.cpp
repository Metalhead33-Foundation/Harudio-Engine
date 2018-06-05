#include "Convolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

Convolver::Convolver(const Convolver& cpy)
	: convolvers(cpy.convolvers.size())
{
	for(size_t i = 0; i < cpy.convolvers.size();++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
Convolver::Convolver(const Convolver& cpy, int channelCount)
	: convolvers(channelCount)
{
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
Convolver::Convolver(const sBuffer nIR, size_t blocksize, int channelCount)
	: convolvers(channelCount)
{
	BufferOutput ptr;
	nIR->getAudioData(&ptr,0);
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(blocksize,ptr.first,ptr.second);
	}
}
Convolver::Convolver(const float* IR, size_t irSize, size_t blocksize, int channelCount)
	: convolvers(channelCount)
{
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(blocksize,IR,irSize);
	}
}
sConvolver Convolver::create(sConvolver cpy)
{
	if(cpy) return sConvolver(new Convolver(*cpy));
	else return nullptr;
}
sConvolver Convolver::create(sConvolver cpy, int channelCount)
{
	if(cpy) return sConvolver(new Convolver(*cpy,channelCount));
	else return nullptr;
}
sConvolver Convolver::create(const sBuffer nIR, size_t blocksize, int channelCount)
{
	if(nIR) return sConvolver(new Convolver(nIR,blocksize,channelCount));
	else return nullptr;
}
sConvolver  Convolver::create(const float* IR, size_t irSize, size_t blocksize, int channelCount)
{
	return sConvolver(new Convolver(IR,irSize,blocksize,channelCount));
}
long Convolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != convolvers.size()) throw std::runtime_error("Convolver - I/O Channel number mismatch! Please use a panner or channel mixer!");
	for(int i = 0; i < channelNum; ++i)
	{
		long sampleCursor=maxFrames*i;
		convolvers[i]->process(&inBuffer[sampleCursor],&outBuffer[sampleCursor],maxFrames);
	}
	return maxFrames;
}

}
}
