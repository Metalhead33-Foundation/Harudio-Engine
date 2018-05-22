#include "AudioContext.hpp"
#include <stdexcept>
#include <cstring>

namespace Audio {

Context::Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize, int conversionQuality)
	: framerate(intendedBufferSize), numChannels(intendedBumChannels),
	  mixingBuffer(intendedBufferSize), stream(nullptr), samplerateConverter(conversionQuality, intendedBumChannels)
{
	PaError err;
	err = Pa_OpenDefaultStream( &stream,
								0,          /* no input channels */
								numChannels,          /* stereo output */
								paFloat32,  /* 32 bit floating point output */
								framerate,
								intendedBufferSize,        /* frames per buffer, i.e. the number
												   of sample frames that PortAudio will
												   request from the callback. Many apps
												   may want to use
												   paFramesPerBufferUnspecified, which
												   tells PortAudio to pick the best,
												   possibly changing, buffer size.*/
								patestCallback, /* this is your callback function */
								this); /*This is a pointer that will be passed to
												   your callback*/
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}

Context::~Context()
{
	if(stream) Pa_CloseStream(stream);
}
void Context::suspend()
{
	PaError err = Pa_StopStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Context::unsuspend()
{
	PaError err = Pa_StartStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Context::abort()
{
	PaError err = Pa_AbortStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
bool Context::isStopped()
{
	PaError err = Pa_IsStreamStopped(stream);
	return err != 0;
}
bool Context::isActive()
{
	PaError err = Pa_IsStreamActive(stream);
	return err != 0;
}

}
