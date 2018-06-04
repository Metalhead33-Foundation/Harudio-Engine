#ifndef GATE_HPP
#define GATE_HPP
#include "SampleLevelEffect.hpp"
namespace Audio {
namespace FX {

class Gate : public SampleLevelEffect
{
private:
	float level;
public:
	Gate();
	float doEffect(float input);
};

}
}
#endif // GATE_HPP
