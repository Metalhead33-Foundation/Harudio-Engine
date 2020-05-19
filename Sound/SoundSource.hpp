#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "../Abstract/AudioSeekable.hpp"
#include "SoundBuffer.hpp"

namespace Sound {
DEFINE_CLASS(Source)
class Source : public Audio::Seekable
{
private:
	sBuffer buff;
	Audio::FrameCount_T cursor;
	Status state;
	bool looping;
	Source(const Source& cpy) = delete; // No copying
	void operator=(const Source& cpy) = delete; // No copying
public:
	Source();
	Source(Source&& mov);
	void operator=(Source&& mov);
	Source(const sBuffer& nbuff);
	Source(sBuffer&& nbuff);
	Audio::FrameCount_T outputTo(const Audio::Output& dst);
	Status getState() const;
	void play();
	void pause();
	void stop();
	bool isLooping() const;
	void setLooping(bool looping);
	double seek(double seconds, SeekPos whence = SeekPos::SET);
	double tell() const;
	double size() const;
	const sBuffer& getBuff() const;
	void setBuff(const sBuffer &value);
	void setBuff(sBuffer&& value);
};
}

#endif // SOUNDSOURCE_HPP
