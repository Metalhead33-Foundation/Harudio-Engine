#include "AudioSource.hpp"

namespace Audio {

Source::Source()
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
float Source::getSpeed() const
{
	return speed;
}
void Source::setSpeed(float nSpeed)
{
	speed = nSpeed;
}
long Source::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	std::unique_lock<std::mutex> locker(this->locker);
	if(channelNum != getChannelCount()) throw std::runtime_error("Source - I/O Channel number mismatch! Please use a panner or channel mixer!");
	if(frameRate != getFramerate())
	{
		if(getFramerate() > frameRate) maxFrameNum = long(float(maxFrameNum) * (float(getFramerate()) / float(frameRate)));
	}
	getBuffer()->getAudioData(&out,frameCursor);
	long framedFrames = std::min(out.numberOfRemainingFrames,maxFrameNum);
	for(long i = 0; i < framedFrames; ++i)
	{
		output[i] += out.audioData[i];
	}
	frameCursor += framedFrames;
	return framedFrames;
}

}
