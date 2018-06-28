#include "SimpleConvolver.hpp"
#include "Convolver.hpp"
#include <vector>

namespace Audio {
namespace FX {

sSimpleConvolver SimpleConvolver::create(size_t blocksize, int channelCount)
{
	return sSimpleConvolver(new SimpleConvolver(blocksize,channelCount));
}
sSimpleConvolver SimpleConvolver::create(size_t head, size_t tail, int channelCount)
{
	return sSimpleConvolver(new SimpleConvolver(head,tail,channelCount));
}

struct SimpleConvolver_private
{
	const int channelCount;
	std::vector<Convolver> conv;
	SimpleConvolver_private(int channelCnt, size_t blocksize)
		: channelCount(channelCnt)
	{
		for(int i = 0; i < channelCnt;++i) conv.push_back(Convolver(blocksize));
	}
	SimpleConvolver_private(int channelCnt, size_t head, size_t tail)
		: channelCount(channelCnt)
	{
		// for(int i = 0; i < channelCnt;++i) conv.emplace_back(head,tail);
		for(int i = 0; i < channelCnt;++i) conv.push_back(Convolver(head,tail));
	}
	void init(const sBuffer nIR)
	{
		conv[0].init(nIR);
		for(int i = 1; i < channelCount;++i) conv[i].init(conv[0]);
	}
	void init(const float* IR, size_t irSize)
	{
		conv[0].init(IR,irSize);
		for(int i = 1; i < channelCount;++i) conv[i].init(conv[0]);
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

SimpleConvolver::SimpleConvolver(size_t blocksize, int channelCount)
: impl(new SimpleConvolver_private(channelCount,blocksize))
{
	;
}
SimpleConvolver::SimpleConvolver(size_t head, size_t tail, int channelCount)
: impl(new SimpleConvolver_private(channelCount,head,tail))
{
	;
}
void SimpleConvolver::reset(size_t blocksize, int channelCount)
{
	impl = uSimpleConvolver_private(new SimpleConvolver_private(blocksize,channelCount));
}
void SimpleConvolver::reset(size_t head, size_t tail, int channelCount)
{
	impl = uSimpleConvolver_private(new SimpleConvolver_private(head,tail,channelCount));
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
void SimpleConvolver::adapt(const std::vector<float>& IR, int channelId)
{
	(void)channelId;
	init(IR.data(),IR.size());
}

}
}
