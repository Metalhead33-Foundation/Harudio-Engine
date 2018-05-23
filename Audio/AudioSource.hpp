#ifndef AUDIOSOURCE_HPP
#define AUDIOSOURCE_HPP
#include "AudioPlayable.hpp"
#include "AudioBuffer.hpp"
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
	float speed;
	long frameCursor;
	BufferOutput out;
	std::mutex locker;
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	virtual void onBufferRequest() = 0;
public:
	Source();
	virtual int getFramerate() const;
	virtual int getChannelCount() const;
	virtual bool isPlaying() const;
	Status getState() const;
	void play();
	void pause();
	void stop();

	float getSpeed() const;
	void setSpeed(float nSpeed);

	virtual const sBuffer getBuffer() const = 0;
};

}
#endif // AUDIOSOURCE_HPP
