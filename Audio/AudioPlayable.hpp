#ifndef AUDIOPLAYABLE_HPP
#define AUDIOPLAYABLE_HPP
#include "../Io/Global.hpp"
#include <portaudio.h>

namespace Audio {

DEFINE_CLASS(Mixer)
DEFINE_CLASS(Playable)

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
protected:
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate) = 0;
	float volume;
public:
	virtual ~Playable() = default;
	virtual bool isPlaying() = 0;
	static int patestCallback( const void *inputBuffer, void *outputBuffer,
							   unsigned long framesPerBuffer,
							   const PaStreamCallbackTimeInfo* timeInfo,
							   PaStreamCallbackFlags statusFlags,
							   void *userData );
	virtual int getFramerate() = 0;
	virtual int getChannelCount() = 0;
	float getVolume();
	void setVolume(float nVolume);
	static void mixChannels(const float* frameIn, float* frameOut, int chanIn, int chanOut, float vol, size_t frameCount=1);
	enum MixingType : uint8_t
	{
		EQUAL_MIX,
		DOWNMIX,
		UPMIX
	};
};

}

#endif // AUDIOPLAYABLE_HPP
