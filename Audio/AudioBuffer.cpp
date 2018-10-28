#include "AudioBuffer.hpp"
#include <cstring>

namespace Software {
Buffer::Buffer()
{

}

long Buffer::bufferData(const float* input, size_t frameNum,
						int frameRate, int channelNum, size_t bufferOffset,
						bool forceResize)
{
	if(!input) return 0;
	this->frameRate = frameRate;
	this->channelNum = channelNum;
	if((bufferOffset+(frameNum*channelNum)) < buff.size() || forceResize)
	{
		buff.resize(bufferOffset+(frameNum*channelNum));
	}
	memcpy(&buff[bufferOffset],input,sizeof(float)*frameNum*channelNum);
	return (sizeof(float)*frameNum*channelNum);
}
long Buffer::bufferData(Audio::Importer* import, size_t frameNum,
						int frameRate, int channelNum, size_t bufferOffset,
						bool forceResize)
{
	if(!import) return 0;
	this->frameRate = frameRate;
	this->channelNum = channelNum;
	if((bufferOffset+(frameNum*channelNum)) < buff.size() || forceResize)
	{
		buff.resize(bufferOffset+(frameNum*channelNum));
	}
	import->writeToBuffer(&buff[bufferOffset],sizeof(float)*frameNum*channelNum);
	return (sizeof(float)*frameNum*channelNum);
}

int Buffer::getFrameRate() const
{
	return frameRate;
}
int Buffer::getChannelNum() const
{
	return channelNum;
}
void Buffer::setFrameRate(int frameRate)
{
	this->frameRate = frameRate;
}
size_t Buffer::getFrameCount() const
{
	if(buff.empty()) return 0;
	else return buff.size() / channelNum;
}
size_t Buffer::getSampleCount() const
{
	return buff.size();
}
void Buffer::getAudioData(Audio::BufferOutput* out, size_t index) const
{
	if(out)
	{
		out->first = &buff[index];
		out->second = buff.size() - index;
	}
}

}
