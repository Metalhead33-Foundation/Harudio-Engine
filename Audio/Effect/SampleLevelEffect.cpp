#include "SampleLevelEffect.hpp"

namespace Audio {
namespace FX {

SampleLevelEffect::SampleLevelEffect(float nEffectLevel)
	: effectLevel(nEffectLevel)
{

}
float SampleLevelEffect::getEffectLevel() const
{
	return effectLevel;
}
void SampleLevelEffect::setEffectLevel(float nEffectLevel)
{
	effectLevel = nEffectLevel;
}
long SampleLevelEffect::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	for(long currFrame=0; currFrame < maxFrames; ++currFrame)
	{
		long sampleCursor = currFrame * channelNum;
		for(int i = 0; i < channelNum; ++i)
		{
			long currSample = sampleCursor+i;
			outBuffer[currSample] = (inBuffer[currSample]*(1.0f-effectLevel))+
					(doEffect(inBuffer[currSample])*effectLevel);
		}
	}
	return maxFrames;
}

}
}
