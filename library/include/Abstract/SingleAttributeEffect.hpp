#ifndef AUDIOSATTRIBUTEEFFECT_HPP
#define AUDIOSATTRIBUTEEFFECT_HPP
#include "AudioEffect.hpp"

namespace Audio {
DEFINE_CLASS(SingleAttributeEffect)
class SingleAttributeEffect : public Effect {
protected:
	float level;
public:
	SingleAttributeEffect(float nlevel = 1.0f);
	float getLevel() const;
	virtual void setLevel(float nlevel);
	virtual void doEffect(float& target) = 0;
};
} // namespace Audio

#endif // AUDIOSATTRIBUTEEFFECT_HPP
