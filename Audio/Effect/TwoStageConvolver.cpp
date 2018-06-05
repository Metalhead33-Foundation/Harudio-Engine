#include "TwoStageConvolver.hpp"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

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
sTwoStageConvolver TwoStageConvolver::create(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize, int channelNum)
{
	if(nIR) return sTwoStageConvolver(new TwoStageConvolver(nIR,head_blocksize,tail_blocksize,channelNum));
	else return nullptr;
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
