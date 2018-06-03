#ifndef AUDIOMIXER_HPP
#define AUDIOMIXER_HPP
#include "AudioPlayable.hpp"
#include <list>
#include <vector>

namespace Audio {

class Mixer : public Playable
{
public:
	typedef std::list<wPlayable> PlayableList;
	typedef PlayableList::iterator PlayableIterator;
private:
	PlayableList playableList;
protected:
	void mixDown(bool normalize=false);
	std::vector<float> inputBuffer;
	std::vector<float> outputBuffer;
	const int channelNumber;
	const int frameRate;
	const long frameCount;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
public:
	Mixer(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize);
	bool isPlaying() const;
	int getFramerate() const;
	int getChannelCount() const;
	void addToList(sPlayable playable);
	void removeFromList(PlayableIterator it);
	void removeFromList(sPlayable playable);
};

}

#endif // AUDIOMIXER_HPP
