#include "Resampler.hpp"
namespace Audio {

Resampler::Resampler(int converterType)
	: converter(nullptr), converterType(converterType)
{

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
	cleanBuffer();
	convertData.src_ratio = double(tmp->getFramerate()) / double(frameRate);
	long processedFrames = 0;
	long readFrames = 0;
	int guard = int(double(TINYBUFF / 2) / convertData.src_ratio);
	guard = std::min(guard,TINYBUFF/2);
	do {
		convertData.data_out = ownBuffer;
		convertData.data_out = &ownBuffer[guard];
		readFrames = tmp->pullAudio(ownBuffer,guard/tmp->getChannelCount(),tmp->getChannelCount(),tmp->getFramerate());
		convertData.input_frames = readFrames;
		readFrames = long(double(readFrames) * convertData.src_ratio);
		convertData.output_frames = readFrames;
		converter->process(&convertData);
		for(long addedSamples = 0; addedSamples < readFrames && processedFrames < maxFrameNum; ++addedSamples,++processedFrames)
		{
			for(int i = 0; i < channelNum; ++i)
			{
				output[processedFrames+i] += ownBuffer[guard+addedSamples+i];
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
