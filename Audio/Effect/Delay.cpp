#include "Delay.hpp"
#include "Convolver.hpp"
#include "TwoStageConvolver.hpp"
#include <cstring>
namespace Audio {
namespace FX {

void createDelayIR(std::vector<float>& IR, size_t sampleOffset, float delayVolume=1.0f)
{
	IR.resize(sampleOffset);
	memset(IR.data(),0,IR.size()*sizeof(float));
	IR[0] = 1.0f;
	IR[IR.size()-1] = delayVolume;
	/*for(int i = 0; i < 4; ++i)
	{
		IR.push_back(IR[IR.size()-1]*0.5f);
	}*/
}

struct Delay_private
{
	virtual const sEffect getEffect() const = 0;
	virtual ~Delay_private() = default;
	virtual void resetSelf() = 0;
	int channelCount;
	size_t sampleOffset;
	float delayVolume;
};
struct SimpleDelay : public Delay_private
{
	sConvolver conv;
	size_t blocksize;
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		std::vector<float> tmp;
		createDelayIR(tmp,sampleOffset,delayVolume);
		conv = Convolver::create(tmp.data(),tmp.size(),blocksize,channelCount);
	}
	SimpleDelay(size_t blocksize, size_t offset,float delayVolume, int channelCount)
	{
		this->blocksize = blocksize;
		this->sampleOffset = offset;
		this->delayVolume = delayVolume;
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
		std::vector<float> tmp;
		createDelayIR(tmp,sampleOffset,delayVolume);
		conv = TwoStageConvolver::create(tmp.data(),tmp.size(),head,tail,channelCount);
	}
	TwoStageDelay(size_t head, size_t tail, size_t offset, float delayVolume, int channelCount)
	{
		this->head = head;
		this->tail = tail;
		this->sampleOffset = offset;
		this->delayVolume = delayVolume;
		this->channelCount = channelCount;
		resetSelf();
	}
};

Delay::Delay(size_t blocksize, size_t offset,float delayVolume, int channelCount)
	: impl(new SimpleDelay(blocksize,offset,delayVolume,channelCount))
{
	;
}
Delay::Delay(size_t head, size_t tail, size_t offset,float delayVolume, int channelCount)
	: impl(new TwoStageDelay(head,tail,offset,delayVolume,channelCount))
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
float Delay::getDelayVolume() const
{
	return impl->delayVolume;
}
void Delay::setDelayVolume(float setto)
{
	if(setto != impl->delayVolume)
	{
		impl->delayVolume = setto;
		impl->resetSelf();
	}
}

sDelay Delay::create(size_t blocksize, size_t offset, float delayVolume, int channelCount)
{
	return sDelay(new Delay(blocksize,offset,delayVolume,channelCount));
}
sDelay Delay::create(size_t head, size_t tail, size_t offset, float delayVolume, int channelCount)
{
	return sDelay(new Delay(head,tail,offset,delayVolume,channelCount));
}

}
}
