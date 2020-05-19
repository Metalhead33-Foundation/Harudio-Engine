#include "SoundRingbuffer.hpp"

namespace Sound {
bool Ringbuffer::getLooping() const
{
	return looping;
}

void Ringbuffer::setLooping(bool value)
{
	looping = value;
}

Ringbuffer::Ringbuffer(Mh::SoundfileWrapper &&mov, std::size_t buffsize)
	: buff(buffsize), sound(std::move(mov)), readPtr(0), writePtr(0), looping(false)
{
	//this->totalFrames = Audio::FrameCount_T(buffsize/sound.getChannels());
}
Ringbuffer::Ringbuffer(Abstract::sFIO fio, std::size_t buffsize)
	: buff(buffsize), sound(fio,true), readPtr(0), writePtr(0), looping(false)
{
	//this->totalFrames = Audio::FrameCount_T(buffsize/sound.getChannels());
}
Ringbuffer::Ringbuffer(Ringbuffer&& mov)
	: buff(std::move(mov.buff)), sound(std::move(mov.sound)), readPtr(mov.readPtr), writePtr(mov.writePtr), looping(mov.looping)
{
	mov.readPtr = 0;
	mov.writePtr = 0;
}
void Ringbuffer::operator=(Ringbuffer&& mov)
{
	this->buff = std::move(mov.buff);
	this->sound = std::move(mov.sound);
	this->readPtr = mov.readPtr;
	this->writePtr = mov.writePtr;
	this->looping = mov.looping;
	mov.readPtr = 0;
	mov.writePtr = 0;
}

void Ringbuffer::setInput(Audio::Input &dst) const
{
	dst.src = &buff[readPtr];
	dst.frameRate = Audio::Framerate_T(sound.getSamplerate());
	dst.channelCnt = Audio::ChannelCount_T(sound.getChannels());
	dst.interleavingType = Audio::InterleavingType::INTERLEAVED;
	if(readPtr < writePtr)
	{
		dst.frameCnt = Audio::FrameCount_T((writePtr - readPtr)/dst.channelCnt);
	} else {
		dst.frameCnt = Audio::FrameCount_T((buff.size() - readPtr)/dst.channelCnt);
	}
}

void Ringbuffer::advanceReadPtr(Audio::SampleCount_T reqSamples)
{
	readPtr += reqSamples;
	/*if(readPtr < writePtr)
	{
		readPtr = std::min(writePtr,readPtr + reqSamples);
	} else {
		readPtr = std::min(buff.size(),readPtr + reqSamples);
	}
	if(readPtr += buff.size()) readPtr = 0;*/
}

void Ringbuffer::checkQueue()
{
	while(writePtr != readPtr)
	{
		std::size_t totalSize;
		if(writePtr < readPtr) // Write ptr is behind read ptr
		{
			totalSize = readPtr - writePtr;  // We can only read readPtr - writePtr
		}
		else // Write ptr is in front of read ptr
		{
			totalSize = buff.size() - writePtr; // We can read till the end of buffer
		}
		const long readSamples = sound.read(&buff[writePtr],long(totalSize));
		if(!readSamples) {
				if(looping) sound.seekCur(0);
				return;
		}
		writePtr += std::size_t(readSamples); // Advance the write ptr
		if(writePtr >= buff.size()) {
			writePtr = 0;
		}
	}
}

Audio::Framerate_T Ringbuffer::getFramerate() const
{
	return Audio::Framerate_T(sound.getSamplerate());
}

Audio::ChannelCount_T Ringbuffer::getChannels() const
{
	return Audio::ChannelCount_T(sound.getChannels());
}

Audio::FrameCount_T Ringbuffer::getTotalFrames() const
{
	return Audio::FrameCount_T(sound.getFrameNum());
}


}
