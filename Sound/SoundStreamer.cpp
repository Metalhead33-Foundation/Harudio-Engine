#include "SoundStreamer.hpp"

namespace Sound {

Streamer::Streamer(Abstract::sFIO readah, int buffNum, size_t bufferSize)
	: soundfile(Audio::SoundFile::createSoundFile(readah)),
	  curBufferCursor(0)
{
	for(int i = 0; i < buffNum;++i)
	{
		queue.push_back(BufferQueueElement(Audio::Buffer::create(bufferSize),true));
	}
	currBufferIndex = queue.begin();
}
void Streamer::checkQueue()
{
	BufferQueueElement* ptr = nullptr;
	do {
		ptr = &(queue.front());
		if(ptr->second)
		{
			Audio::sBuffer tmpbuff = ptr->first;
			queue.pop_front();
			tmpbuff->bufferData(soundfile,frameCursor,tmpbuff->getFrameCount());
			queue.push_back(BufferQueueElement(tmpbuff,false));
		} else break;
	} while(true);
}
const Audio::sBuffer Streamer::getBuffer() const
{
	if(currBufferIndex == queue.end()) return nullptr;
	else return currBufferIndex->first;
}
long Streamer::onBufferRequest(Audio::BufferOutput* ptr, long len)
{
	if(currBufferIndex == queue.end()) return 0;
	if(ptr)
	{
		Audio::sBuffer tmp = currBufferIndex->first;
		if(tmp) {
		tmp->getAudioData(ptr,curBufferCursor * getChannelCount());
		if(len > ptr->second)
		{
			currBufferIndex->second = true;
			++currBufferIndex;
			return ptr->second;
		} return len;
		} else return 0;
	} else return 0;
}
void Streamer::onBufferEnd(bool looping)
{
	frameCursor = 0;
	soundfile->seek(SEEK_SET,0);
	if(!looping)
	{
		state = STOPPED;
	}
}

}
