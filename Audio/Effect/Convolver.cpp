#include "Convolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include <cstring>
namespace Audio {
namespace FX {

Convolver::Convolver(const sBuffer nIR, size_t blocksize)
	: FFT(fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver()))
{
	BufferOutput ptr;
	nIR->getAudioData(&ptr,0);
	FFT->init(blocksize,ptr.first,ptr.second);
}
sConvolver Convolver::create(const sBuffer nIR, size_t blocksize)
{
	if(nIR) return sConvolver(new Convolver(nIR,blocksize));
	else return nullptr;
}
long Convolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	const long sampleCount=maxFrames*channelNum;
	FFT->process(inBuffer,outBuffer,sampleCount);
	return maxFrames;
}

}
}
