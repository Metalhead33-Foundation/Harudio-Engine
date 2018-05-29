#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include "../Audio/AudioSource.hpp"
#include "../Io/SoundFile.hpp"
#include <list>

namespace Sound {

DEFINE_CLASS(Streamer)
class Streamer : public Audio::Source
{
private:
	const Audio::sSoundFile soundfile;
	const Audio::sBuffer buff;
	size_t readPtr, writePtr;
protected:
	virtual long onBufferRequest(Audio::BufferOutput* ptr, long len);
	virtual void onBufferEnd(bool looping);
public:
	Streamer(Abstract::sFIO readah, size_t bufferSize);
	const Audio::sBuffer getBuffer() const;
	void checkQueue();
};

}
#endif // SOUNDSTREAMER_HPP
