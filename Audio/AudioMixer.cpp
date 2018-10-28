#include "AudioMixer.hpp"
#include <cstring>
#include <stdexcept>

namespace Software {

Mixer::Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize)
	:  channelNumber(intendedChannelNumber), frameRate(intendedFramerate),bufferSize(intendedBufferSize),
	  inputBuffer(intendedBufferSize*intendedChannelNumber), outputBuffer(intendedBufferSize*intendedChannelNumber)
{
	;
}
bool Mixer::isPlaying() const
{
	if(playableList.empty()) return  false;
	else {
		for(auto it = playableList.begin();it != playableList.end();++it)
		{
			if(it->first->isPlaying()) return true;
		}
		return false;
	}
}
int Mixer::getFramerate() const
{
	return frameRate;
}
int Mixer::getChannelCount() const
{
	return channelNumber;
}
long Mixer::mixDown(long maxFrameNum)
{
	if(playableList.empty()) return 0;
	long receivedFrames = 0;
	memset(outputBuffer.data(),0,outputBuffer.size() * sizeof(float));
	for(auto it = playableList.begin(); it != playableList.end();++it )
	{
		memset(inputBuffer.data(),0,inputBuffer.size() * sizeof(float));
		const long localFrameNum = it->first->pullAudio(inputBuffer.data(),
														std::min(maxFrameNum,bufferSize),
														channelNumber,frameRate);
		receivedFrames = std::max(receivedFrames,localFrameNum);
		for(long i = 0; i< localFrameNum;++i)
		{
			for(int j = 0; j < channelNumber; ++j)
			{
				outputBuffer[i+j] = std::min(outputBuffer[i+j] + inputBuffer[i+j] * it->second,1.0f);
			}
		}
	}
	return receivedFrames;
}
long Mixer::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(channelNum != this->channelNumber) throw std::runtime_error("Mixer - Channel number mismatch! Please use a panner!");
	if(frameRate != this->frameRate) throw std::runtime_error("Mixer - Samplerate mismatch! Please use a resampler!");
	long framesRemaining = maxFrameNum;
	long receivedTotalFrames = 0;
	while(framesRemaining) {
		const long currentPtr = maxFrameNum - framesRemaining;
		const long receivedFrames = mixDown(framesRemaining);
		framesRemaining -= receivedFrames;
		receivedTotalFrames += receivedFrames;
		if(!receivedFrames) break;
		memcpy(&output[currentPtr*channelNum],outputBuffer.data(),receivedFrames*channelNum*sizeof(float));
	}
	return receivedTotalFrames;
}
void Mixer::addToList(Audio::sPlayable playable,float volume)
{
	playableList.insert(std::make_pair(playable,volume));
}
void Mixer::removeFromList(Audio::sPlayable playable)
{
	auto it = playableList.find(playable);
	if(it != playableList.end()) playableList.erase(it);
}
float Mixer::getVolume(Audio::sPlayable playable) const
{
	auto it = playableList.find(playable);
	if(it == playableList.end()) return 0.0f;
	else return it->second;
}
bool Mixer::empty() const
{
	return playableList.empty();
}

}
