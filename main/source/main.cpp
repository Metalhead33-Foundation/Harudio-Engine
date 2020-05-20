#include "Driver/SDL.hpp"
#include "Sound/SoundModulePlayer.hpp"
#include "Sound/SoundSinewave.hpp"
#include "Sound/SoundSource.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Util/AudioConvolver.hpp"
#include "Util/AudioMixer.hpp"
#include "Global/StdStream.hpp"
#include <iostream>

using namespace std;

const char* sharedDig = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/05 - Shared Dig [Alexander Brandon].s3m";
const char* Title = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/02 - Flight Castle (Unreal Menu) [Alexander Brandon].it";
const char* digging = "/home/legacy/zene/GameMusic/Legacy of Kain/Soul Reaver - Ozar Midrashim 20th Anniversary Cover-9f9wiAiu_8E.ogg";
const char* starwars_ogg = "/home/legacy/zene/GameMusic/converted_midis/rjedi_select.ogg";
const char* starwars_opus = "/home/legacy/zene/GameMusic/converted_midis/rjedi_select.opus";
const char* motika = "/home/legacy/Vuze Downloads/Tropico5.tar/Tropico 5/Music/Motika.opus";
const char* blastereo_wav = "/home/legacy/zene/GameMusic/blastereo.wav";
const char* blastereo_ogg = "/home/legacy/zene/GameMusic/blastereo.ogg";
const char* blastereo_opus = "/home/legacy/zene/GameMusic/blastereo.opus";
const char* IR = "/home/legacy/zene/Projects/Red Wire Impulses/eloxl-wav01.wav";

int main()
{
	std::string str2;
	SDL_Init(SDL_INIT_AUDIO);
	Abstract::sFIO stream1(new StdStream(sharedDig,true));
	Abstract::sFIO irstream(new StdStream(IR,true));
	auto mod = std::make_shared<Sound::ModulePlayer>(stream1);
	auto convolver = std::make_shared<Audio::Convolver>(irstream,1024);
	//streamer->checkQueue();
	auto tester = std::make_shared<Sound::Sinewave>(1200.0f,1.0f/48000.0f);
	Driver::SDL audioDev(48000,1,2048);
	auto mixer = std::make_shared<Audio::Mixer>(1000,audioDev.getFreq(),audioDev.getChannels()) ;
	audioDev.setPlayable(mixer);
	convolver->setPlayable(mod);
	mixer->insert(convolver,0.5f);
	mod->play();
	//streamer->play();
	//mixer->insert(tester,0.1f);
	mixer->setActive(true);
	audioDev.pause(false);
	cout << "Hello World!" << endl;
	/*do {
		SDL_Delay(1000);
		streamer->checkQueue();
	} while(true);*/
	cin >> str2;
	SDL_Quit();
	return 0;
}
