#include "AudioSource.hpp"

namespace Audio {

Source::Source()
	: frameCursor(0), state(STOPPED)
{

}
int Source::getFramerate() const
{
	if(getBuffer()) return getBuffer()->getFrameRate();
	else return 0;
}
int Source::getChannelCount() const
{
	if(getBuffer()) return getBuffer()->getChannelNum();
	else return 0;
}
bool Source::isPlaying() const
{
	return state == PLAYING;
}
Source::Status Source::getState() const
{
	return state;
}
bool Source::isLooping() const
{
	return looping;
}
void Source::setLooping(bool looping)
{
	this->looping = looping;
}
void Source::play()
{
	std::unique_lock<std::mutex> locker(this->locker);
	if(state != PAUSED) frameCursor = 0;
	if(getBuffer()) state = PLAYING;
}
void Source::pause()
{
	std::unique_lock<std::mutex> locker(this->locker);
	state = PAUSED;
}
void Source::stop()
{
	std::unique_lock<std::mutex> locker(this->locker);
	state = STOPPED;
	frameCursor = 0;
}
long Source::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	std::unique_lock<std::mutex> locker(this->locker);
	if(channelNum != getChannelCount()) throw std::runtime_error("Source - I/O Channel number mismatch! Please use a panner or channel mixer!");
	BufferOutput ptr;
	bool isOver = false;
	long framedSamples = 0;
	long samplesToRead = maxFrameNum * channelNum;
	while(samplesToRead) {
		long readSamples = onBufferRequest(&ptr, samplesToRead);
		samplesToRead -= readSamples;
		for(long i = 0; i < readSamples; ++i,++framedSamples)
		{
			output[framedSamples] += out.first[i];
		}
		if(!readSamples)
		{
			isOver = true;
			break;
		}
	}
	if(isOver) onBufferEnd(looping);
	return framedSamples / channelNum;
}

}
