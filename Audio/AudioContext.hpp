#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP
#include "Samplerate.hpp"
#include "AudioMixer.hpp"
#include <vector>
#include <mutex>
#include <SDL2/SDL_audio.h>

namespace Audio {

class Context : public Mixer
{
private:
	SDL_AudioDeviceID dev;
	static std::recursive_mutex locker;
public:
	Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize);
	~Context();
	void suspend();
	void unsuspend();
	bool isStopped();
	bool isActive();
};

}

#endif // AUDIOCONTEXT_HPP
