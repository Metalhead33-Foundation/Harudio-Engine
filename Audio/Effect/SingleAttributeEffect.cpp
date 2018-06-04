#include "SingleAttributeEffect.hpp"
namespace Audio {
namespace FX {

SingleAttributeEffect::SingleAttributeEffect(float nLevel)
	: level(nLevel)
{
	;
}
SingleAttributeEffect::SingleAttributeEffect(const SingleAttributeEffect& cpy)
	: level(cpy.level)
{
	;
}
float SingleAttributeEffect::getLevel() const
{
	return level;
}
void SingleAttributeEffect::setLevel(float nLevel)
{
	level = nLevel;
}

}
}
