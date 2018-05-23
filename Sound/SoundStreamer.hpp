#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include "../Audio/AudioSource.hpp"
#include <vector>

namespace Sound {

DEFINE_CLASS(Streamer)
class Streamer : public Audio::Source
{
public:
	struct BufferQueueElement {
		Audio::sBuffer buff;
		bool isSpent;
	};
private:
	std::vector<BufferQueueElement> bufferQueue;
	const Audio::sSoundFile soundfile;
	const sf_count_t buffsize;
	int bufferIndex;
	sf_count_t frameCursor;
protected:
	virtual void onBufferRequest();
public:
	Streamer(Abstract::sFIO readah, sf_count_t bufferSize, sf_count_t bufferCount);
	const Audio::sBuffer getBuffer() const;
};

}
#endif // SOUNDSTREAMER_HPP
