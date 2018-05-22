#ifndef AUDIOMIXER_HPP
#define AUDIOMIXER_HPP
#include "AudioPlayable.hpp"
#include <list>
#include <vector>

namespace Audio {

class Mixer : public Playable
{
private:
	void mixDown(bool normalize=false);
	std::list<wPlayable> playableList;
	std::vector<float> buffer;
	const int channelNumber;
	const int frameRate;
	const long frameCount;
	float volume;
protected:
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
public:
	Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize);
	bool isPlaying();
	int getFramerate();
	int getChannelCount();
};

}

#endif // AUDIOMIXER_HPP
