#ifndef SOUNDRINGBUFFER_HPP
#define SOUNDRINGBUFFER_HPP
#include "../Wrappers/MhSoundfileWrapper.hpp"
#include "../Abstract/AudioBuffer.hpp"
#include "../Abstract/AudioPacket.hpp"

namespace Sound {

DEFINE_CLASS(Ringbuffer)
class Ringbuffer
{
private:
	Audio::DynamicBuffer buff;
	Mh::SoundfileWrapper sound;
	std::size_t readPtr, writePtr;
	bool looping;
	Ringbuffer(const Ringbuffer& cpy) = delete; // Copying disabled
	void operator=(const Ringbuffer& cpy) = delete; // Copying disabled
public:
	Ringbuffer(Mh::SoundfileWrapper&& mov, std::size_t buffsize);
	Ringbuffer(Abstract::sFIO fio, std::size_t buffsize);
	Ringbuffer(Ringbuffer&& mov); // Move constructor
	void operator=(Ringbuffer&& mov); // Move assignment

	void setInput(Audio::Input& dst) const;
	void advanceReadPtr(Audio::SampleCount_T reqSamples);
	void checkQueue();
	// Getters
	Audio::Framerate_T getFramerate() const;
	Audio::ChannelCount_T getChannels() const;
	Audio::FrameCount_T getTotalFrames() const;
	bool getLooping() const;
	void setLooping(bool value);
	void seek(Audio::FrameCount_T frame);
};

}
#endif // SOUNDRINGBUFFER_HPP
