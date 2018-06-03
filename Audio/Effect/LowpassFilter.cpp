#include "LowpassFilter.hpp"
#include <cstring>
extern "C" {
#include <alloca.h>
}
namespace Audio {
namespace FX {

LowpassFilter::LowpassFilter(int nLowEnd)
	: lowEnd(nLowEnd)
{
	;
}
sLowpassFilter LowpassFilter::create(int nLowEnd)
{
	return sLowpassFilter(new LowpassFilter(nLowEnd));
}
int LowpassFilter::getLowEnd() const
{
	return lowEnd;
}
void LowpassFilter::setLowEnd(int nLowEnd)
{
	lowEnd = nLowEnd;
}
long LowpassFilter::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	bool readMode=true;
	float ratio=1.00/(float(frameRate)/float(lowEnd));
	float compRatio=1.0f;
	float* kernel = reinterpret_cast<float*>(alloca(sizeof(float)*channelNum));
	memset(kernel,0,sizeof(float)*channelNum);
	for(long curFrame=0; curFrame < maxFrames; ++curFrame)
	{
		long sampleBegin=curFrame * channelNum;
		for(int curChannel=0; curChannel < channelNum; ++curChannel)
		{
			if(readMode) {
				kernel[curChannel] += inBuffer[sampleBegin+curChannel];
			} else {
				outBuffer[sampleBegin+curChannel] = kernel[curChannel];
			}
		}
		compRatio -= ratio;
		if(compRatio <= 0.0f)
		{
			if(readMode) {
				readMode = false;
				for(int i = 0; i < channelNum;++i) kernel[i] /= 1.0f/ratio;
				while(compRatio <= 1.0f)
				{
					--curFrame;
					compRatio += ratio;
				}
			} else {
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

}
}
