#include "Degrader.hpp"
#include <cstring>
#include <cmath>

namespace Audio {
namespace FX {

Degrader::Degrader(int nLowEnd)
	: lowEnd(nLowEnd)
{
	;
}
sDegrader Degrader::create(int nLowEnd)
{
	return sDegrader(new Degrader(nLowEnd));
}
int Degrader::getLowEnd() const
{
	return lowEnd;
}
void Degrader::setLowEnd(int nLowEnd)
{
	lowEnd = nLowEnd;
}
long Degrader::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	bool readMode=true;
	const long sampleCount=maxFrames*channelNum;
	const float invRatio=floor((float(frameRate)/float(lowEnd))+0.5f);
	const float ratio=1.0f/invRatio;
	float compRatio=1.0f;
	float kernel = 0.0f;
	memcpy(outBuffer,inBuffer,sampleCount*sizeof(float));
	for(int curChannel=0;curChannel<channelNum;++curChannel)
	{
		long curFrame=0;
		for(curFrame=0;curFrame<maxFrames;++curFrame)
		{
			const long samplePtr=(maxFrames*curChannel)+curFrame;
			if(readMode)
			{
				kernel += inBuffer[samplePtr];
			}
			else
			{
				outBuffer[samplePtr] = kernel;
			}
			compRatio -= ratio;
			if(compRatio <= 0.0f)
			{
				if(readMode)
				{
					readMode = false;
					kernel /= invRatio;
					while(compRatio <= 1.0f)
					{
						--curFrame;
						compRatio += ratio;
					}
				}
				else
				{
					kernel = 0;
					readMode = true;
					while(compRatio <= 1.0f)
					{
						compRatio += ratio;
					}
				}
				if(curFrame < 0) curFrame = 0;
			}
		}
		if(readMode)
		{
			readMode = false;
			kernel /= compRatio;
			// outBuffer[(maxFrames*curChannel)+curFrame] = kernel;
		}
		compRatio = 1.0f;
		readMode = true;
		kernel = 0;
	}
	return maxFrames;
}

}
}
