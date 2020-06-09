#include "Effect/Bitcrusher.hpp"
#include <cmath>

namespace Effect {
void Bitcrusher::doEffect(float& target)
{
	target = sgn(target) * std::round(std::abs(target)*level)*levelReciprocal;
}
Bitcrusher::Bitcrusher(float nlevel)
	: SingleAttributeEffect(nlevel), levelReciprocal(1.0f/nlevel)
{
	
}
void Bitcrusher::setLevel(float nlevel)
{
	level = nlevel;
	levelReciprocal = 1.0f/nlevel;
}
}
