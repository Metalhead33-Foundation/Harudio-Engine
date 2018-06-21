#ifndef SIMPLECONVOLVER_HPP
#define SIMPLECONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"
#include "AdaptableConvolver.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(SimpleConvolver)
DEFINE_STRUCT(SimpleConvolver_private)
class SimpleConvolver : public Effect, public AdaptableConvolver
{
private:
	uSimpleConvolver_private impl;
protected:
	void adapt(const std::vector<float>& IR, int channelId);
public:
	SimpleConvolver(size_t blocksize, int channelCount);
	SimpleConvolver(size_t head, size_t tail, int channelCount);
	void reset(size_t blocksize, int channelCount);
	void reset(size_t head, size_t tail, int channelCount);
	void init(const sBuffer nIR);
	void init(const float* IR, size_t irSize);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
};

}
}
#endif // SIMPLECONVOLVER_HPP
