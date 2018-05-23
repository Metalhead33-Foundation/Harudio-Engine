#include "SoundSource.hpp"

namespace Sound {

Source::Source(Audio::sBuffer nBuffer)
	: buff(nBuffer)
{
	;
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
void Source::onBufferRequest()
{
	;
}

}
