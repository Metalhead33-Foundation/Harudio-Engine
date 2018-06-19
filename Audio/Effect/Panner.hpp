#ifndef PANNER_HPP
#define PANNER_HPP
#include "../AudioPluginPlayable.hpp"
#include <stdexcept>

namespace Audio {
template <int outputChannelCount> class Panner : public PluginPlayable
{
public:
	typedef std::shared_ptr<Panner> sPanner;
private:
	enum MixingType : uint8_t
	{
		EQUAL_MIX,
		DOWNMIX,
		UPMIX
	} mixingType;
	float channelRatio;
	int inputChannelCount;
	PluggableBuffer inputBuffer;
protected:
	float volumeLevel[outputChannelCount];
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
	{
		if(input.expired()) return 0;
		if(channelNum != outputChannelCount) throw std::runtime_error("Panner - The number of requested channels doesn't match the number of output channels for this panner!");
		sPlayable tinput = input.lock();
		long processedFrames = 0;
		long readFrames = 0;
		do {
			readFrames = std::min(maxFrameNum-processedFrames,long(inputBuffer.size()/tinput->getChannelCount()));
			readFrames = tinput->pullAudio(inputBuffer.data(),readFrames,inputChannelCount,tinput->getFramerate());
			for(long curFrame = 0; curFrame < readFrames; ++curFrame,++processedFrames)
			{
				const long inCursor = curFrame * inputChannelCount;
				const long outCursor = processedFrames * outputChannelCount;
				for(int i = 0; i < outputChannelCount;++i) output[outCursor+i] = 0.0f;
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
public:
	float getVolumeLevel(int index) const { return volumeLevel[index % outputChannelCount]; }
	void setVolumeLevel(int index, float newBalance) { volumeLevel[index % outputChannelCount] = newBalance; }
	void setVolumeLevel(float newBalance) {
		for(int i = 0; i < outputChannelCount; ++i) volumeLevel[i] = newBalance;
	}
	int getInputChannelCount() const { return inputChannelCount; }
	virtual int getChannelCount() const
	{
		return outputChannelCount;
	}
	static sPanner createPanner()
	{
		return sPanner(new Panner());
	}
	static sPanner createPanner(int inputChCount)
	{
		return sPanner(new Panner(inputChCount));
	}
};

typedef Panner<1> MonoPanner;
typedef Panner<2> StereoPanner;
typedef Panner<4> QuadPanner;

}

#endif // PANNER_HPP
