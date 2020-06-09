#ifndef BITCRUSHER_HPP
#define BITCRUSHER_HPP
#include <Abstract/SingleAttributeEffect.hpp>
namespace Effect {

DEFINE_CLASS(Bitcrusher)
class Bitcrusher : public Audio::SingleAttributeEffect<float> {
private:
	float levelReciprocal;
public:
	Bitcrusher(float nlevel = 1.0f);
	void doEffect(float& target);
	void setLevel(float nlevel) override;
};
	
}
#endif // BITCRUSHER_HPP
