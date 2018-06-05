#include "TwoStageConvolver.hpp"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

TwoStageConvolver::TwoStageConvolver(const TwoStageConvolver& cpy)
	: convolvers(cpy.convolvers.size())
{
	for(size_t i = 0; i < cpy.convolvers.size();++i)
	{
		convolvers[i] = fftconvolver::sTwoStageFFTConvolver(new fftconvolver::TwoStageFFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
TwoStageConvolver::TwoStageConvolver(const TwoStageConvolver& cpy, int channelCount)
	: convolvers(channelCount)
{
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sTwoStageFFTConvolver(new fftconvolver::TwoStageFFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
TwoStageConvolver::TwoStageConvolver(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize, int channelNum)
	: convolvers(channelNum)
{
	BufferOutput ptr;
	nIR->getAudioData(&ptr,0);
	for(int i = 0; i < channelNum;++i)
	{
		convolvers[i] = fftconvolver::sTwoStageFFTConvolver(new fftconvolver::TwoStageFFTConvolver());
		convolvers[i]->init(head_blocksize,tail_blocksize,ptr.first,ptr.second);
	}
}
TwoStageConvolver::TwoStageConvolver(const float* IR, size_t irLen, size_t head_blocksize, size_t tail_blocksize, int channelNum)
	: convolvers(channelNum)
{
	for(int i = 0; i < channelNum;++i)
	{
		convolvers[i] = fftconvolver::sTwoStageFFTConvolver(new fftconvolver::TwoStageFFTConvolver());
		convolvers[i]->init(head_blocksize,tail_blocksize,IR,irLen);
	}
}
sTwoStageConvolver TwoStageConvolver::create(sTwoStageConvolver cpy)
{
	if(cpy) return sTwoStageConvolver(new TwoStageConvolver(*cpy));
	else return nullptr;
}
sTwoStageConvolver TwoStageConvolver::create(sTwoStageConvolver cpy, int channelCount)
{
	if(cpy) return sTwoStageConvolver(new TwoStageConvolver(*cpy,channelCount));
	else return nullptr;
}
sTwoStageConvolver TwoStageConvolver::create(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize, int channelNum)
{
	if(nIR) return sTwoStageConvolver(new TwoStageConvolver(nIR,head_blocksize,tail_blocksize,channelNum));
	else return nullptr;
}
sTwoStageConvolver TwoStageConvolver::create(const float* IR, size_t irLen, size_t head_blocksize, size_t tail_blocksize, int channelNum)
{
	return sTwoStageConvolver(new TwoStageConvolver(IR,irLen,head_blocksize,tail_blocksize,channelNum));
}
long TwoStageConvolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
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
