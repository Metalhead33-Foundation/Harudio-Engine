#include "SimpleConvolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <vector>

namespace Audio {
namespace FX {

struct SimpleConvolver_private
{
	const int channelCount;
	virtual ~SimpleConvolver_private() = default;
	SimpleConvolver_private(int channelCnt)
		: channelCount(channelCnt)
	{
		;
	}
	virtual void init(const sBuffer nIR) = 0;
	virtual void init(const float* IR, size_t irSize) = 0;
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

struct NormalSimpleConvolver : public SimpleConvolver_private
{
	std::vector<fftconvolver::FFTConvolver> conv;
	const size_t blockSize;
	NormalSimpleConvolver(size_t blocksize, int channelNum)
		: SimpleConvolver_private(channelNum), blockSize(blocksize), conv(channelNum)
	{
		;
	}
	void init(const sBuffer nIR)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv[0].init(blockSize,ptr.first,ptr.second);
		for(int i = 0; i < channelCount;++i)
		{
			conv[i].init(conv[0]);
		}
	}
	void init(const float* IR, size_t irSize)
	{
		conv[0].init(blockSize,IR,irSize);
		for(int i = 0; i < channelCount;++i)
		{
			conv[i].init(conv[0]);
		}
	}
	void processOneChannel(float* input, float* output, size_t sampleCount, int channelId)
	{
		conv[channelId].process(input,output,sampleCount);
	}
};

struct TwoStageSimpleConvolver : public SimpleConvolver_private
{
	std::vector<fftconvolver::TwoStageFFTConvolver> conv;
	const size_t head, tail;
	TwoStageSimpleConvolver(size_t head, size_t tail, int channelNum)
		: SimpleConvolver_private(channelNum), head(head), tail(tail), conv(channelNum)
	{
		;
	}
	void init(const sBuffer nIR)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv[0].init(head,tail,ptr.first,ptr.second);
		for(int i = 0; i < channelCount;++i)
		{
			conv[i].init(conv[0]);
		}
	}
	void init(const float* IR, size_t irSize)
	{
		conv[0].init(head,tail,IR,irSize);
		for(int i = 0; i < channelCount;++i)
		{
			conv[i].init(conv[0]);
		}
	}
	void processOneChannel(float* input, float* output, size_t sampleCount, int channelId)
	{
		conv[channelId].process(input,output,sampleCount);
	}
};

SimpleConvolver::SimpleConvolver(size_t blocksize, int channelCount)
: impl(new NormalSimpleConvolver(blocksize,channelCount))
{
	;
}
SimpleConvolver::SimpleConvolver(size_t head, size_t tail, int channelCount)
: impl(new TwoStageSimpleConvolver(head,tail,channelCount))
{
	;
}
void SimpleConvolver::reset(size_t blocksize, int channelCount)
{
	impl = uSimpleConvolver_private(new NormalSimpleConvolver(blocksize,channelCount));
}
void SimpleConvolver::reset(size_t head, size_t tail, int channelCount)
{
	impl = uSimpleConvolver_private(new TwoStageSimpleConvolver(head,tail,channelCount));
}
void SimpleConvolver::init(const sBuffer nIR)
{
	impl->init(nIR);
}
void SimpleConvolver::init(const float* IR, size_t irSize)
{
	impl->init(IR,irSize);
}
long SimpleConvolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != impl->channelCount) throw std::runtime_error("Convolver - I/O Channel number mismatch! Please use a panner or channel mixer!");
	return impl->process(inBuffer,outBuffer,maxFrames,channelNum);
}

}
}
