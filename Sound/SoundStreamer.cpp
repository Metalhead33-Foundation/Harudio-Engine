#include "SoundStreamer.hpp"

namespace Sound {

Streamer::Streamer(Abstract::sFIO readah, int buffNum, size_t bufferSize)
	: soundfile(Audio::SoundFile::createSoundFile(readah)),
	  curBufferCursor(0)
{
	for(int i = 0; i < buffNum;++i)
	{
		queue.emplace_back(Audio::Buffer::create(bufferSize),true);
	}
	mWrite = queue.begin();
	mRead = queue.begin();
}
void Streamer::checkQueue()
{
	while(mWrite->second) {
		Audio::sBuffer tmpbuff = mWrite->first;
		tmpbuff->bufferData(soundfile,frameCursor,tmpbuff->getFrameCount());
		mWrite->second = false;

		++mWrite;

		if(mWrite == queue.end()) {
			mWrite = queue.begin();
		}
	};
}
const Audio::sBuffer Streamer::getBuffer() const
{
	if(mRead == queue.end()) return nullptr;
	else return mRead->first;
}
long Streamer::onBufferRequest(Audio::BufferOutput* ptr, long len)
{
	if(!mRead->second) {
		Audio::sBuffer tmp = mRead->first;
		if(tmp) {
			tmp->getAudioData(ptr,curBufferCursor * getChannelCount());
			if(len > mRead->second)
			{
				mRead->second = true;
				++mRead;

				if(mRead == queue.end()) {
					mRead = queue.begin();
				}
				return mRead->second;
			} return len;
		} else return 0;
	}else return 0;
}
void Streamer::onBufferEnd(bool looping)
{
	frameCursor = 0;
	soundfile->seek(SEEK_SET,0);
	mWrite = queue.begin();
	mRead = queue.begin();
	if(!looping)
	{
		state = STOPPED;
	}
}

}
