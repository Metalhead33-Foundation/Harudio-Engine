#include "SampleLevelEffect.hpp"

namespace Audio {
namespace FX {

long SampleLevelEffect::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	const long sampleNum = maxFrames * channelNum;
	// #pragma omp target teams distribute parallel for
#pragma omp for
	for(long currSample=0; currSample < sampleNum; ++currSample)
	{
		outBuffer[currSample] = doEffect(inBuffer[currSample]);
	}
	return maxFrames;
}

}
}
