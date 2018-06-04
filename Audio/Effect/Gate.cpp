#include "Gate.hpp"
namespace Audio {
namespace FX {

Gate::Gate(float nLevel)
	: SingleAttributeEffect(nLevel)
{
	;
}
Gate::Gate(const SingleAttributeEffect& cpy)
	: SingleAttributeEffect(cpy)
{
	;
}
sSingleAttributeEffect Gate::create(float nLevel)
{
	return sSingleAttributeEffect(new Gate(nLevel));
}
sSingleAttributeEffect Gate::create(const SingleAttributeEffect& cpy)
{
	return sSingleAttributeEffect(new Gate(cpy));
}
sSingleAttributeEffect Gate::create(const sSingleAttributeEffect cpy)
{
	if(cpy) return sSingleAttributeEffect(new Gate(*cpy));
	else return nullptr;
}
float Gate::doEffect(float input)
{
	// return (std::max(input, level) - level) / (1.0f - level);
	return sgn(input) * (std::max(std::abs(input), level) - level) / (1.0f - level);
}

}
}
