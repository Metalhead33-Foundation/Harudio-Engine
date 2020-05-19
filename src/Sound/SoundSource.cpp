#include "SoundSource.hpp"
#include "../Abstract/AudioMismatchError.hpp"
#include <cstring>
#include <algorithm>

namespace Sound {
const sBuffer &Source::getBuff() const
{
	return buff;
}

void Source::setBuff(const sBuffer &value)
{
	buff = value;
}
void Source::setBuff(sBuffer&& value)
{
	buff = std::move(value);
}

Source::Source()
	: buff(nullptr), cursor(0)
{

}

Source::Source(Source &&mov)
	: buff(std::move(mov.buff)), cursor(0)
{

}

void Source::operator=(Source &&mov)
{
	buff = std::move(mov.buff);
}

Source::Source(const sBuffer &nbuff)
	: buff(nbuff), cursor(0)
{

}

Source::Source(sBuffer &&nbuff)
	: buff(std::move(nbuff)), cursor(0)
{

}

Audio::FrameCount_T Source::outputTo(const Audio::Output &dst)
{
	if(!buff) return 0;
	if(state != Status::PLAYING) return 0;
	Audio::Input in;
	buff->setInput(in,cursor);
	if(in.src) { // Input is valid
	if( (dst.frameRate != in.frameRate) ||
			(dst.channelCnt != in.channelCnt) ||
			( dst.interleavingType != Audio::InterleavingType::DONT_CARE && (dst.interleavingType != in.interleavingType)))
	{
		throw Audio::MismatchError(dst.frameRate,in.frameRate,dst.channelCnt,in.channelCnt,dst.interleavingType,in.interleavingType);
	}
	const Audio::FrameCount_T framesToGo = std::min(in.frameCnt,dst.frameCnt);
	std::memcpy(dst.dst,in.src,Audio::framesToBytes(framesToGo,dst.channelCnt));
	cursor += framesToGo;
	if(cursor >= buff->getFrameCount())
	{
		if(!looping) state = Status::STOPPED;
		cursor = 0;
	}
	return framesToGo;
	} else return 0; // Input is invalid
}

Source::Status Source::getState() const
{
	return state;
}

void Source::play()
{
	if(state == Status::STOPPED)
	{
		cursor = 0;
	}
	state = Status::PLAYING;
}

void Source::pause()
{
	if(state != Status::STOPPED) state = Status::PAUSED;
}

void Source::stop()
{
	state = Status::STOPPED;
	cursor = 0;
}

bool Source::isLooping() const
{
	return looping;
}

void Source::setLooping(bool looping)
{
	this->looping = looping;
}

double Source::seek(double seconds, SeekPos whence)
{
	if(!buff) return 0.0;
	Audio::FrameCount_T nframe;
	switch (whence) {
	case SeekPos::SET:
		nframe = Audio::FrameCount_T(seconds*double(buff->getFramerate()));
		break;
	case SeekPos::CUR:
		nframe = cursor + Audio::FrameCount_T(seconds*double(buff->getFramerate()));
		break;
	case SeekPos::END:
		nframe = buff->getFrameCount() - Audio::FrameCount_T(seconds*double(buff->getFramerate()));
		break;
	}
	return double(nframe)/double(buff->getFramerate());
}

double Source::tell() const
{
	if(!buff) return 0.0;
	return double(cursor)/double(buff->getFramerate());
}

double Source::size() const
{
	if(!buff) return 0.0;
	return double(buff->getFrameCount())/double(buff->getFramerate());
}

}
