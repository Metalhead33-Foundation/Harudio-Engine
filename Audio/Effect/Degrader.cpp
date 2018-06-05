#include "Degrader.hpp"
#include <cstring>

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
	const float invRatio=(float(frameRate)/float(lowEnd));
	const float ratio=1.0f/invRatio;
	float compRatio=1.0f;
	float kernel = 0.0f;
	for(int curChannel=0;curChannel<channelNum;++curChannel)
	{
		for(long curFrame=0;curFrame<maxFrames;++curFrame)
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
	}
	return maxFrames;
}

}
}
