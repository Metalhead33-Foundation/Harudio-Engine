#ifndef RESAMPLER_HPP
#define RESAMPLER_HPP
#include "../AudioEffect.hpp"
#include "../Samplerate.hpp"

namespace Audio {
namespace FX {

class Resampler : public Effect
{
private:
	Samplerate converter;
	SRC_DATA convertData;
	int inputFramerate;
	const int channelNumber;
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	Resampler(int intendedChannelNumber, int converterType);
	void setInputFramerate(int newFramerate);
	int getInputFramerate() const;
};

}
}

#endif // RESAMPLER_HPP
