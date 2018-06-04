#include "Clamp.hpp"
#include <cmath>
namespace Audio {
namespace FX {

Clamp::Clamp(float nLevel)
	: SingleAttributeEffect(nLevel)
{
	;
}
Clamp::Clamp(const SingleAttributeEffect& cpy)
	: SingleAttributeEffect(cpy)
{
	;
}
sSingleAttributeEffect Clamp::create(float nLevel)
{
	return sSingleAttributeEffect(new Clamp(nLevel));
}
sSingleAttributeEffect Clamp::create(const SingleAttributeEffect& cpy)
{
	return sSingleAttributeEffect(new Clamp(cpy));
}
sSingleAttributeEffect Clamp::create(const sSingleAttributeEffect cpy)
{
	if(cpy) return sSingleAttributeEffect(new Clamp(*cpy));
	else return nullptr;
}
float Clamp::doEffect(float input)
{
	// return std::min(input, level) / (level);
	return sgn(input) * std::min(std::abs(input), level) / (level);
}

}
}
