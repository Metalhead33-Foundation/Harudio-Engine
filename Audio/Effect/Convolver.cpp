#include "Convolver.hpp"
#include <cstring>
namespace Audio {
namespace FX {

Convolver::Convolver(const sBuffer nIR)
	: IR(nIR), memBuffer(nIR->getSampleCount()*2), memPtr(0)
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
	memcpy(&memBuffer[memPtr],inBuffer,std::min(ptr.second,long(memBuffer.size())-memPtr)*sizeof(float));
	for(long currFrame=0;currFrame<maxFrames;++currFrame)
	{
		for(int sampleOffset=0; sampleOffset<channelNum;++sampleOffset)
		{
			long outputSampleCursor = (currFrame*channelNum)+sampleOffset;
			outBuffer[outputSampleCursor] = 0.0f;
			// memBuffer[memPtr] = inBuffer[outputSampleCursor];
			for(int I = 0; I < ptr.second; I++) {
				outBuffer[outputSampleCursor] += memBuffer[(memBuffer.size() + memPtr - I) % memBuffer.size()]*ptr.first[I];
			}
			if(memPtr >= memBuffer.size()) memPtr = 0;
			else memPtr++;
		}
	}
	return maxFrames;
}

}
}
