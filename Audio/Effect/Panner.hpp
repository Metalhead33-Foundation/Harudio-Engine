#ifndef PANNER_HPP
#define PANNER_HPP
#include "../AudioEffect.hpp"
#include <stdexcept>

namespace Audio {
namespace FX {

template <int outputChannelCount> class Panner : public Effect
{
protected:
	enum MixingType : uint8_t
	{
		EQUAL_MIX,
		DOWNMIX,
		UPMIX
	} mixingType;
	float volumeLevel[outputChannelCount];
	float channelRatio;
	int inputChannelCount;
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
	{
		if(channelNum != outputChannelCount) throw std::runtime_error("Panner - The number of requested channels doesn't match the number of output channels for this panner!");
		for(long curFrame = 0; curFrame < maxFrames; ++curFrame)
		{
			long inCursor = curFrame * inputChannelCount;
			long outCursor = curFrame * outputChannelCount;
			switch (mixingType) {
				case EQUAL_MIX:
				{
					for(int i = 0; i < inputChannelCount;++i)
						outBuffer[outCursor+i] = inBuffer[inCursor+i] * volumeLevel[i];
					break;
				}
				case DOWNMIX:
				{
					for(int i = 0; i < inputChannelCount;++i)
						outBuffer[outCursor+(i%outputChannelCount)] += inBuffer[inCursor+i] * volumeLevel[i%outputChannelCount] * channelRatio;
					break;
				}
				case UPMIX:
				{
					for(int i = 0; i < outputChannelCount;++i)
						outBuffer[outCursor+i] = inBuffer[inCursor+(i%inputChannelCount)] * volumeLevel[i];
					break;
				}
			}
		}
	}
public:
	float getVolumeLevel(int index) const { return volumeLevel[index % outputChannelCount]; }
	void setVolumeLevel(int index, float newBalance) { volumeLevel[index % outputChannelCount] = newBalance; }
	int getInputChannelCount() const { return inputChannelCount; }
	void setInputChannelCount(int newChannelCount) {
		inputChannelCount = newChannelCount;
		if(inputChannelCount == outputChannelCount) mixingType = EQUAL_MIX;
		else if(inputChannelCount < outputChannelCount) mixingType = UPMIX;
		else mixingType = DOWNMIX;
		channelRatio = float(outputChannelCount) / float(inputChannelCount);
	}
	Panner()
	{
		setInputChannelCount(1);
		for(int i = 0; i < outputChannelCount; ++i) volumeLevel[i] = 1.00f;
	}
	Panner(int inputChCount)
	{
		setInputChannelCount(inputChCount);
		for(int i = 0; i < outputChannelCount; ++i) volumeLevel[i] = 1.00f;
	}
};

typedef Panner<2> StereoPanner;

}
}

#endif // PANNER_HPP
