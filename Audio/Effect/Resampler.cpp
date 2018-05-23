#include "Resampler.hpp"
#include <cstring>
namespace Audio {

Resampler::Resampler(int converterType)
	: converter(nullptr), converterType(converterType)
{
	convertData.data_in = inputBuffer;
	convertData.data_out = outputBuffer;
}
void Resampler::cleanBuffers()
{
	memset(inputBuffer,0,TINYBUFF * sizeof(float));
	memset(outputBuffer,0,TINYBUFF * sizeof(float));
}
void Resampler::onChangedInput()
{
	sPlayable tmp = input.lock();
	converter = sSamplerate(new Samplerate(converterType,tmp->getChannelCount()));
}
long Resampler::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(input.expired()) return 0;
	sPlayable tmp = input.lock();
	if(channelNum != tmp->getChannelCount()) throw std::runtime_error("Resampler - I/O Channel number mismatch! Please use a panner or channel mixer!");
	cleanBuffers();
	convertData.src_ratio = double(frameRate) / double(tmp->getFramerate());
	double greaterDenominator = double(std::max(tmp->getFramerate(),frameRate)) / double(std::min(tmp->getFramerate(),frameRate));
	int guard = std::min(int(maxFrameNum),TINYBUFF);
	if(frameRate > tmp->getFramerate()) // Downsample - smaller output
	{
		guard = int(double(guard/channelNum) * convertData.src_ratio);
	} else { // Upsample - smaller input
		guard = int(double(guard/channelNum) / convertData.src_ratio);
	}
	long processedFrames = 0;
	long readFrames = 0;
	do {
		readFrames = tmp->pullAudio(inputBuffer,guard,channelNum,tmp->getFramerate());
		convertData.input_frames = readFrames;
		convertData.output_frames = long(double(readFrames)*convertData.src_ratio);
		converter->process(&convertData);
		for(long frameCursor = 0; frameCursor < convertData.output_frames; ++frameCursor,++processedFrames)
		{
			for(int i = 0; i < channelNum; ++i)
			{
				output[processedFrames+i] += outputBuffer[frameCursor+i];
			}
		}
	} while(readFrames);
	return processedFrames;
}
/*long Resampler::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != channelNumber) throw std::runtime_error("Resampler - I/O Channel number mismatch! Please use a panner or channel mixer!");
	convertData.src_ratio = double(inputFramerate) / double(frameRate);
	convertData.input_frames = long(double(maxFrames) * convertData.src_ratio);
	convertData.output_frames = maxFrames;
	convertData.data_in = inBuffer;
	convertData.data_out = outBuffer;
	converter.process(&convertData);
	return maxFrames;
}*/

}
