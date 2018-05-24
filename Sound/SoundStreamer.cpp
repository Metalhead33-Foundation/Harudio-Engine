#include "SoundStreamer.hpp"

namespace Sound {

Streamer::Streamer(Abstract::sFIO readah, sf_count_t bufferSize)
	: soundfile(Audio::SoundFile::createSoundFile(readah)),
	  buff(Audio::Buffer::create(bufferSize)),frameCursor(0), bufferLoad(0)
{

}
const Audio::sBuffer Streamer::getBuffer() const
{
	return buff;
}
void Streamer::onBufferRequest(long requestedSize)
{
	if(bufferLoad >= buff->getBufferSize())
	{
		buff->bufferData(soundfile,frameCursor,buff->getFrameCount());
		frameCursor += buff->getFrameCount();
		bufferLoad = 0;
	}
	bufferLoad += requestedSize;
}

}
