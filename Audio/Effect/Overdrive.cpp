#include "Overdrive.hpp"
#include <cmath>

namespace Audio {
namespace FX {

Overdrive::Overdrive(float distortionPower)
	: SampleLevelEffect(distortionPower)
{
	;
}
sOverdrive Overdrive::create(float distortionPower)
{
	return sOverdrive(new Overdrive(distortionPower));
}
float Overdrive::doEffect(float input)
{
	if(input >= 0.0f)
	{
		return (1.0f - exp(input));
	}
	else
	{
		return (-1.0f + exp(input));
	}
}

}
}
