#ifndef AUDIOMIXER_IMP_HPP
#define AUDIOMIXER_IMP_HPP
#include "../harudio-headers/Audio/AudioMixer.hpp"
#include <vector>
#include <unordered_map>

namespace Software {

class Mixer : public Audio::Mixer
{
public:
	Mixer(int intendedChannelNumber, int intendedFramerate,
		  long intendedBufferSize);
	// "Inherited" from Playable
	virtual bool isPlaying() const;
	virtual int getFramerate() const ;
	virtual int getChannelCount() const;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	// New functions
	virtual void addToList(Audio::sPlayable playable,float volume);
	virtual void removeFromList(Audio::sPlayable playable);
	virtual float getVolume(Audio::sPlayable playable) const;
	virtual bool empty() const;

	const int channelNumber;
	const int frameRate;
	const long bufferSize;
private:
	std::vector<float> inputBuffer;
	std::vector<float> outputBuffer;
	std::unordered_map<Audio::sPlayable,float> playableList;
	virtual long mixDown(long maxFrameNum);
};

}
#endif // AUDIOMIXER_IMP_HPP
