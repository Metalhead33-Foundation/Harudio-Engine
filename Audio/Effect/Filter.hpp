#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "Convolver.hpp"
#include "TwoStageConvolver.hpp"

namespace Audio {
namespace FX {
// Lowpass filters
sConvolver createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount);
// Highpass filters
sConvolver createHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount);
}
}
#endif // LOWPASSFILTER_HPP
