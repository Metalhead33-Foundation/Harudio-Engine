#include "AudioContext.hpp"
#include <cstring>

namespace Audio {

Context::Context(size_t bufferSize, int nChannelNum, int nSampleRate, int conversionQuality)
	: samplerateConverter(conversionQuality, nChannelNum), tempBuffer(bufferSize),
	  channelNum(nChannelNum), sampleRate(nSampleRate)
{
	;
}
long Context::process(long frameNum, const float* input, float* output, int inputSamplerate)
{
	if(inputSamplerate != sampleRate) {
	// Prepare for process
	converter.data_in = input;
	converter.data_out = tempBuffer.data();
	converter.src_ratio = double(inputSamplerate) / double(sampleRate);
	long maxFrameNum = long(double(tempBuffer.size()) / converter.src_ratio);
	maxFrameNum = MIN(maxFrameNum,frameNum);
	converter.input_frames = maxFrameNum;

	// Now we process
	samplerateConverter.process(&converter);

	// Okay, now that we are done converting the samples...
	memcpy(output,tempBuffer.data(),sizeof(float) * maxFrameNum);

	// Reset everything, as we are finished with processing!
	memset(&converter, 0, sizeof(SRC_DATA));
	return maxFrameNum;
	} else {
		long maxFrameNum = MIN(frameNum,tempBuffer.size());
		memcpy(output,input,sizeof(float) * maxFrameNum);
		return maxFrameNum;
	}
}

}
