#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Io/StdStream.hpp"
#include "Audio/Effect/Resampler.hpp"
#include "Audio/Effect/Panner.hpp"
#include "Audio/AuxiliaryEffectSlot.hpp"
#include "Audio/Effect/Gate.hpp"
#include "Audio/Effect/Clamp.hpp"
#include "Audio/Effect/TwoStageConvolver.hpp"
#include <time.h>

using namespace std;

#define SONG_PATH "/home/legacy/zene/GameMusic/Doki Doki Literature Club/getoutmyhead.ogg"
#define IR_PATH "/home/metalhead33/vst/Red Wire Impulses/Impulses/Blue Voodoo 4x12 WGS Veteran30 Laney/15-06_e609_Edge_-1-081115_1802_dc.wav"
#define IR2_PATH "/home/metalhead33/vst/Red Wire Impulses/Impulses/Amps & Cabs (Guitar)/Fender68VibroluxReverb/Fender 68-Vibrolux SM57 off Axis.wav"
#define IR3_PATH "/home/metalhead33/vst/Red Wire Impulses/catharsis-awesometime-fredman/2off-preshigh.wav"

int main()
{
	std::cout << "Creating context!" << std::endl;
	Audio::Context context(44100,2,2048);
	std::cout << "Created context!" << std::endl;
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 10000;
	auto sndfile = StdStream::createReader(SONG_PATH);
	auto irfile = StdStream::createReader(IR3_PATH);
	auto irBuff = Audio::Buffer::create(irfile);
	auto stream = Sound::Streamer::create(sndfile,22000);
	auto resampler = Audio::Resampler::create(SRC_SINC_BEST_QUALITY);
	auto stereoPanner = Audio::StereoPanner::create();
	auto aux = Audio::AuxiliaryEffectSlot::create(2,44100);
	auto overdrive = Audio::FX::Clamp::create(0.2f);
	auto convolver = Audio::FX::TwoStageConvolver::create(irBuff,64,512,2);
	resampler->setSpeed(1.10f);
	resampler->setInput(stream);
	aux->addToList(overdrive);
	aux->addToList(convolver);
	aux->setSource(resampler);
	stereoPanner->setInput(aux);
	stereoPanner->setVolumeLevel(0.2f);
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
