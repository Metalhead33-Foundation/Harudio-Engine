#include "Abstract/SingleAttributeEffect.hpp"
namespace Audio {
float SingleAttributeEffect::getLevel() const
{
	return level;
}
void SingleAttributeEffect::setLevel(float nlevel)
{
	level = nlevel;
}
SingleAttributeEffect::SingleAttributeEffect(float nlevel)
	: level(nlevel)
{
	
}
}
