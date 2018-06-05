#ifndef CONVOLVER_HPP
#define CONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"


namespace fftconvolver
{
DEFINE_CLASS(FFTConvolver)
}

namespace Audio {
namespace FX {

DEFINE_CLASS(Convolver)
class Convolver : public Effect
{
private:
	const fftconvolver::sFFTConvolver FFT;
	Convolver(const sBuffer nIR, size_t blocksize);
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	static sConvolver create(const sBuffer nIR, size_t blocksize);
};

}
}
#endif // CONVOLVER_HPP
