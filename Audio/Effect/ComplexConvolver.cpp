#include "ComplexConvolver.hpp"
#include "Convolver.hpp"
#include <vector>

namespace Audio {
namespace FX {

sComplexConvolver ComplexConvolver::create(size_t blocksize, int channelCount)
{
	return sComplexConvolver(new ComplexConvolver(blocksize,channelCount));
}
sComplexConvolver ComplexConvolver::create(size_t head, size_t tail, int channelCount)
{
	return sComplexConvolver(new ComplexConvolver(head,tail,channelCount));
}

struct ComplexConvolver_private
{
	const int channelCount;
	std::vector<Convolver> conv;
	ComplexConvolver_private(int channelCnt, size_t blocksize)
		: channelCount(channelCnt)
	{
		for(int i = 0; i < channelCnt;++i) conv.emplace_back(blocksize);
	}
	ComplexConvolver_private(int channelCnt, size_t head, size_t tail)
		: channelCount(channelCnt)
	{
		for(int i = 0; i < channelCnt;++i) conv.emplace_back(head,tail);
	}
	void init(const sBuffer nIR, int channelId)
	{
		conv[channelId % channelCount].init(nIR);
	}
	virtual void init(const float* IR, size_t irSize, int channelId)
	{
		conv[channelId % channelCount].init(IR,irSize);
	}
	void processOneChannel(float* input, float* output, size_t sampleCount, int channelId)
	{
		conv[channelId % channelCount].process(input,output,sampleCount);
	}
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

ComplexConvolver::ComplexConvolver(size_t blocksize, int channelCount)
	: impl(new ComplexConvolver_private(blocksize,channelCount))
{
	;
}
ComplexConvolver::ComplexConvolver(size_t head, size_t tail, int channelCount)
	: impl(new ComplexConvolver_private(head,tail,channelCount))
{
	;
}
void ComplexConvolver::reset(size_t blocksize, int channelCount)
{
	impl = uComplexConvolver_private(new ComplexConvolver_private(blocksize,channelCount));
}
void ComplexConvolver::reset(size_t head, size_t tail, int channelCount)
{
	impl = uComplexConvolver_private(new ComplexConvolver_private(head,tail,channelCount));
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
void ComplexConvolver::adapt(const std::vector<float>& IR, int channelId)
{
	init(IR.data(),IR.size(),channelId);
}

}
}
