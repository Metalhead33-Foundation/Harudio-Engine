#include "AuxiliaryEffectSlot.hpp"
#include <cstring>

namespace Audio {

AuxiliaryEffectSlot::AuxiliaryEffectSlot(int intendedChannelNumber, int intendedFramerate)
	: frameRate(intendedFramerate), channelNumber(intendedChannelNumber),
	  frameCount(TINYBUFF / intendedChannelNumber), source(nullptr)
{
	;
}
sAuxiliaryEffectSlot AuxiliaryEffectSlot::create(int intendedChannelNumber, int intendedFramerate)
{
	return sAuxiliaryEffectSlot(new AuxiliaryEffectSlot(intendedChannelNumber,intendedFramerate));
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
bool AuxiliaryEffectSlot::isPlaying() const
{
	if(source) return source->isPlaying();
	else return false;
}
void AuxiliaryEffectSlot::processEffects(long intendedFrameNum)
{
	memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
	for(auto it = effects.begin(); it != effects.end(); ++it)
	{
		pEffect eff = it->get();
		eff->process(dryBuffer.data(),wetBuffer.data(),intendedFrameNum,channelNumber,frameRate);
		memcpy(dryBuffer.data(),wetBuffer.data(),sizeof(float) * dryBuffer.size());
		memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
	}
}
long AuxiliaryEffectSlot::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(!output) throw std::runtime_error("Invalid output!");
	if(channelNum != channelNumber) throw std::runtime_error("Mixer - I/O Channel number mismatch! Please use a panner or channel mixer!");
	if(frameRate != this->frameRate) throw std::runtime_error("Mixer - I/O Framerate mismatch! Please use a samplerate converter!");
	long processedFrames = 0;
	long readFrames = 0;
	do {
		memset(dryBuffer.data(),0,sizeof(float) * dryBuffer.size());
		readFrames = std::min(long(dryBuffer.size()/channelNum),maxFrameNum-processedFrames);
		if(readFrames) readFrames = source->pullAudio(dryBuffer.data(),readFrames,channelNum,frameRate);
		if(readFrames)
		{
			processEffects(readFrames);
			memcpy(&output[processedFrames],dryBuffer.data(),readFrames * channelNum * sizeof(float));
			processedFrames += readFrames;
		}
	} while(readFrames);
	return processedFrames;
}
void AuxiliaryEffectSlot::addToList(sEffect playable)
{
	effects.push_back(playable);
}
void AuxiliaryEffectSlot::removeFromList(EffectIterator it)
{
	effects.erase(it);
}
void AuxiliaryEffectSlot::removeFromList(sEffect playable)
{
	for(auto it = effects.begin(); it != effects.end(); ++it)
	{
		if(*it == playable)
		{
			effects.erase(it);
			return;
		}
	}
}

}
