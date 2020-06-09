#ifndef CLAMP_HPP
#define CLAMP_HPP
#include <Abstract/SingleAttributeEffect.hpp>
namespace Effect {

DEFINE_CLASS(Clamp)
class Clamp : public Audio::SingleAttributeEffect<float> {
public:
	Clamp(float nlevel = 1.0f);
	void doEffect(float& target);
};
	
}
#endif // CLAMP_HPP
