#ifndef COMPLEXCONVOLVER_HPP
#define COMPLEXCONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(ComplexConvolver)
DEFINE_STRUCT(ComplexConvolver_private)
class ComplexConvolver : public Effect
{
private:
	uComplexConvolver_private impl;
public:
	ComplexConvolver(size_t blocksize, int channelCount);
	ComplexConvolver(size_t head, size_t tail, int channelCount);
	void reset(size_t blocksize, int channelCount);
	void reset(size_t head, size_t tail, int channelCount);
	void init(const sBuffer nIR, int channelId);
	void init(const float* IR, size_t irSize, int channelId);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
};

}
}
#endif // COMPLEXCONVOLVER_HPP
