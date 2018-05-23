#include "AuxiliaryEffectSlot.hpp"
#include <cstring>

namespace Audio {

AuxiliaryEffectSlot::AuxiliaryEffectSlot(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize)
	: frameRate(intendedFramerate), channelNumber(intendedChannelNumber),
	  frameCount(intendedBufferSize), dryBuffer(intendedBufferSize * intendedChannelNumber),
	  wetBuffer(intendedBufferSize * intendedChannelNumber)
{
	;
}
int AuxiliaryEffectSlot::getFramerate() const
{
	return frameRate;
}
int AuxiliaryEffectSlot::getChannelCount() const
{
	return channelNumber;
}
const sPlayable AuxiliaryEffectSlot::getSource() const
{
	return source;
}
void AuxiliaryEffectSlot::setSource(sPlayable nSource)
{
	source = nSource;
}
void AuxiliaryEffectSlot::processEffects()
{
	memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
	for(auto it = effects.begin(); it != effects.end(); ++it)
	{
		pEffect eff = it->get();
		eff->process(dryBuffer.data(),wetBuffer.data(),frameCount,channelNumber,frameRate);
		memcpy(dryBuffer.data(),wetBuffer.data(),sizeof(float) * dryBuffer.size());
		memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
	}
}
long AuxiliaryEffectSlot::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(channelNum != channelNumber) throw std::runtime_error("Mixer - I/O Channel number mismatch! Please use a panner or channel mixer!");
	if(frameRate != this->frameRate) throw std::runtime_error("Mixer - I/O Framerate mismatch! Please use a samplerate converter!");
	memset(dryBuffer.data(),0,sizeof(float) * dryBuffer.size());
	if(source) source->pullAudio(dryBuffer.data(),maxFrameNum,channelNum,frameRate);
	processEffects();
	long maxFrames = std::min(maxFrameNum,frameCount);
	for(long curFrame = 0; curFrame < maxFrames;++curFrame)
	{
		long frameCursor = curFrame * channelNum;
		for(int i = 0; i < channelNum; ++i) output[frameCursor+i] += dryBuffer[frameCursor+i];
	}
	return maxFrames;
}

}
