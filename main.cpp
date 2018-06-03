#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Io/StdStream.hpp"
#include "Audio/Effect/Resampler.hpp"
#include "Audio/Effect/Panner.hpp"
#include "Audio/AuxiliaryEffectSlot.hpp"
#include "Audio/Effect/Overdrive.hpp"
#include <time.h>

using namespace std;

#define SONG_PATH "/home/legacy/zene/GameMusic/Doki Doki Literature Club/getoutmyhead.ogg"

int main()
{
	std::cout << "Creating context!" << std::endl;
	Audio::Context context(44100,2,1024);
	std::cout << "Created context!" << std::endl;
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 10000;
	auto sndfile = StdStream::createReader(SONG_PATH);
	auto stream = Sound::Streamer::create(sndfile,22000);
	auto resampler = Audio::Resampler::create(SRC_SINC_BEST_QUALITY);
	auto stereoPanner = Audio::StereoPanner::create();
	auto aux = Audio::AuxiliaryEffectSlot::create(2,44100);
	auto overdrive = Audio::FX::Overdrive::create(4,1.0f);
	aux->addToList(overdrive);
	resampler->setSpeed(1.00f);
	resampler->setInput(stream);
	aux->setSource(resampler);
	stereoPanner->setInput(aux);
	stereoPanner->setVolumeLevel(0.01f);
	context.addToList(stereoPanner);
	stream->play();
	context.unsuspend();
	nanosleep(&tim , &tim2);
	do {
		stream->checkQueue();
		if(nanosleep(&tim , &tim2) < 0 )
		{
			context.suspend();
		   return -1;
		}
		isPlaying = context.isPlaying();
	} while(isPlaying);
	return 0;
}
