#ifndef RESAMPLER_HPP
#define RESAMPLER_HPP
#include "../AudioPluginPlayable.hpp"
#include "../Samplerate.hpp"

namespace Audio {
class Resampler : public PluginPlayable
{
private:
	sSamplerate converter;
	SRC_DATA convertData;
	int converterType;
	float inputBuffer[TINYBUFF];
	float outputBuffer[TINYBUFF];
	void cleanBuffers();
public:
	Resampler(int converterType);
	virtual void onChangedInput();
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
};

}

#endif // RESAMPLER_HPP
