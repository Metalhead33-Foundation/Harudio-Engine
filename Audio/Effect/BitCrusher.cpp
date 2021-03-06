#include "BitCrusher.hpp"
#include <cmath>
namespace Audio {
namespace FX {

BitCrusher::BitCrusher(uint8_t nbits)
	:  bits(nbits)
{
	numberClamper = pow(double(2),double(nbits-1));
}
sBitCrusher BitCrusher::create(uint8_t nbits)
{
	return sBitCrusher(new BitCrusher(nbits));
}
float BitCrusher::doEffect(float input)
{
	bool isNegative = input < 0.0f;
	if(isNegative) input *= -1.0f;
	input = std::min(input,1.0f);
	input *= numberClamper;
	input = floorf(input+0.5f);
	input /= numberClamper;
	if(isNegative) input *= -1.0f;
	return input;
}
uint8_t BitCrusher::getBits() const
{
	return bits;
}
void BitCrusher::setBits(uint8_t setto)
{
	if(bits != setto)
	{
		bits = setto;
		numberClamper = pow(double(2),double(bits))-1.0;
	}
}

}
}
