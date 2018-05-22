#include "TwoDimensionalPanner.hpp"
namespace Audio {
namespace FX {

TwoDimensionalPanner::TwoDimensionalPanner()
{
	setBalance(0.5f);
}
float TwoDimensionalPanner::getBalance() const
{
	return balance;
}
void TwoDimensionalPanner::setBalance(float newBalance)
{
	balance = newBalance;
	inverseBalance = 1.00f - balance;
	compensator = 1.00f - std::max(balance,inverseBalance);
}
long TwoDimensionalPanner::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != 2) throw std::runtime_error("TwoDimensionalPanner - Only stereo output is supported!");
	if(inputChannelCount == 1)
	{
		for(long curFrame = 0; curFrame < maxFrames; ++curFrame)
		{
			long outputCursor = curFrame * 2;
			outBuffer[outputCursor] = inBuffer[curFrame] * (inverseBalance + compensator);
			outBuffer[outputCursor+1] = inBuffer[curFrame] * (balance + compensator);
		}
	}
	else if(inputChannelCount == 2)
	{
		for(long curFrame = 0; curFrame < maxFrames; ++curFrame)
		{
			long outputCursor = curFrame * 2;
			outBuffer[outputCursor] = inBuffer[outputCursor] * (inverseBalance + compensator);
			outBuffer[outputCursor+1] = inBuffer[outputCursor+1] * (balance + compensator);
		}
	}

	else if(inputChannelCount > 2)
	{
		float fChannelCount = float(inputChannelCount);
		for(long curFrame = 0; curFrame < maxFrames; ++curFrame)
		{
			long outputCursor = curFrame * 2;
			long inputCursor = curFrame * inputChannelCount;
			for(int i = 0; i < inputChannelCount; ++i)
			{
				if(i%2)	outBuffer[outputCursor+(i%2)] += inBuffer[inputCursor+i] * (balance + compensator) / fChannelCount;
				else outBuffer[outputCursor+(i%2)] += inBuffer[inputCursor+i] * (inverseBalance + compensator) / fChannelCount;
			}
		}
	}
	else throw std::runtime_error("TwoDimensionalPanner - Invalid number of channels!");
	return maxFrames;
}
int TwoDimensionalPanner::getInputChannelCount() const
{
	return inputChannelCount;
}
void TwoDimensionalPanner::setInputChannelCount(int newChannelCount)
{
	inputChannelCount = newChannelCount;
}

}
}
