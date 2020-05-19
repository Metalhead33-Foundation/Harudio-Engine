#include "SoundStreamer.hpp"

namespace Sound {
Streamer::Streamer(Mh::SoundfileWrapper &&mov, std::size_t buffsize)
	: buff(std::move(mov),buffsize), state(Status::STOPPED)
{

}
Streamer::Streamer(Abstract::sFIO fio, std::size_t buffsize)
	: buff(fio,buffsize), state(Status::STOPPED)
{

}
Streamer::Streamer(Ringbuffer &&mov)
	: buff(std::move(mov)), state(Status::STOPPED)
{

}
Streamer::Streamer(Streamer &&mov)
	: buff(std::move(mov.buff)), state(mov.state)
{
	mov.state = Status::STOPPED;
}
void Streamer::receiveInput(Audio::Input &src) const
{
	buff.setInput(src);
}

void Streamer::outputFeedback(Audio::FrameCount_T frames)
{
	buff.advanceReadPtr(frames*buff.getChannels());
}

void Streamer::operator=(Ringbuffer &&mov)
{
	this->buff = std::move(mov);
}

void Streamer::operator=(Streamer &&mov)
{
	this->buff = std::move(mov.buff);
	this->state = mov.state;
	mov.state = Status::STOPPED;
}

Audio::Provider::Status Streamer::getState() const
{
	return state;
}

void Streamer::play()
{
	if(state == Status::STOPPED)
	{
		buff.seek(0);
	}
	state = Status::PLAYING;
}

void Streamer::pause()
{
	if(state != Status::STOPPED) state = Status::PAUSED;
}

void Streamer::stop()
{
	state = Status::STOPPED;
	buff.seek(0);
}

bool Streamer::isLooping() const
{
	return buff.getLooping();
}

void Streamer::setLooping(bool looping)
{
	buff.setLooping(looping);
}

void Streamer::checkQueue()
{
	buff.checkQueue();
}

}
