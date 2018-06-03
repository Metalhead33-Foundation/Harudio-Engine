#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP
#include "Samplerate.hpp"
#include "AudioMixer.hpp"
#include <vector>
#include <mutex>

namespace Audio {

class Context : public Mixer
{
private:
	PaStream *stream;
	static int numContexts;
	static std::recursive_mutex locker;
	static void queryDevices(PaStreamParameters* inputParams, PaStreamParameters* outputParams, double desiredSamplerate);
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
