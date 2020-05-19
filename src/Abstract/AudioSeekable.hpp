#ifndef AUDIOSEEKABLE_HPP
#define AUDIOSEEKABLE_HPP
#include "AudioPlayable.hpp"

namespace Audio {

DEFINE_CLASS(Seekable)
class Seekable : public Playable
{
public:
	enum class Status : std::uint8_t {
		PLAYING,
		PAUSED,
		STOPPED
	};
	enum class SeekPos : std::uint8_t {
		SET,
		CUR,
		END
	};

	virtual ~Seekable() = default;
	virtual bool isPlaying() const; // Basically return getState() == Status::PLAYING
	virtual FrameCount_T outputTo(const Output& dst) = 0; // Still needs implementation

	virtual Status getState() const = 0;
	virtual void play() = 0;
	virtual void pause() = 0;
	virtual void stop() = 0;
	virtual bool isLooping() const = 0;
	virtual void setLooping(bool looping) = 0;
	virtual double seek(double seconds, SeekPos whence = SeekPos::SET) = 0;
	virtual double tell() const = 0;
	virtual double size() const = 0;
};
}

#endif // AUDIOSEEKABLE_HPP
