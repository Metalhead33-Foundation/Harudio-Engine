#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Io/StdStream.hpp"
#include "Audio/Effect/Resampler.hpp"
#include "Audio/Effect/Panner.hpp"
#include "Audio/AuxiliaryEffectSlot.hpp"
#include "Audio/Effect/Clamp.hpp"
#include "Audio/Effect/Gate.hpp"
#include "Audio/Effect/Degrader.hpp"
#include "Audio/Effect/BitCrusher.hpp"
#include "Audio/Effect/Filter.hpp"
#include "Audio/Effect/Convolver.hpp"
#include "Audio/Effect/AmbisonicPanner.hpp"
#include "Sound/SongLibrary.hpp"
#include <time.h>

using namespace std;

#define SONG_PATH "/home/legacy/zene/GameMusic/Doki Doki Literature Club/getoutmyhead.ogg"
#define RUS_SONG "/home/legacy/zene/GameMusic/Doki Doki Literature Club/rus.ogg"
#define ENG_SONG "/home/legacy/zene/GameMusic/Doki Doki Literature Club/10000000_1576501802457395_2632349514147481969_n.ogg"
#define STILL_NIGHT "/home/legacy/zene/GameMusic/Runescape/Still Night (Journey to Varrock) - RuneScape Guitar Cover-M4XFYy75u5g.ogg"
#define HARMONY "/home/legacy/zene/GameMusic/Runescape/Harmony (Lumbridge) - Runescape Guitar Cover-fAgnRd7BUPo.ogg"
#define IR_PATH "/home/legacy/study/lofi_impulse_responses/20mm_loudspeaker.wav"
#define IR2_PATH "/home/metalhead33/vst/Red Wire Impulses/Impulses/Amps & Cabs (Guitar)/Fender68VibroluxReverb/Fender 68-Vibrolux SM57 off Axis.wav"
#define IR3_PATH "/home/metalhead33/vst/Red Wire Impulses/catharsis-awesometime-fredman/2off-preshigh.wav"
#define IR4_PATH "/home/metalhead33/QtProjects/Audio-Stuff/ir1.wav"

int main()
{
#pragma omp parallel num_threads(3)
	std::cout << "Creating context!" << std::endl;
	Audio::Context context(48000,2,2048);
	std::cout << "Created context!" << std::endl;
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 1000;
	auto irfile = StdStream::createReader(IR_PATH);
	auto irBuff = Audio::Buffer::create(irfile);
	auto resampler = Audio::Resampler::create(SRC_SINC_BEST_QUALITY);
	auto stereoPanner = Audio::StereoPanner::createPanner();
	auto monoPanner = Audio::MonoPanner::createPanner();
	auto ambisonic = Audio::AmbisonicPanner::createAmbisonicPanner();


	auto songlib = Sound::SongLibrary::create(
				[](const std::string& path) {
			std::vector<std::string> vec;
			vec.push_back("/home/legacy/zene/others/Eurobeat/Initial D - Night Of Fire-SRbhLtjOiRc.ogg");
			vec.push_back("/home/legacy/zene/Jmusic/m.o.v.e/m.o.v.e _ FLY ME SO HIGH-13XKfnzPgz4.ogg");
			vec.push_back("/home/legacy/zene/Jmusic/m.o.v.e/m.o.v.e _ BREAK IN2 THE NITE-7OkzGLgyyCw.ogg");
			return vec;
		},StdStream::createReader
	);
	for(auto it = songlib->begin(); it != songlib->end();++it)
	{
		std::cout << it->artist << " - " << it->title << "\n";
	}
	auto stream = Sound::Streamer::create(songlib->getSong(2).getSong(StdStream::createReader),
										  22000);
	stream->setLooping(true);
	monoPanner->setInput(stream);
	ambisonic->setInput(monoPanner);

	resampler->setSpeed(1.20f);
	resampler->setInput(ambisonic);
	stereoPanner->setInput(resampler);
	// stereoPanner->setVolumeLevel(1.0f);
	context.addToList(stereoPanner,1.0f);
	stream->play();
	context.unsuspend();
	nanosleep(&tim , &tim2);
	float degrees = 0;
	do {
		stream->checkQueue();
		degrees += 0.01f;
		ambisonic->setHorizontalAngle(degrees*0.0174532925f);
		if(nanosleep(&tim , &tim2) < 0 )
		{
			context.suspend();
		   return -1;
		}
		isPlaying = context.isPlaying();
	} while(isPlaying);
	return 0;
}
