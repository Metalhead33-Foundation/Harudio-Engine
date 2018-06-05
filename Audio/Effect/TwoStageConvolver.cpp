#include "TwoStageConvolver.hpp"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

TwoStageConvolver::TwoStageConvolver(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize)
	: FFT(fftconvolver::sTwoStageFFTConvolver(new fftconvolver::TwoStageFFTConvolver()))
{
	BufferOutput ptr;
	nIR->getAudioData(&ptr,0);
	FFT->init(head_blocksize,tail_blocksize,ptr.first,ptr.second);
}
sTwoStageConvolver TwoStageConvolver::create(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize)
{
	if(nIR) return sTwoStageConvolver(new TwoStageConvolver(nIR,head_blocksize,tail_blocksize));
	else return nullptr;
}
long TwoStageConvolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	const long sampleCount=maxFrames*channelNum;
	FFT->process(inBuffer,outBuffer,sampleCount);
	return maxFrames;
}

}
}
