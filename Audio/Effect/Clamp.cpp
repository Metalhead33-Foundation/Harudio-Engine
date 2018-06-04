#include "Clamp.hpp"
#include <cmath>
namespace Audio {
namespace FX {

Clamp::Clamp()
{

}
float Clamp::doEffect(float input)
{
	// return std::min(input, level) / (level);
	return sgn(input) * std::min(std::abs(input), level) / (level);
}

}
}
