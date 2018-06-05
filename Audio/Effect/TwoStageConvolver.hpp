#ifndef TWOSTAGECONVOLVER_HPP
#define TWOSTAGECONVOLVER_HPP
#include "../AudioEffect.hpp"
#include "../AudioBuffer.hpp"

namespace fftconvolver
{
DEFINE_CLASS(TwoStageFFTConvolver)
}

namespace Audio {
namespace FX {

DEFINE_CLASS(TwoStageConvolver)
class TwoStageConvolver : public Effect
{
private:
	const fftconvolver::sTwoStageFFTConvolver FFT;
	TwoStageConvolver(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize);
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	static sTwoStageConvolver create(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize);
};

}
}
#endif // TWOSTAGECONVOLVER_HPP
