#include "SoundBuffer.hpp"
#include <cstring>

namespace Sound {

Buffer::Buffer(Buffer&& mov)
	: buff(std::move(mov.buff)),framerate(mov.framerate),channels(mov.channels),interleavingType(mov.interleavingType), totalFrames(mov.totalFrames)
{
	mov.framerate = 0;
	mov.channels = 0;
	mov.interleavingType = Audio::InterleavingType::DONT_CARE;
	mov.totalFrames = 0;
}
Buffer::Buffer(const Buffer& cpy)
	: buff(cpy.buff),framerate(cpy.framerate),channels(cpy.channels),interleavingType(cpy.interleavingType), totalFrames(cpy.totalFrames)
{

}
void Buffer::operator=(Buffer&& mov)
{
	this->buff = std::move(mov.buff);
	this->framerate = mov.framerate;
	mov.framerate = 0;
	this->channels = mov.channels;
	mov.channels = 0;
	this->interleavingType = mov.interleavingType;
	mov.interleavingType = Audio::InterleavingType::DONT_CARE;
	this->totalFrames = mov.totalFrames;
	mov.totalFrames = 0;
}
void Buffer::operator=(const Buffer& cpy)
{
	this->buff = cpy.buff;
	this->framerate = cpy.framerate;
	this->channels = cpy.channels;
	this->interleavingType = cpy.interleavingType;
	this->totalFrames = cpy.totalFrames;
}

Audio::Framerate_T Buffer::getFramerate() const
{
	return framerate;
}
Audio::ChannelCount_T Buffer::getChannels() const
{
	return channels;
}

Audio::FrameCount_T Buffer::getTotalFrames() const
{
	return totalFrames;
}

Buffer::Buffer(Audio::DynamicBuffer &&mov, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType)
	: buff(mov), framerate(nframerate), channels(nchannelcnt), interleavingType(ninterleavingType)
{
	totalFrames = Audio::FrameCount_T(buff.size() / channels);
}
Buffer::Buffer(const Audio::DynamicBuffer& cpy, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType)
	: buff(cpy), framerate(nframerate), channels(nchannelcnt), interleavingType(ninterleavingType)
{
	totalFrames = Audio::FrameCount_T(buff.size() / channels);
}
Buffer::Buffer(const float* src, Audio::FrameCount_T nframes, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType)
	: buff(nframes * nchannelcnt), framerate(nframerate), channels(nchannelcnt), totalFrames(nframes), interleavingType(ninterleavingType)
{
	memcpy(buff.data(),src,Audio::framesToBytes(nframes,channels));
}

Buffer::Buffer(const Mh::SoundfileWrapper &soundfile)
{
	this->totalFrames = Audio::FrameCount_T(soundfile.getFrameNum());
	this->channels = Audio::ChannelCount_T(soundfile.getChannels());
	this->framerate = Audio::Framerate_T(soundfile.getSamplerate());
	this->interleavingType = Audio::InterleavingType::INTERLEAVED;
	Audio::DynamicBuffer tmpbuff(std::size_t(this->totalFrames * this->channels));
	soundfile.readf(tmpbuff.data(),this->totalFrames);
	this->buff = std::move(tmpbuff);
}
Buffer::Buffer(Abstract::sFIO fio)
{
	Mh::SoundfileWrapper soundfile(fio,true);
	this->totalFrames = Audio::FrameCount_T(soundfile.getFrameNum());
	this->channels = Audio::ChannelCount_T(soundfile.getChannels());
	this->framerate = Audio::Framerate_T(soundfile.getSamplerate());
	this->interleavingType = Audio::InterleavingType::INTERLEAVED;
	Audio::DynamicBuffer tmpbuff(std::size_t(this->totalFrames * this->channels));
	soundfile.readf(tmpbuff.data(),this->totalFrames);
	this->buff = std::move(tmpbuff);
}

void Buffer::setInput(Audio::Input &dst, Audio::FrameCount_T cursor) const
{
	if(cursor >= totalFrames)
	{
		memset(&dst,0,sizeof(Audio::Input));
	} else {
	dst.src = &buff[cursor*channels];
	dst.channelCnt = channels;
	dst.frameRate = framerate;
	dst.frameCnt = totalFrames - cursor;
	dst.interleavingType = interleavingType;
	}
}
}
