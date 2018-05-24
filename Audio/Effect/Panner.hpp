#ifndef PANNER_HPP
#define PANNER_HPP
#include "../AudioPluginPlayable.hpp"
#include <stdexcept>

namespace Audio {
template <int outputChannelCount> class Panner : public PluginPlayable
{
private:
	enum MixingType : uint8_t
	{
		EQUAL_MIX,
		DOWNMIX,
		UPMIX
	} mixingType;
	float volumeLevel[outputChannelCount];
	float channelRatio;
	int inputChannelCount;
	float inputBuffer[TINYBUFF];
protected:
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
	{
		if(input.expired()) return 0;
		if(channelNum != outputChannelCount) throw std::runtime_error("Panner - The number of requested channels doesn't match the number of output channels for this panner!");
		sPlayable tinput = input.lock();
		long processedFrames = 0;
		long readFrames = 0;
		do {
			readFrames = std::min(maxFrameNum-processedFrames,long(TINYBUFF/tinput->getChannelCount()));
			readFrames = tinput->pullAudio(inputBuffer,readFrames,inputChannelCount,tinput->getFramerate());
			for(long curFrame = 0; curFrame < readFrames; ++curFrame,++processedFrames)
			{
				long inCursor = curFrame * inputChannelCount;
				long outCursor = processedFrames * outputChannelCount;
				switch (mixingType) {
					case EQUAL_MIX:
					{
						for(int i = 0; i < inputChannelCount;++i)
							output[outCursor+i] += inputBuffer[inCursor+i] * volumeLevel[i];
						break;
					}
					case DOWNMIX:
					{
						for(int i = 0; i < inputChannelCount;++i)
							output[outCursor+(i%outputChannelCount)] += inputBuffer[inCursor+i] * volumeLevel[i%outputChannelCount] * channelRatio;
						break;
					}
					case UPMIX:
					{
						for(int i = 0; i < outputChannelCount;++i)
							output[outCursor+i] += inputBuffer[inCursor+(i%inputChannelCount)] * volumeLevel[i];
						break;
					}
				}
			}
		} while(readFrames);
		return processedFrames;
	}
	void setInputChannelCount(int newChannelCount) {
		inputChannelCount = newChannelCount;
		if(inputChannelCount == outputChannelCount) mixingType = EQUAL_MIX;
		else if(inputChannelCount < outputChannelCount) mixingType = UPMIX;
		else mixingType = DOWNMIX;
		channelRatio = float(outputChannelCount) / float(inputChannelCount);
	}
virtual void onChangedInput()
	{
		sPlayable tinput = input.lock();
		setInputChannelCount(tinput->getChannelCount());
	}
public:
	float getVolumeLevel(int index) const { return volumeLevel[index % outputChannelCount]; }
	void setVolumeLevel(int index, float newBalance) { volumeLevel[index % outputChannelCount] = newBalance; }
	int getInputChannelCount() const { return inputChannelCount; }
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
	virtual int getChannelCount() const
	{
		return outputChannelCount;
	}
};

typedef Panner<2> StereoPanner;

}

#endif // PANNER_HPP
