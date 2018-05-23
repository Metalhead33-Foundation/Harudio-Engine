#ifndef AUDIOEFFECT_HPP
#define AUDIOEFFECT_HPP
#include "../Io/Global.hpp"

namespace Audio {

DEFINE_CLASS(Effect)
DEFINE_CLASS(AuxiliaryEffectSlot)
class Effect
{
public:
	friend class AuxiliaryEffectSlot;
protected:
	virtual long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate) = 0;
public:
	virtual ~Effect() = default;
};

}

#endif // AUDIOEFFECT_HPP
