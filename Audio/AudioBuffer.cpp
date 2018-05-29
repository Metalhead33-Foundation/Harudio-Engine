#include "AudioBuffer.hpp"
#include <cstring>

namespace Audio {

Buffer::Buffer(int frameRate, int channelNum)
{
	this->frameRate = frameRate;
	this->channelNum = channelNum;
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
	return getSampleCount() / size_t(channelNum);
}

Buffer::Buffer(sf_count_t buffsize)
	: frameRate(0),channelNum(0), buff(buffsize)
{
	;
}
Buffer::Buffer(Abstract::sFIO readah)
	: frameRate(0),channelNum(0)
{
	bufferData(readah);
}
Buffer::Buffer(sSoundFile file, sf_count_t offset, sf_count_t frameNum)
	: frameRate(0),channelNum(0)
{
	bufferData(file,offset,frameNum,0,true);
}
Buffer::Buffer(const float* input, size_t frameNum, int frameRate, int channelNum)
	: frameRate(0),channelNum(0)
{
	bufferData(input,frameNum,frameRate,channelNum,0,true);
}

void Buffer::getAudioData(BufferOutput* out, size_t index) const
{
	if(out)
	{
		if(index < buff.size())
		{
			out->first = &buff[index];
			out->second = buff.size() - index;
		}
		else
		{
			out->first = nullptr;
			out->second = 0;
		}
	}
	else
	{
		out->first = nullptr;
		out->second = 0;
	}
}
size_t Buffer::getSampleCount() const
{
	return  buff.size();
}
long Buffer::bufferData(const float* input, size_t frameNum, int frameRate, int channelNum,  size_t bufferOffset, bool forceResize)
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
	this->frameRate = frameRate;
	this->channelNum = channelNum;
	if(forceResize) buff.resize(frameNum*channelNum);
	else if((frameNum * channelNum) > buff.size()) buff.resize(frameNum*channelNum);
	memcpy(&buff[bufferOffset],input,buff.size() * sizeof(float));
	return frameNum;
}
long Buffer::bufferData(const sSoundFile file, sf_count_t offset, sf_count_t frameNum, size_t bufferOffset, bool forceResize)
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
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
		return file->readf(&buff[bufferOffset],readingFrames);
	}
	return 0;
}
long Buffer::bufferData(Abstract::sFIO readah)
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
	sSoundFile sndfile = SoundFile::createSoundFile(readah);
	this->frameRate = sndfile->samplerate();
	this->channelNum = sndfile->channels();
	buff.resize(sndfile->frames() * sndfile->channels());
	return sndfile->readf(buff.data(),sndfile->frames());
}
sBuffer Buffer::create(sf_count_t buffsize)
{
	return sBuffer(new Buffer(buffsize));
}
sBuffer Buffer::create(Abstract::sFIO readah)
{
	return sBuffer(new Buffer(readah));
}
sBuffer Buffer::create(sSoundFile file, sf_count_t offset, sf_count_t frameNum)
{
	return sBuffer(new Buffer(file,offset,frameNum));
}
sBuffer Buffer::create(const float* input, size_t frameNum, int frameRate, int channelNum)
{
	return sBuffer(new Buffer(input,frameNum,frameRate,channelNum));
}

}
