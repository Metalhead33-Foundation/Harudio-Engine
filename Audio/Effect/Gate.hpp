#ifndef GATE_HPP
#define GATE_HPP
#include "SampleLevelEffect.hpp"
#include "SingleAttributeEffect.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(Gate)
class Gate : public SingleAttributeEffect, public SampleLevelEffect
{
private:
	Gate(float nLevel=1.0f);
	Gate(const SingleAttributeEffect& cpy);
public:
	static sSingleAttributeEffect create(float nLevel=1.0f);
	static sSingleAttributeEffect create(const SingleAttributeEffect& cpy);
	static sSingleAttributeEffect create(const sSingleAttributeEffect cpy);
	float doEffect(float input);
};

}
}
#endif // GATE_HPP
