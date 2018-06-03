#ifndef SAMPLELEVELEFFECT_HPP
#define SAMPLELEVELEFFECT_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(SampleLevelEffect)
class SampleLevelEffect : public Effect
{
private:
	float effectLevel;
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	SampleLevelEffect(float nEffectLevel=1.0f);
	virtual ~SampleLevelEffect() = default;
	float getEffectLevel() const;
	void setEffectLevel(float nEffectLevel);
	virtual float doEffect(float input) = 0;
};

}
}

#endif // SAMPLELEVELEFFECT_HPP
