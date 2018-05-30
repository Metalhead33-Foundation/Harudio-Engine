#include "SoundSource.hpp"

namespace Sound {

Source::Source(Audio::sBuffer nBuffer)
	: buff(nBuffer)
{
	;
}
sSource Source::create(Audio::sBuffer nBuffer)
{
	return sSource(new Source(nBuffer));
}
const Audio::sBuffer Source::getBuffer() const
{
	return buff;
}
void Source::setBuffer(Audio::sBuffer nBuffer)
{
	std::unique_lock<std::mutex> locker(this->locker);
	buff = nBuffer;
}
long Source::onBufferRequest(Audio::BufferOutput* ptr, long len)
{
	if(buff)
	{
		if(ptr)
		{
			buff->getAudioData(ptr,frameCursor * getChannelCount());
			return std::min(len,ptr->second);
		} else return 0;
	} else return 0;
}
void Source::onBufferEnd(bool looping)
{
	frameCursor = 0;
	if(!looping)
	{
		state = STOPPED;
	}
}

}
