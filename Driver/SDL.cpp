#include "SDL.hpp"

namespace Driver {

Audio::sPlayable SDL::getPlayable() const
{
	return playable;
}

void SDL::setPlayable(const Audio::sPlayable &value)
{
	playable = value;
}

int SDL::getFreq() const
{
	return have.freq;
}

Uint8 SDL::getChannels() const
{
	return have.channels;
}

Uint16 SDL::getSamples() const
{
	return have.samples;
}

SDL::SDL(int freq, uint8_t channels, uint16_t frameCnt)
{
	SDL_AudioSpec want;
	SDL_memset(&want, 0, sizeof(want));
	want.freq = freq;
	want.format = AUDIO_F32;
	want.channels = channels;
	want.samples = frameCnt*channels;
	want.callback = SDL_AudioCallback;
	want.userdata = this;
	id = SDL_OpenAudioDevice(nullptr, 0, &want, &have, 0);
}

SDL::~SDL()
{
	if(id) SDL_CloseAudioDevice(id);
}

void SDL::SDL_AudioCallback(void *userdata, Uint8 *stream, int len)
{
	memset(stream,0,len);
	if(userdata) {
	auto chandle = reinterpret_cast<SDL*>(userdata);
	if(chandle->playable) {
	Audio::Output out;
	out.dst = reinterpret_cast<float*>(stream);
	out.frameRate = chandle->have.freq;
	out.channelCnt = chandle->have.channels;
	out.frameCnt = len/sizeof(float)/out.channelCnt;
	out.interleavingType = Audio::InterleavingType::INTERLEAVED;
	chandle->playable->outputTo(out);
	}
	}
}

void SDL::lock()
{
	if(id) SDL_LockAudioDevice(id);
}

void SDL::unlock()
{
	if(id) SDL_UnlockAudioDevice(id);
}

void SDL::pause(bool val)
{
	if(id) SDL_PauseAudioDevice(id,val);
}

}
