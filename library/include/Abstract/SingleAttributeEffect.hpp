#ifndef AUDIOSATTRIBUTEEFFECT_HPP
#define AUDIOSATTRIBUTEEFFECT_HPP
#include "AudioEffect.hpp"

namespace Audio {

template <typename T> class SingleAttributeEffect : public Effect {
protected:
	T level;
public:
	SingleAttributeEffect(T nlevel = 1);
	T getLevel() const { return level; }
	virtual void setLevel(T nlevel) { level = nlevel; }
	virtual void doEffect(float& target) = 0;
};
} // namespace Audio

#endif // AUDIOSATTRIBUTEEFFECT_HPP
