#include "Overdrive.hpp"
#include <cmath>

namespace Audio {
namespace FX {

Overdrive::Overdrive(int multi, float distortionPower)
	: SampleLevelEffect(distortionPower), selfMultiplyAmmount(multi)
{
	;
}
sOverdrive Overdrive::create(int multi, float distortionPower)
{
	return sOverdrive(new Overdrive(multi,distortionPower));
}
float Overdrive::doEffect(float input)
{
	bool isNegative = input < 0.0f;
	if(isNegative) input *= -1.0f;
	input *= 0.5f;
	input += 1.0f;
	for(int i = 0; i < selfMultiplyAmmount; ++i) input *= input;
	input -= 1.0f;
	input = std::min(input,1.0f);
	if(isNegative) input *= -1.0f;
	return input;
}
int Overdrive::getSelfMultiplyAmount() const
{
	return selfMultiplyAmmount;
}
void Overdrive::setSelfMultiplyAmount(int multi)
{
	selfMultiplyAmmount = multi;
}

}
}
