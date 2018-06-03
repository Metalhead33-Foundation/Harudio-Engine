#include "SoundStreamer.hpp"

namespace Sound {

Streamer::Streamer(Abstract::sFIO readah, size_t bufferSize)
	: soundfile(Audio::SoundFile::createSoundFile(readah)),
	  writePtr(0), readPtr(0), buff(Audio::Buffer::create(bufferSize))
{
	frameCursor = buff->bufferData(soundfile,0,buff->getSampleCount() / soundfile->channels());
}
sStreamer Streamer::create(Abstract::sFIO readah, size_t bufferSize)
{
	return sStreamer(new Streamer(readah,bufferSize));
}
void Streamer::checkQueue()
{
	if(writePtr == readPtr) return;
	size_t totalSize;
	if(writePtr < readPtr)
	{
		totalSize = readPtr - writePtr;
	}
	else
	{
		totalSize = buff->getSampleCount() - writePtr;
	}
		long readFrames = buff->bufferData(soundfile,frameCursor,totalSize / buff->getChannelNum(),writePtr);
		writePtr += readFrames * buff->getChannelNum();
		frameCursor += readFrames;
	if(writePtr >= buff->getSampleCount()) {
		writePtr = 0;
	}
}
const Audio::sBuffer Streamer::getBuffer() const
{
	return buff;
}
long Streamer::onBufferRequest(Audio::BufferOutput* ptr, long len)
{
	// std::cout << readPtr << " - " << writePtr << std::endl;
	if(ptr)
	{
		buff->getAudioData(ptr,readPtr);
		long givenSamples = std::min(len,ptr->second);
		if(ptr->second - givenSamples <= 0)
		{
			// checkQueue();
			readPtr = 0;
		} else readPtr += givenSamples;
		return givenSamples;
	} else return 0;
}
void Streamer::onBufferEnd(bool looping)
{
	frameCursor = 0;
	soundfile->seek(SEEK_SET,0);
	readPtr = 0;
	writePtr = 0;
	if(!looping)
	{
		state = STOPPED;
	}
}

}
