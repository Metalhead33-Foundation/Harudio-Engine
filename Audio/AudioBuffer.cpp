#include "AudioBuffer.hpp"
#include <cstring>

namespace Audio {

Buffer::Buffer()
	: buff(0), frameRate(0), channelNum(0)
{
	;
}
Buffer::Buffer(Abstract::sFIO readah)
{
	bufferData(readah);
}
Buffer::Buffer(sSoundFile file, sf_count_t offset, sf_count_t frameNum)
{
	bufferData(file,offset,frameNum,true);
}
Buffer::Buffer(const float* input, size_t frameNum, int frameRate, int channelNum)
{
	bufferData(input,frameNum,frameRate,channelNum);
}

void Buffer::getAudioData(BufferOutput* out, size_t index) const
{
	if(out)
	{
		if(index < buff.size())
		{
			out->audioData = &buff[index];
			out->numberOfRemainingFrames = buff.size() - index;
		}
		else
		{
			out->audioData = nullptr;
			out->numberOfRemainingFrames = 0;
		}
	}
	else
	{
		out->audioData = nullptr;
		out->numberOfRemainingFrames = 0;
	}
}
int Buffer::getFrameRate() const
{
	return frameRate;
}
int Buffer::getChannelNum() const
{
	return channelNum;
}
size_t Buffer::getFrameCount() const
{
	return buff.size() / channelNum;
}
size_t Buffer::getBufferSize() const
{
	return  buff.size();
}
void Buffer::bufferData(const float* input, size_t frameNum, int frameRate, int channelNum)
{
	std::unique_lock<std::mutex> locker(this->locker);
	this->frameRate = frameRate;
	this->channelNum = channelNum;
	buff.resize(frameNum*channelNum);
	memcpy(buff.data(),input,buff.size() * sizeof(float));
}
void Buffer::bufferData(sSoundFile file, sf_count_t offset, sf_count_t frameNum, bool forceResize)
{
	std::unique_lock<std::mutex> locker(this->locker);
	if(file)
	{
		sf_count_t readingFrames = file->frames();
		if(offset)
		{
			file->seek(offset,SEEK_SET);
			readingFrames -= offset;
		}
		if(frameNum)
		{
			readingFrames = std::min(readingFrames,frameNum);
		}
		this->frameRate = file->samplerate();
		this->channelNum = file->channels();
		if(forceResize) buff.resize(readingFrames * file->channels());
		else if(readingFrames > (buff.size() / file->channels())) buff.resize(readingFrames * file->channels());
		file->readf(buff.data(),readingFrames);
	}
}
void Buffer::bufferData(Abstract::sFIO readah)
{
	std::unique_lock<std::mutex> locker(this->locker);
	sSoundFile sndfile = SoundFile::createSoundFile(readah);
	this->frameRate = sndfile->samplerate();
	this->channelNum = sndfile->channels();
	buff.resize(sndfile->frames() * sndfile->channels());
	sndfile->readf(buff.data(),sndfile->frames());

}

}
