#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include "../Abstract/AudioProvider.hpp"
#include "SoundRingbuffer.hpp"

namespace Sound {
DEFINE_CLASS(Streamer)
class Streamer : public Audio::Provider
{
protected:
	void receiveInput(Audio::Input& src) const; // Gain access to the buffer
	void outputFeedback(Audio::FrameCount_T frames); // Needed for things like advancing the a ringbuffer's pointer
private:
	Ringbuffer buff;
	Status state;
	Streamer(const Streamer& cpy) = delete; // Copying disabled
	void operator=(const Streamer& cpy) = delete; // Copying disabled
public:
	Streamer(Mh::SoundfileWrapper&& mov, std::size_t buffsize);
	Streamer(Abstract::sFIO fio, std::size_t buffsize);
	Streamer(Ringbuffer&& mov);
	Streamer(Streamer&& mov); // Move constructor
	void operator=(Ringbuffer&& mov); // Move assignment
	void operator=(Streamer&& mov); // Move assignment
	Status getState() const;
	void play();
	void pause();
	void stop();
	bool isLooping() const ;
	void setLooping(bool looping);
	void checkQueue();
};
}

#endif // SOUNDSTREAMER_HPP
