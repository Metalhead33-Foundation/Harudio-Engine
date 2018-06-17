#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Io/StdStream.hpp"
#include "Audio/Effect/Resampler.hpp"
#include "Audio/Effect/Panner.hpp"
#include "Audio/AuxiliaryEffectSlot.hpp"
#include "Audio/Effect/Delay.hpp"
#include "Audio/Effect/Degrader.hpp"
#include <time.h>

using namespace std;

#define SONG_PATH "/home/legacy/zene/GameMusic/Doki Doki Literature Club/getoutmyhead.ogg"
#define RUS_SONG "/home/legacy/zene/GameMusic/Doki Doki Literature Club/rus.ogg"
#define ENG_SONG "/home/legacy/zene/GameMusic/Doki Doki Literature Club/10000000_1576501802457395_2632349514147481969_n.ogg"
#define STILL_NIGHT "/home/legacy/zene/GameMusic/Runescape/Still Night (Journey to Varrock) - RuneScape Guitar Cover-M4XFYy75u5g.ogg"
#define HARMONY "/home/legacy/zene/GameMusic/Runescape/Harmony (Lumbridge) - Runescape Guitar Cover-fAgnRd7BUPo.ogg"
#define IR_PATH "/home/metalhead33/vst/Red Wire Impulses/Impulses/Blue Voodoo 4x12 WGS Veteran30 Laney/15-06_e609_Edge_-1-081115_1802_dc.wav"
#define IR2_PATH "/home/metalhead33/vst/Red Wire Impulses/Impulses/Amps & Cabs (Guitar)/Fender68VibroluxReverb/Fender 68-Vibrolux SM57 off Axis.wav"
#define IR3_PATH "/home/metalhead33/vst/Red Wire Impulses/catharsis-awesometime-fredman/2off-preshigh.wav"
#define IR4_PATH "/home/metalhead33/QtProjects/Audio-Stuff/ir1.wav"

int main()
{
	std::cout << "Creating context!" << std::endl;
	Audio::Context context(48000,2,2048);
	std::cout << "Created context!" << std::endl;
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 1000;
	auto sndfile = StdStream::createReader(STILL_NIGHT);
	auto irfile = StdStream::createReader(IR4_PATH);
	auto irBuff = Audio::Buffer::create(irfile);
	auto stream = Sound::Streamer::create(sndfile,22000);
	stream->setLooping(true);
	auto resampler = Audio::Resampler::create(SRC_SINC_BEST_QUALITY);
	auto stereoPanner = Audio::StereoPanner::create();
	auto aux = Audio::AuxiliaryEffectSlot::create(2,48000);
	auto delay = Audio::FX::Delay::create(512,8000,0.3f,2);
	// auto convolver = Audio::FX::LowpassFilter::create(512,2,44100,5000);
	auto degrader = Audio::FX::Degrader::create(3500);
	resampler->setSpeed(1.20f);
	resampler->setInput(stream);
	aux->addToList(delay,1.00f);
	aux->setSource(resampler);
	stereoPanner->setInput(aux);
	stereoPanner->setVolumeLevel(1.0f);
	context.addToList(stereoPanner,1.0f);
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
