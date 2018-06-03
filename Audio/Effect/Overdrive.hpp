#ifndef OVERDRIVE_HPP
#define OVERDRIVE_HPP
#include "SampleLevelEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(Overdrive)
class Overdrive : public SampleLevelEffect
{
private:
	Overdrive(int multi=1, float distortionPower = 1.0f);
	int selfMultiplyAmmount;
public:
	static sOverdrive create(int multi=1, float distortionPower = 1.0f);
	float doEffect(float input);
	int getSelfMultiplyAmount() const;
	void setSelfMultiplyAmount(int multi);
};

}
}

#endif // OVERDRIVE_HPP
