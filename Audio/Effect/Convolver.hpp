#ifndef CONVOLVER_HPP
#define CONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(Convolver)
class Convolver : public Effect
{
private:
	const sBuffer IR;
	std::vector<float> memBuffer;
	long memPtr;
	Convolver(const sBuffer nIR);
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	static sConvolver create(const sBuffer nIR);
};

}
}
#endif // CONVOLVER_HPP
