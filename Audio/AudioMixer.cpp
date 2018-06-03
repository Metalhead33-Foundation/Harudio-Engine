#include "AudioMixer.hpp"
#include <cstring>
#include <stdexcept>

namespace Audio {

Mixer::Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize)
	: frameRate(intendedFramerate), channelNumber(intendedChannelNumber),
	  frameCount(intendedBufferSize), inputBuffer(intendedBufferSize * intendedChannelNumber),
	  outputBuffer(intendedBufferSize * intendedChannelNumber)
{
	;
}
void Mixer::mixDown(bool normalize)
{
	memset(outputBuffer.data(),0,outputBuffer.size() * sizeof(float));
	// std::cout << playableList.size() << std::endl;
	size_t proc = 0;
	for(auto it = playableList.begin(); it != playableList.end();)
	{
		if(it->expired()) it = playableList.erase(it);
		else
		{
			sPlayable tmp = it->lock();
			if(tmp->isPlaying())
			{
				memset(inputBuffer.data(),0,inputBuffer.size() * sizeof(float));
				tmp->pullAudio(inputBuffer.data(),frameCount,channelNumber,frameRate);
				for(size_t i = 0; i < inputBuffer.size(); ++i)
				{
					outputBuffer[i] += inputBuffer[i];
				}
				++proc;
			}
			++it;
		}
	}
	if(normalize && proc)
	{
		float fProc = float(proc);
		for(size_t i = 0; i < outputBuffer.size(); ++i)
		{
			outputBuffer[i] /= fProc;
		}
	}
}
long Mixer::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(!output) throw std::runtime_error("Invalid output!");
	mixDown();
	long maxFrames = std::min(maxFrameNum,frameCount);
	if(channelNum != channelNumber) throw std::runtime_error("Mixer - I/O Channel number mismatch! Please use a panner or channel mixer!");
	if(frameRate != this->frameRate) throw std::runtime_error("Mixer - I/O Framerate mismatch! Please use a samplerate converter!");
	memcpy(output,outputBuffer.data(),std::min(frameCount,maxFrameNum) * channelNum * sizeof(float));
	return maxFrames;
}
bool Mixer::isPlaying() const
{
	return true;
}
int Mixer::getFramerate() const
{
	return frameRate;
}
int Mixer::getChannelCount() const
{
	return channelNumber;
}
void Mixer::addToList(sPlayable playable)
{
	playableList.push_back(playable);
}
void Mixer::removeFromList(PlayableIterator it)
{
	playableList.erase(it);
}
void Mixer::removeFromList(sPlayable playable)
{
	for(auto it = playableList.begin(); it != playableList.end(); ++it)
	{
		if(!it->expired())
		{
			auto tmp = it->lock();
			if(tmp == playable)
			{
				playableList.erase(it);
				return;
			}
		}
	}
}

}
