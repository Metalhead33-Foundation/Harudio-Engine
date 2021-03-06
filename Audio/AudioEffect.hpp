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
public:
	virtual ~Effect() = default;
	virtual long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate) = 0;
};

}

#endif // AUDIOEFFECT_HPP
