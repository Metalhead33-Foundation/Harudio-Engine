#include "Gate.hpp"
namespace Audio {
namespace FX {

Gate::Gate()
{

}
float Gate::doEffect(float input)
{
	// return (std::max(input, level) - level) / (1.0f - level);
	return sgn(input) * (std::max(std::abs(input), level) - level) / (1.0f - level);
}

}
}
