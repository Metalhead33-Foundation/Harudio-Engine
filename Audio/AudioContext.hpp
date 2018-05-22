#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP
#include "Samplerate.hpp"
#include "AudioMixer.hpp"
#include <vector>

namespace Audio {

class Context : public Mixer
{
private:
	PaStream *stream;
protected:
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
public:
	Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize);
	~Context();
	void suspend();
	void unsuspend();
	void abort();
	bool isStopped();
	bool isActive();
};

}

#endif // AUDIOCONTEXT_HPP
