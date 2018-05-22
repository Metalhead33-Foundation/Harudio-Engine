#include "Resampler.hpp"
namespace Audio {
namespace FX {

Resampler::Resampler(int intendedChannelNumber, int converterType)
	: converter(converterType,intendedChannelNumber), channelNumber(intendedChannelNumber)
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
	if(channelNum != channelNumber) throw std::runtime_error("Resampler - I/O Channel number mismatch! Please use a panner or channel mixer!");
	convertData.src_ratio = double(inputFramerate) / double(frameRate);
	convertData.input_frames = long(double(maxFrames) * convertData.src_ratio);
	convertData.output_frames = maxFrames;
	convertData.data_in = inBuffer;
	convertData.data_out = outBuffer;
	converter.process(&convertData);
	return maxFrames;
}

}
}
