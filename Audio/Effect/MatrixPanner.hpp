#ifndef MATRIXPANNER_HPP
#define MATRIXPANNER_HPP
#include "../AudioPluginPlayable.hpp"
#include <stdexcept>
#include <iostream>

namespace Audio {
template <int inputChannelCount, int outputChannelCount> class MatrixPanner : public PluginPlayable
{
private:
	PluggableBuffer inputBuffer;
protected:
	float volumeLevel[inputChannelCount][outputChannelCount];
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
	{
		if(input.expired()) return 0;
		if(channelNum != outputChannelCount) throw std::runtime_error("Panner - The number of requested channels doesn't match the number of output channels for this panner!");
		sPlayable tinput = input.lock();
		long processedFrames = 0;
		long readFrames = 0;
		do {
			readFrames = std::min(maxFrameNum-processedFrames,long(inputBuffer.size()/inputChannelCount));
			// readFrames = std::min(maxFrameNum-processedFrames,long(inputBuffer.size()/tinput->getChannelCount()));
			readFrames = tinput->pullAudio(inputBuffer.data(),readFrames,inputChannelCount,tinput->getFramerate());
			for(long curFrame = 0; curFrame < readFrames; ++curFrame,++processedFrames)
			{
				const long inCursor = curFrame * inputChannelCount;
				const long outCursor = processedFrames * outputChannelCount;
				for(int i = 0; i < outputChannelCount;++i) output[outCursor+i] = 0.0f;
				for(int i = 0; i < inputChannelCount;++i)
				{
					for(int j = 0; j < outputChannelCount;++j)
					{
						output[outCursor+j] += inputBuffer[inCursor+i] * volumeLevel[i][j];
						if(inputChannelCount >= 2) std::cout << output[outCursor+j] << "\n";
					}
				}
			}
		} while(readFrames);
	}
	MatrixPanner()
	{
		for(int i = 0; i < inputChannelCount;++i)
		{
			for(int j = 0; j < outputChannelCount;++j)
			{
				volumeLevel[i][j] = 1.0f;
			}
		}
	}
	virtual void onChangedInput()
	{
		;
	}
public:
	void setVolume(float vol, int row, int column)
	{
		volumeLevel[row % inputChannelCount][column % outputChannelCount] = vol;
	}
	float getVolume(int row, int column) const
	{
		return volumeLevel[row % inputChannelCount][column % outputChannelCount];
	}
	virtual int getChannelCount() const
	{
		return outputChannelCount;
	}
	typedef std::shared_ptr<MatrixPanner> sMatrixPanner;
	static sMatrixPanner createMatrixPanner()
	{
		return sMatrixPanner(new MatrixPanner);
	}
};
typedef MatrixPanner<1,2> Mono2StereoPanner;
typedef MatrixPanner<2,1> Stereo2MonoPanner;
typedef MatrixPanner<1,4> Mono2QuadPanner;
typedef MatrixPanner<2,2> Stereo2StereoPanner;

}
#endif // MATRIXPANNER_HPP
