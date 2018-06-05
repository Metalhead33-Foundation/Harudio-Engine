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
public:
	typedef fftconvolver::sTwoStageFFTConvolver FastConvolver;
private:
	std::vector<FastConvolver> convolvers;
	TwoStageConvolver(const TwoStageConvolver& cpy);
	TwoStageConvolver(const TwoStageConvolver& cpy, int channelCount);
	TwoStageConvolver(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize, int channelNum);
	TwoStageConvolver(const float* IR, size_t irLen, size_t head_blocksize, size_t tail_blocksize, int channelNum);
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	static sTwoStageConvolver create(sTwoStageConvolver cpy);
	static sTwoStageConvolver create(sTwoStageConvolver cpy, int channelCount);
	static sTwoStageConvolver create(const sBuffer nIR, size_t head_blocksize, size_t tail_blocksize, int channelNum);
	static sTwoStageConvolver create(const float* IR, size_t irLen, size_t head_blocksize, size_t tail_blocksize, int channelNum);
};

}
}
#endif // TWOSTAGECONVOLVER_HPP
