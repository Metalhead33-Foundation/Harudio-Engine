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
long AuxiliaryEffectSlot::getFrameCount() const
{
	return long(dryBuffer.size()) / channelNumber;
}
void AuxiliaryEffectSlot::swapBuffers()
{
	memcpy(dryBuffer.data(),wetBuffer.data(),sizeof(float) * dryBuffer.size());
	memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
}
void AuxiliaryEffectSlot::interlace()
{
	const long frameCnt=getFrameCount();
	for(long curFrame=0;curFrame < frameCnt; ++curFrame)
	{
		for(int sampleOffset=0;sampleOffset<channelNumber;++sampleOffset)
		{
			const long wetFrameStart=(curFrame*channelNumber)+sampleOffset;
			const long dryFrameStart=(frameCnt*sampleOffset)+curFrame;
			wetBuffer[wetFrameStart] = dryBuffer[dryFrameStart];
		}
	}
}
void AuxiliaryEffectSlot::deinterlace()
{
	const long frameCnt=getFrameCount();
	for(long curFrame=0;curFrame < frameCnt; ++curFrame)
	{
		const long dryFrameStart=(curFrame*channelNumber);
		for(int sampleOffset=0;sampleOffset<channelNumber;++sampleOffset)
		{
			const long dryFrameStart=(curFrame*channelNumber)+sampleOffset;
			const long wetFrameStart=(frameCnt*sampleOffset)+curFrame;
			wetBuffer[wetFrameStart] = dryBuffer[dryFrameStart];
		}
	}
}
void AuxiliaryEffectSlot::processEffects(long intendedFrameNum)
{
	memset(wetBuffer.data(),0,sizeof(float) * wetBuffer.size());
	for(auto it = effects.begin(); it != effects.end(); ++it)
	{
		pEffect eff = it->get();
		eff->process(dryBuffer.data(),wetBuffer.data(),intendedFrameNum,channelNumber,frameRate);
		swapBuffers();
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
			if(effects.empty()) {
				memcpy(&output[processedFrames],dryBuffer.data(),readFrames * channelNum * sizeof(float));
			} else {
				deinterlace();
				swapBuffers();
				processEffects(readFrames);
				interlace();
				memcpy(&output[processedFrames],wetBuffer.data(),readFrames * channelNum * sizeof(float));
			}
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
