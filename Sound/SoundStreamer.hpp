#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include "../Audio/AudioSource.hpp"
#include <vector>

namespace Sound {

DEFINE_CLASS(Streamer)
class Streamer : public Audio::Source
{
private:
	const Audio::sBuffer buff;
	const Audio::sSoundFile soundfile;
	sf_count_t frameCursor;
	size_t bufferLoad;
protected:
	virtual void onBufferRequest(long requestedSize);
public:
	Streamer(Abstract::sFIO readah, sf_count_t bufferSize);
	const Audio::sBuffer getBuffer() const;
};

}
#endif // SOUNDSTREAMER_HPP
