#ifndef AUDIOCONTEXT_HPP
#define AUDIOCONTEXT_HPP
#include "Samplerate.hpp"
#include <vector>
namespace Audio {

class Context
{
private:
	Samplerate samplerateConverter;
	std::vector<float> tempBuffer;
	SRC_DATA converter;
public:
	const int channelNum;
	const int sampleRate;
	Context(size_t bufferSize, int nChannelNum, int nSampleRate, int conversionQuality);
	long process(long frameNum, const float* input, float* output, int inputSamplerate);
};

}
#endif // AUDIOCONTEXT_HPP
