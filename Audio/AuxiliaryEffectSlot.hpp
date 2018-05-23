#ifndef AUXILIARYEFFECTSLOT_HPP
#define AUXILIARYEFFECTSLOT_HPP
#include "AudioPlayable.hpp"
#include "AudioEffect.hpp"
#include <vector>
#include <list>

namespace Audio {

class AuxiliaryEffectSlot : public Playable
{
private:
	std::vector<float> dryBuffer;
	std::vector<float> wetBuffer;
	std::list<sEffect> effects;
	const int channelNumber;
	const int frameRate;
	const long frameCount;
	void processEffects();
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	sPlayable source;
public:
	AuxiliaryEffectSlot(int intendedChannelNumber, int intendedFramerate, long intendedBufferSize);
	int getFramerate() const;
	int getChannelCount() const;
	const sPlayable getSource() const;
	void setSource(sPlayable nSource);
};

}
#endif // AUXILIARYEFFECTSLOT_HPP
