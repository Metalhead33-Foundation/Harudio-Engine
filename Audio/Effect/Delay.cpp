#include "Delay.hpp"
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

void Delay::reset()
{
	std::vector<float> IR;
	createDelayIR(IR,sampleOffset,delayVolume);
	adapt(IR);
}
Delay::Delay(size_t offset, float delayVolume, int channelId,const sAdaptableConvolver setto)
	: ImpulseResponseGenerator(channelId,setto)
{
	this->sampleOffset = offset;
	this->delayVolume = delayVolume;
	if(setto) reset();
}
size_t Delay::getSampleOffset() const
{
	return sampleOffset;
}
void Delay::setSampleOffset(size_t setto)
{
	if(setto != sampleOffset)
	{
		sampleOffset = setto;
		reset();
	}
}
float Delay::getDelayVolume() const
{
	return delayVolume;
}
void Delay::setDelayVolume(float setto)
{
	if(setto != delayVolume)
	{
		delayVolume = setto;
		reset();
	}
}

sDelay Delay::create(size_t offset, float delayVolume, int channelId,const sAdaptableConvolver setto)
{
	return sDelay(new Delay(offset,delayVolume,channelId,setto));
}

}
}
