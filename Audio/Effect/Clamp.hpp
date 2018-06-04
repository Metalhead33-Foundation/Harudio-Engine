#ifndef CLAMP_HPP
#define CLAMP_HPP
#include "SampleLevelEffect.hpp"
namespace Audio {
namespace FX {


class Clamp : public SampleLevelEffect
{
private:
	float level;
public:
	Clamp();
	float doEffect(float input);
};

}
}
#endif // CLAMP_HPP
