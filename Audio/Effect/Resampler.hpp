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
	float outputBuffer[TINYBUFF];
	SRC_STATE* converter;
	float speed;
	void cleanBuffers();
	static long converterCallback(void *self, float **data);

	double getRatio(int outputFramerate) const;
	Resampler(int converterType=SRC_LINEAR);
public:
	static sResampler create(int converterType=SRC_LINEAR);
	virtual void onChangedInput();
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate);
	float getSpeed() const;
	void setSpeed(float newSpeed);
};

}

#endif // RESAMPLER_HPP
