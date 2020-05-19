#ifndef AUDIOPROVIDER_HPP
#define AUDIOPROVIDER_HPP
#include "AudioPlayable.hpp"

namespace Audio {

DEFINE_CLASS(Provider)
class Provider : public Playable
{
protected:
	enum Status : std::uint8_t {
		PLAYING,
		PAUSED,
		STOPPED
		};
protected:
	virtual void receiveInput(Input& src) const = 0; // Gain access to the buffer
	virtual void outputFeedback(FrameCount_T frames) = 0; // Needed for things like advancing the a ringbuffer's pointer
public:
	virtual ~Provider() = default;
	virtual bool isPlaying() const; // Is this thing even on?
	FrameCount_T outputTo(const Output& dst); // Return value: frames transmitted

	virtual Status getState() const = 0;
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;
	virtual bool isLooping() const = 0;
	virtual void setLooping(bool looping) = 0;
};
}

#endif // AUDIOPROVIDER_HPP
