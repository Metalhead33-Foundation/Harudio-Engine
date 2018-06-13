#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include <vector>
#include "Convolver.hpp"
#include "TwoStageConvolver.hpp"

namespace Audio {
namespace FX {
sConvolver createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount);

}
}
#endif // LOWPASSFILTER_HPP
