#include "AudioContext.hpp"
#include <stdexcept>
#include <cstring>
#include <vector>
#include <climits>

namespace Audio {

std::recursive_mutex Context::locker;

Context::Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize)
	: Mixer(intendedBumChannels,intendedFramerate,intendedBufferSize), dev(0)
{
	SDL_AudioSpec want, have;
	SDL_memset(&want, 0, sizeof(want));
	want.freq = intendedFramerate;
	want.format = AUDIO_F32;
	want.channels = intendedBumChannels;
	want.samples = intendedBufferSize;
	want.callback = Playable::SDL_AudioCallback;
	want.userdata = this;
	this->dev = SDL_OpenAudioDevice(NULL, 0, &want, &have, 0);
	if (dev == 0) {
		throw std::runtime_error(SDL_GetError());
	}
	std::unique_lock<std::recursive_mutex> locker(this->locker);
}
Context::~Context()
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
	if(dev) SDL_CloseAudioDevice(dev);
}
void Context::suspend()
{
	SDL_PauseAudioDevice(dev,1);
}
void Context::unsuspend()
{
	SDL_PauseAudioDevice(dev,0);
}
bool Context::isStopped()
{
	return (SDL_GetAudioDeviceStatus(dev) != SDL_AUDIO_PLAYING);
}
bool Context::isActive()
{
	return (SDL_GetAudioDeviceStatus(dev) == SDL_AUDIO_PLAYING);
}

}
