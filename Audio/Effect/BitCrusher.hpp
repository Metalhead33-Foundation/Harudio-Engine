#ifndef BITCRUSHER_HPP
#define BITCRUSHER_HPP
#include "SampleLevelEffect.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(BitCrusher)
class BitCrusher : public SampleLevelEffect
{
private:
	float numberClamper;
	uint8_t bits;
	BitCrusher(uint8_t nbits=8);
public:
	static sBitCrusher create(uint8_t nbits=8);
	float doEffect(float input);
	uint8_t getBits() const;
	void setBits(uint8_t setto);
};

}
}
#endif // BITCRUSHER_HPP
