#include "AudioInputBuffer.hpp"

namespace Audio {

int InputBuffer::patestCallback( const void *inputBuffer, void *outputBuffer,
						   unsigned long framesPerBuffer,
						   const PaStreamCallbackTimeInfo* timeInfo,
						   PaStreamCallbackFlags statusFlags,
						   void *userData )
{
	pInputBuffer data = reinterpret_cast<pInputBuffer>(userData);
	if(data) {
	float *out = reinterpret_cast<float*>(outputBuffer);

	// calculate num frames left to read
	long numFramesLeft = data->getFrameCount() - data->getFrameIndex();
	long numFramesToRead = (numFramesLeft < framesPerBuffer) ? numFramesLeft : framesPerBuffer;

	data->process(out,sf_count_t(numFramesToRead));
	return (data->getFrameIndex() >= data->getFrameCount()) ? paComplete : paContinue;
	} else return paAbort;
}

}
