#include "AudioPlayable.hpp"

namespace Audio {


int Playable::patestCallback( const void *inputBuffer, void *outputBuffer,
						   unsigned long framesPerBuffer,
						   const PaStreamCallbackTimeInfo* timeInfo,
						   PaStreamCallbackFlags statusFlags,
						   void *userData )
{
	if(userData && outputBuffer) {
	const pPlayable data = static_cast<pPlayable>(userData);
	// float* out = (float*)outputBuffer;
	float* out = static_cast<float*>(outputBuffer);
	if(data->isPlaying()) data->pullAudio(out, framesPerBuffer, data->getChannelCount(), data->getFramerate());
	// std::cout << userData << " - audio: " << *out << std::endl;
	return paContinue;
	} else return paAbort;
}

}
