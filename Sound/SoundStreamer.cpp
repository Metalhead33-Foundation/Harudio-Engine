#include "SoundStreamer.hpp"

namespace Sound {

Streamer::Streamer(Abstract::sFIO readah, sf_count_t bufferSize, sf_count_t bufferCount)
	: soundfile(Audio::SoundFile::createSoundFile(readah)), bufferIndex(0), bufferQueue(bufferCount),
	  buffsize(bufferSize), frameCursor(0)
{
	for(size_t i = 0; i < bufferCount;++i)
	{
		bufferQueue[i].isSpent = false;
		bufferQueue[i].buff = Audio::Buffer::create(bufferSize);
	}
}
void Streamer::onBufferRequest()
{
	for(size_t i = 0; i < bufferQueue.size();++i)
	{
		if(bufferQueue[i].isSpent) bufferQueue[i].isSpent = false;
		Audio::sBuffer tmpBuff = bufferQueue[i].buff;
		tmpBuff->bufferData(soundfile, frameCursor, buffsize / tmpBuff->getChannelNum());
		frameCursor += buffsize / tmpBuff->getChannelNum();
	}
}

}
