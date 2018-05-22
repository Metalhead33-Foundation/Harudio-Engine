#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP
#include "Samplerate.hpp"
#include "AudioPlayable.hpp"
#include <vector>

namespace Audio {

class Context : public Playable
{
private:
	PaStream *stream;
	Samplerate samplerateConverter;
	SRC_DATA samplerateConversionData;
	std::vector<float> mixingBuffer;
	void mixDown();
protected:
	virtual long pullAudio(float* output, long maxFrameNum, long channelNum);
public:
	const int framerate;
	const int numChannels;
	Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize, int conversionQuality);
	~Context();
	void suspend();
	void unsuspend();
	void abort();
	bool isStopped();
	bool isActive();
	virtual bool isPlaying() = 0;
	virtual int getChannelNumber() = 0;
};

}

#endif // AUDIOCONTEXT_HPP
