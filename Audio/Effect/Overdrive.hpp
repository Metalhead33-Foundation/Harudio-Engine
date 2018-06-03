#ifndef OVERDRIVE_HPP
#define OVERDRIVE_HPP
#include "SampleLevelEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(Overdrive)
class Overdrive : public SampleLevelEffect
{
private:
	Overdrive(float distortionPower = 1.0f);
public:
	static sOverdrive create(float distortionPower = 1.0f);
	float doEffect(float input);
};

}
}

#endif // OVERDRIVE_HPP
