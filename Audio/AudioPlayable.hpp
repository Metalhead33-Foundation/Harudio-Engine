#ifndef AUDIOPLAYABLE_HPP
#define AUDIOPLAYABLE_HPP
#include "../Io/Global.hpp"
#include <portaudio.h>
#include <array>

namespace Audio {

DEFINE_CLASS(Mixer)
DEFINE_CLASS(Playable)
DEFINE_CLASS(AuxiliaryEffectSlot)
#define TINYBUFF 2048

/*struct PlayData
{
	sPlayable playableAudio;
	int framerate;
	int channelCount;
};*/

class Playable
{
public:
	friend class Mixer;
	friend class AuxiliaryEffectSlot;
public:
	typedef std::array<float,TINYBUFF> PluggableBuffer;
	virtual ~Playable() = default;
	virtual bool isPlaying() const = 0;
	static int patestCallback( const void *inputBuffer, void *outputBuffer,
							   unsigned long framesPerBuffer,
							   const PaStreamCallbackTimeInfo* timeInfo,
							   PaStreamCallbackFlags statusFlags,
							   void *userData );
	virtual int getFramerate() const = 0;
	virtual int getChannelCount() const = 0;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate) = 0;
};

}

#endif // AUDIOPLAYABLE_HPP
