#ifndef RESAMPLER_HPP
#define RESAMPLER_HPP
#include "../AudioPluginPlayable.hpp"
#include <samplerate.h>

namespace Audio {
DEFINE_CLASS(Resampler)
class Resampler : public PluginPlayable
{
private:
	int converterType;
	float inputBuffer[TINYBUFF];
	float outputBuffer[TINYBUFF];
	SRC_STATE* converter;
	float speed;
	int outputFramerate;
	void cleanBuffers();
	static long converterCallback(void *self, float **data);

	double getRatio() const;
public:
	Resampler(int converterType);
	virtual void onChangedInput();
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	float getSpeed() const;
	void setSpeed(float newSpeed);
};

}

#endif // RESAMPLER_HPP
