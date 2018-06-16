#include "SampleLevelEffect.hpp"

namespace Audio {
namespace FX {

long SampleLevelEffect::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	const long sampleNum = maxFrames * channelNum;
	for(long currSample=0; currSample < sampleNum; ++currSample)
	{
		outBuffer[currSample] = doEffect(inBuffer[currSample]);
	}
	return maxFrames;
}

}
}
