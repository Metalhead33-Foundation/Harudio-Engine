#include "Effect/Gate.hpp"

namespace Effect {
void Gate::doEffect(float& target)
{
	target = sgn(target) * (std::max(std::abs(target), level) - level) / (1.0f - level);
}
Gate::Gate(float nlevel)
	: SingleAttributeEffect(nlevel)
{
	
}
}
