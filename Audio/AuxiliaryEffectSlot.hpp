#ifndef AUXILIARYEFFECTSLOT_HPP
#define AUXILIARYEFFECTSLOT_HPP
#include "AudioPlayable.hpp"
#include "AudioEffect.hpp"
#include <vector>
#include <list>

namespace Audio {

DEFINE_CLASS(AuxiliaryEffectSlot)
class AuxiliaryEffectSlot : public Playable
{
public:
	typedef std::list<sEffect> EffectList;
	typedef EffectList::iterator EffectIterator;
private:
	PluggableBuffer dryBuffer;
	PluggableBuffer wetBuffer;
	EffectList effects;
	const int channelNumber;
	const int frameRate;
	const long frameCount;
	void swapBuffers();
	void interlace();
	void deinterlace();
	void processEffects(long intendedFrameNum);
	long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	sPlayable source;
	AuxiliaryEffectSlot(int intendedChannelNumber, int intendedFramerate);
public:
	static sAuxiliaryEffectSlot create(int intendedChannelNumber, int intendedFramerate);
	int getFramerate() const;
	int getChannelCount() const;
	long getFrameCount() const;
	const sPlayable getSource() const;
	void setSource(sPlayable nSource);

	void addToList(sEffect playable);
	void removeFromList(EffectIterator it);
	void removeFromList(sEffect playable);
	bool isPlaying() const;
};

}
#endif // AUXILIARYEFFECTSLOT_HPP
