#ifndef CONVOLVER_HPP
#define CONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"
#include <vector>

namespace fftconvolver
{
DEFINE_CLASS(FFTConvolver)
}

namespace Audio {
namespace FX {

DEFINE_CLASS(Convolver)
class Convolver : public Effect
{
public:
	typedef fftconvolver::sFFTConvolver FastConvolver;
private:
	Convolver(const Convolver& cpy);
	Convolver(const Convolver& cpy, int channelCount);
	Convolver(const sBuffer nIR, size_t blocksize, int channelCount);
	Convolver(const float* IR, size_t irSize, size_t blocksize, int channelCount);
protected:
	std::vector<FastConvolver> convolvers;
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	static sConvolver create(sConvolver cpy);
	static sConvolver create(sConvolver cpy, int channelCount);
	static sConvolver create(const sBuffer nIR, size_t blocksize, int channelCount);
	static sConvolver create(const float* IR, size_t irSize, size_t blocksize, int channelCount);
};

}
}
#endif // CONVOLVER_HPP
