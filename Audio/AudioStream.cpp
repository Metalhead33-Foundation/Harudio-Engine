#include "AudioStream.hpp"
#include <stdexcept>

namespace Audio {

Stream::Stream(const sInputBuffer nBuff, int samplerate, size_t buffsize)
	: buff(nBuff), stream(nullptr)
{
	PaError err;
	err = Pa_OpenDefaultStream( &stream,
								0,          /* no input channels */
								2,          /* stereo output */
								paFloat32,  /* 32 bit floating point output */
								samplerate,
								buffsize,        /* frames per buffer, i.e. the number
												   of sample frames that PortAudio will
												   request from the callback. Many apps
												   may want to use
												   paFramesPerBufferUnspecified, which
												   tells PortAudio to pick the best,
												   possibly changing, buffer size.*/
								InputBuffer::patestCallback, /* this is your callback function */
								buff.get()); /*This is a pointer that will be passed to
												   your callback*/
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
Stream::~Stream()
{
	if(stream) Pa_CloseStream(stream);
}
void Stream::start()
{
	PaError err = Pa_StartStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Stream::stop()
{
	PaError err = Pa_StopStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Stream::abort()
{
	PaError err = Pa_AbortStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
bool Stream::isStopped()
{
	PaError err = Pa_IsStreamStopped(stream);
	return err != 0;
}
bool Stream::isActive()
{
	PaError err = Pa_IsStreamActive(stream);
	return err != 0;
}

}

