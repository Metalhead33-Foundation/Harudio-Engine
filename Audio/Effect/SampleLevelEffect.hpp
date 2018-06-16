#ifndef SAMPLELEVELEFFECT_HPP
#define SAMPLELEVELEFFECT_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(SampleLevelEffect)
class SampleLevelEffect : public virtual Effect
{
public:
	virtual ~SampleLevelEffect() = default;
	virtual float doEffect(float input) = 0;
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
};

}
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

#endif // SAMPLELEVELEFFECT_HPP
