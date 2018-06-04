#include "Convolver.hpp"
namespace Audio {
namespace FX {

Convolver::Convolver(const sBuffer nIR)
	: IR(nIR)
{
	;
}
sConvolver Convolver::create(const sBuffer nIR)
{
	if(nIR) return sConvolver(new Convolver(nIR));
	else return nullptr;
}
long Convolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	BufferOutput ptr;
	IR->getAudioData(&ptr,0);
	for(int sampleOffset=0; sampleOffset<channelNum;++sampleOffset)
	{
		for(long currFrame=0;currFrame<maxFrames;++currFrame)
		{
			long outputSampleCursor = (currFrame*channelNum)+sampleOffset;
			outBuffer[outputSampleCursor] = 0.0f;
			for(long bufferCursor=0;bufferCursor<ptr.second;++bufferCursor)
			{
				long inputSampleCursor = ((currFrame-bufferCursor)*channelNum)+sampleOffset;
				if(inputSampleCursor > 0) outBuffer[outputSampleCursor] += inBuffer[inputSampleCursor] * ptr.first[bufferCursor];
				// else outBuffer[outputSampleCursor] += ptr.first[bufferCursor];
			}
		}
	}
	return maxFrames;
}

}
}
