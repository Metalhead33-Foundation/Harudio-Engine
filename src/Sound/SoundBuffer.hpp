#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP
#include "../Abstract/AudioBuffer.hpp"
#include "../Abstract/AudioPacket.hpp"
#include "Mh/SoundfileWrapper.hpp"

namespace Sound {
DEFINE_CLASS(Buffer)
class Buffer
{
private:
	Audio::DynamicBuffer buff;
	Audio::Framerate_T framerate;
	Audio::ChannelCount_T channels;
	Audio::FrameCount_T totalFrames;
	Audio::InterleavingType interleavingType;
public:
	Buffer(Audio::DynamicBuffer&& mov, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType);
	Buffer(const Audio::DynamicBuffer& cpy, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType);
	Buffer(const float* src, Audio::FrameCount_T nframes, Audio::Framerate_T nframerate, Audio::ChannelCount_T nchannelcnt, Audio::InterleavingType ninterleavingType);
	Buffer(const Mh::SoundfileWrapper& soundfile);
	Buffer(Abstract::sFIO fio);
	// Copy and move constructors + assignments
	Buffer(Buffer&& mov);
	Buffer(const Buffer& cpy);
	void operator=(Buffer&& mov);
	void operator=(const Buffer& cpy);
	// Functions
	void setInput(Audio::Input& dst, Audio::FrameCount_T cursor) const;
	// Getters
	Audio::Framerate_T getFramerate() const;
	Audio::ChannelCount_T getChannels() const;
	Audio::FrameCount_T getTotalFrames() const;
};
}

#endif // SOUNDBUFFER_HPP
