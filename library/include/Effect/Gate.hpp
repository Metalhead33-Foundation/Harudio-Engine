#ifndef GATE_HPP
#define GATE_HPP
#include <Abstract/SingleAttributeEffect.hpp>
namespace Effect {

DEFINE_CLASS(Gate)
class Gate : public Audio::SingleAttributeEffect {
public:
	Gate(float nlevel = 1.0f);
	void doEffect(float& target);
};
	
}
#endif // GATE_HPP
