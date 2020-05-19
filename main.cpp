#include <iostream>
#include "Driver/SDL.hpp"
#include "Util/AudioMixer.hpp"
#include "Sound/SoundModulePlayer.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Sound/SoundSinewave.hpp"
#include "Global/StdStream.hpp"

using namespace std;

const char* sharedDig = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/dig.s3m";
const char* Title = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/02 - Flight Castle (Unreal Menu) [Alexander Brandon].it";
const char* digging = "/home/legacy/zene/GameMusic/Legacy of Kain/Soul Reaver - Ozar Midrashim 20th Anniversary Cover-9f9wiAiu_8E.ogg";
const char* starwars_ogg = "/home/legacy/zene/GameMusic/converted_midis/rjedi_select.ogg";
const char* starwars_opus = "/home/legacy/zene/GameMusic/converted_midis/rjedi_select.opus";
const char* motika = "/home/legacy/Vuze Downloads/Tropico5.tar/Tropico 5/Music/Motika.opus";
const char* blastereo_wav = "/home/legacy/zene/GameMusic/blastereo.wav";
const char* blastereo_ogg = "/home/legacy/zene/GameMusic/blastereo.ogg";
const char* blastereo_opus = "/home/legacy/zene/GameMusic/blastereo.opus";

int main()
{
	std::string str2;
	SDL_Init(SDL_INIT_AUDIO);
	Abstract::sFIO stream1(new StdStream(sharedDig,true));
	Abstract::sFIO stream2(new StdStream(starwars_opus,true));
	Abstract::sFIO stream3(new StdStream(blastereo_opus,true));
	auto mod = std::make_shared<Sound::ModulePlayer>(stream1);
	auto streamer = std::make_shared<Sound::Streamer>(stream2);
	auto buff = std::make_shared<Sound::Buffer>(stream3);
	auto snd = std::make_shared<Sound::Source>(buff);
	//streamer->checkQueue();
	auto tester = std::make_shared<Sound::Sinewave>(1200.0f,1.0f/48000.0f);
	Driver::SDL audioDev(48000,2,2048);
	auto mixer = std::make_shared<Audio::Mixer>(1000,audioDev.getFreq(),audioDev.getChannels()) ;
	audioDev.setPlayable(mixer);
	mixer->insert(streamer,0.5f);
	mixer->insert(snd,0.5f);
	streamer->play();
	snd->play();
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
