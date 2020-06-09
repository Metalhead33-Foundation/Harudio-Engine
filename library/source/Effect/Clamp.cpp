#include "Effect/Clamp.hpp"

namespace Effect {
void Clamp::doEffect(float& target)
{
	target = sgn(target) * std::min(std::abs(target), level) / (level);
}
Clamp::Clamp(float nlevel)
	: SingleAttributeEffect(nlevel)
{
	
}
}
