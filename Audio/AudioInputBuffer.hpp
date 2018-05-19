#ifndef AUDIOIBUFFER_HPP
#define AUDIOIBUFFER_HPP
#include "../Io/SoundFile.hpp"
#include <portaudio.h>

namespace Audio {

DEFINE_CLASS(InputBuffer)
class InputBuffer
{
public:
	virtual ~InputBuffer() = 0;
	virtual sf_count_t getFrameCount() = 0;
	virtual sf_count_t getFrameIndex() = 0;
	virtual void setFrameIndex(sf_count_t nIndex) = 0;
	virtual float* getFramebuffer() = 0;
	virtual void process(float* out, sf_count_t framesToRead) = 0;
	static int patestCallback( const void *inputBuffer, void *outputBuffer,
							   unsigned long framesPerBuffer,
							   const PaStreamCallbackTimeInfo* timeInfo,
							   PaStreamCallbackFlags statusFlags,
							   void *userData );
};

}
#endif // AUDIOIBUFFER_HPP
