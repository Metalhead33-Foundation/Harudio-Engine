#include "ComplexConvolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <vector>

namespace Audio {
namespace FX {

struct ComplexConvolver_private
{
	const int channelCount;
	virtual ~ComplexConvolver_private() = default;
	ComplexConvolver_private(int channelCnt)
		: channelCount(channelCnt)
	{
		;
	}
	virtual void init(const sBuffer nIR, int channelId) = 0;
	virtual void init(const float* IR, size_t irSize, int channelId) = 0;
	virtual void processOneChannel(float* input, float* output, size_t sampleCount, int channelId) = 0;
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum)
	{
		if(channelNum != channelCount) return 0;
		for(int i = 0; i < channelCount;++i)
		{
			const long sampleOffset=maxFrames*i;
			processOneChannel(&inBuffer[sampleOffset],&outBuffer[sampleOffset],maxFrames,i);
		}
		return maxFrames;
	}
};

struct NormalComplexConvolver : public ComplexConvolver_private
{
	std::vector<fftconvolver::FFTConvolver> conv;
	const size_t blockSize;
	NormalComplexConvolver(size_t blocksize, int channelNum)
		: ComplexConvolver_private(channelNum), blockSize(blocksize), conv(channelNum)
	{
		;
	}
	void init(const sBuffer nIR, int channelId)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv[channelId].init(blockSize,ptr.first,ptr.second);
	}
	void init(const float* IR, size_t irSize, int channelId)
	{
		conv[channelId].init(blockSize,IR,irSize);
	}
	void processOneChannel(float* input, float* output, size_t sampleCount, int channelId)
	{
		conv[channelId].process(input,output,sampleCount);
	}
};

struct TwoStageComplexConvolver : public ComplexConvolver_private
{
	std::vector<fftconvolver::TwoStageFFTConvolver> conv;
	const size_t head, tail;
	TwoStageComplexConvolver(size_t head, size_t tail, int channelNum)
		: ComplexConvolver_private(channelNum), head(head), tail(tail), conv(channelNum)
	{
		;
	}
	void init(const sBuffer nIR, int channelId)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv[channelId].init(head,tail,ptr.first,ptr.second);
	}
	void init(const float* IR, size_t irSize, int channelId)
	{
		conv[channelId].init(head,tail,IR,irSize);
	}
	void processOneChannel(float* input, float* output, size_t sampleCount, int channelId)
	{
		conv[channelId].process(input,output,sampleCount);
	}
};

ComplexConvolver::ComplexConvolver(size_t blocksize, int channelCount)
	: impl(new NormalComplexConvolver(blocksize,channelCount))
{
	;
}
ComplexConvolver::ComplexConvolver(size_t head, size_t tail, int channelCount)
	: impl(new TwoStageComplexConvolver(head,tail,channelCount))
{
	;
}
void ComplexConvolver::reset(size_t blocksize, int channelCount)
{
	impl = uComplexConvolver_private(new NormalComplexConvolver(blocksize,channelCount));
}
void ComplexConvolver::reset(size_t head, size_t tail, int channelCount)
{
	impl = uComplexConvolver_private(new TwoStageComplexConvolver(head,tail,channelCount));
}
void ComplexConvolver::init(const sBuffer nIR, int channelId)
{
	impl->init(nIR,channelId);
}
void ComplexConvolver::init(const float* IR, size_t irSize, int channelId)
{
	impl->init(IR,irSize,channelId);
}
long ComplexConvolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != impl->channelCount) throw std::runtime_error("Convolver - I/O Channel number mismatch! Please use a panner or channel mixer!");
	return impl->process(inBuffer,outBuffer,maxFrames,channelNum);
}

}
}
