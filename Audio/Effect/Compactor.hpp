#ifndef COMPACTOR_HPP
#define COMPACTOR_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(Compactor)
class Compactor : public Effect
{
private:
	Compactor();
	static float compact(float num);
	static float uncompact(float num, float original);
public:
	static sCompactor create();
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
};

}
}
#endif // COMPACTOR_HPP
