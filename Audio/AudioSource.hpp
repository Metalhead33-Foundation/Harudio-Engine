#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP
#include "AudioPlayable.hpp"
#include "AudioBuffer.hpp"
#include <mutex>

namespace Audio {

DEFINE_CLASS(Source)
class Source : public Playable
{
public:
	enum Status : uint8_t {
		PLAYING,
		PAUSED,
		STOPPED
	};
protected:
	Status state;
	long frameCursor;
	BufferOutput out;
	std::mutex locker;
	bool looping;
	virtual long onBufferRequest(BufferOutput* ptr, long len) = 0;
	virtual void onBufferEnd(bool looping) = 0;
public:
	Source();
	virtual int getFramerate() const;
	virtual int getChannelCount() const;
	virtual bool isPlaying() const;
	Status getState() const;
	void play();
	void pause();
	void stop();
	bool isLooping() const;
	void setLooping(bool looping);

	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);

	virtual const sBuffer getBuffer() const = 0;
};

}
#endif // AUDIOSOURCE_HPP
