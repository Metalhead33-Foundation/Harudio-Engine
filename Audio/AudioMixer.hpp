#ifndef AUDIOMIXER_HPP
#define AUDIOMIXER_HPP
#include "AudioPlayable.hpp"
#include <list>
#include <vector>

namespace Audio {

class Mixer : public Playable
{
private:
	std::list<wPlayable> playableList;
protected:
	void mixDown(bool normalize=false);
	std::vector<float> buffer;
	const int channelNumber;
	const int frameRate;
	const long frameCount;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
public:
	Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize);
	bool isPlaying() const;
	int getFramerate() const;
	int getChannelCount() const;
};

}

#endif // AUDIOMIXER_HPP
