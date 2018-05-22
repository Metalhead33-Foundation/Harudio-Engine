#include "Resampler.hpp"
namespace Audio {
namespace FX {

Resampler::Resampler(int intendedChannelNumber, int converterType)
	: converter(converterType,intendedChannelNumber)
{

}
void Resampler::setInputFramerate(int newFramerate)
{
	inputFramerate = newFramerate;
}
int Resampler::getInputFramerate() const
{
	return inputFramerate;
}
long Resampler::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	convertData.src_ratio = double(inputFramerate) / double(frameRate);
	convertData.input_frames = long(double(maxFrames) * convertData.src_ratio);
	convertData.output_frames = maxFrames;
	convertData.data_in = inBuffer;
	convertData.data_out = outBuffer;
	converter.process(&convertData);
}

}
}
