#ifndef SINGLEATTRIBUTEEFFECT_HPP
#define SINGLEATTRIBUTEEFFECT_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(SingleAttributeEffect)
class SingleAttributeEffect : public virtual Effect
{
protected:
	float level;
public:
	SingleAttributeEffect(float nLevel=1.0f);
	SingleAttributeEffect(const SingleAttributeEffect& cpy);
	virtual ~SingleAttributeEffect() = default;
	float getLevel() const;
	void setLevel(float nLevel);
};

}
}

#endif // SINGLEATTRIBUTEEFFECT_HPP
