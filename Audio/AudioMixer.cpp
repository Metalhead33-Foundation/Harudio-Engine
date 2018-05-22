#include "AudioMixer.hpp"
#include <cstring>

namespace Audio {

Mixer::Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize)
	: frameRate(intendedFramerate), channelNumber(intendedChannelNumber),
	  frameCount(intendedBufferSize), buffer(intendedBufferSize * intendedChannelNumber)
{
	;
}
void Mixer::mixDown(bool normalize)
{
	memset(buffer.data(),0,buffer.size() * sizeof(float));
	size_t proc = 0;
	for(auto it = playableList.begin(); it != playableList.end();)
	{
		if(it->expired()) it = playableList.erase(it);
		else
		{
			sPlayable tmp = it->lock();
			if(tmp->isPlaying())
			{
				tmp->pullAudio(buffer.data(),frameCount,channelNumber,frameRate);
				++proc;
			}
			++it;
		}
	}
	if(normalize && proc)
	{
		float fProc = float(proc);
		for(size_t i = 0; i < buffer.size(); ++i)
		{
			buffer[i] /= fProc;
		}
	}
}
long Mixer::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	mixDown();
	long maxFrames = std::min(maxFrameNum,frameCount);
	mixChannels(buffer.data(),output,channelNum,channelNumber,volume,maxFrames);
}
bool Mixer::isPlaying()
{
	return true;
}
int Mixer::getFramerate()
{
	return frameRate;
}
int Mixer::getChannelCount()
{
	return channelNumber;
}

}
