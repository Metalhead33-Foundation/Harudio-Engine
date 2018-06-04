#ifndef CLAMP_HPP
#define CLAMP_HPP
#include "SampleLevelEffect.hpp"
#include "SingleAttributeEffect.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(Clamp)
class Clamp : public SingleAttributeEffect, public SampleLevelEffect
{
private:
	Clamp(float nLevel=1.0f);
	Clamp(const SingleAttributeEffect& cpy);
public:
	static sSingleAttributeEffect create(float nLevel=1.0f);
	static sSingleAttributeEffect create(const SingleAttributeEffect& cpy);
	static sSingleAttributeEffect create(const sSingleAttributeEffect cpy);
	float doEffect(float input);
};

}
}
#endif // CLAMP_HPP
