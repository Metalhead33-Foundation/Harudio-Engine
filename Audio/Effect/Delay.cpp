#include "Delay.hpp"
#include "Convolver.hpp"
#include "TwoStageConvolver.hpp"
#include <cstring>
namespace Audio {
namespace FX {

struct Delay_private
{
	virtual const sEffect getEffect() const = 0;
	virtual ~Delay_private() = default;
	virtual void resetSelf() = 0;
	int channelCount;
	size_t sampleOffset;
};
struct SimpleDelay : public Delay_private
{
	sConvolver conv;
	size_t blocksize;
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		std::vector<float> tmp(sampleOffset);
		memset(tmp.data(),0,tmp.size()*sizeof(float));
		tmp[tmp.size()-1] = 1.0f;
		conv = Convolver::create(tmp.data(),tmp.size(),blocksize,channelCount);
	}
	SimpleDelay(size_t blocksize, size_t offset, int channelCount)
	{
		this->blocksize = blocksize;
		this->sampleOffset = offset;
		this->channelCount = channelCount;
		resetSelf();
	}
};
struct TwoStageDelay : public Delay_private
{
	sTwoStageConvolver conv;
	size_t head,tail;
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		std::vector<float> tmp(sampleOffset);
		memset(tmp.data(),0,tmp.size()*sizeof(float));
		tmp[tmp.size()-1] = 1.0f;
		conv = TwoStageConvolver::create(tmp.data(),tmp.size(),head,tail,channelCount);
	}
	TwoStageDelay(size_t head, size_t tail, size_t offset, int channelCount)
	{
		this->head = head;
		this->tail = tail;
		this->sampleOffset = offset;
		this->channelCount = channelCount;
		resetSelf();
	}
};

Delay::Delay(size_t blocksize, size_t offset, int channelCount)
	: impl(new SimpleDelay(blocksize,offset,channelCount))
{
	;
}
Delay::Delay(size_t head, size_t tail, size_t offset, int channelCount)
	: impl(new TwoStageDelay(head,tail,offset,channelCount))
{
	;
}
long Delay::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	impl->getEffect()->process(inBuffer,outBuffer,maxFrames,channelNum,frameRate);
}
size_t Delay::getSampleOffset() const
{
	return impl->sampleOffset;
}
void Delay::setSampleOffset(size_t setto)
{
	if(setto != impl->sampleOffset)
	{
		impl->sampleOffset = setto;
		impl->resetSelf();
	}
}
sDelay Delay::create(size_t blocksize, size_t offset, int channelCount)
{
	return sDelay(new Delay(blocksize,offset,channelCount));
}
sDelay Delay::create(size_t head, size_t tail, size_t offset, int channelCount)
{
	return sDelay(new Delay(head,tail,offset,channelCount));
}

}
}
