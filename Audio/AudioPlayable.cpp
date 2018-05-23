#include "AudioPlayable.hpp"

namespace Audio {


int Playable::patestCallback( const void *inputBuffer, void *outputBuffer,
						   unsigned long framesPerBuffer,
						   const PaStreamCallbackTimeInfo* timeInfo,
						   PaStreamCallbackFlags statusFlags,
						   void *userData )
{
	if(userData) {
	pPlayable data = reinterpret_cast<pPlayable>(userData);
	float *out = reinterpret_cast<float*>(outputBuffer);
	data->pullAudio(out, framesPerBuffer, data->getChannelCount(), data->getFramerate());
	return paContinue;
	} else return paAbort;
}
float Playable::getVolume() const
{
	return volume;
}
void Playable::setVolume(float nVolume)
{
	volume = nVolume;
}

}
