#include "Convolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

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
sConvolver Convolver::create(const sBuffer nIR, size_t blocksize, int channelCount)
{
	if(nIR) return sConvolver(new Convolver(nIR,blocksize,channelCount));
	else return nullptr;
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
