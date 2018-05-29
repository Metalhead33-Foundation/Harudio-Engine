#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include "../Audio/AudioSource.hpp"
#include "../Io/SoundFile.hpp"
#include <list>

namespace Sound {

DEFINE_CLASS(Streamer)
class Streamer : public Audio::Source
{
public:
	typedef std::pair<const Audio::sBuffer,bool> BufferQueueElement;
	typedef std::list<BufferQueueElement> BufferQueue;
	typedef BufferQueue::iterator BufferIterator;
private:
	const Audio::sSoundFile soundfile;
	size_t curBufferCursor; // How far are we in the current buffer?
	BufferIterator currBufferIndex; // Which buffer are we using?
	BufferQueue queue;
protected:
	virtual long onBufferRequest(Audio::BufferOutput* ptr, long len);
	virtual void onBufferEnd(bool looping);
public:
	Streamer(Abstract::sFIO readah, int buffNum, size_t bufferSize);
	const Audio::sBuffer getBuffer() const;
	void checkQueue();
};

}
#endif // SOUNDSTREAMER_HPP
