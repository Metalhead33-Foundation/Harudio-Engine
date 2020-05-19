#include <iostream>
#include "Driver/SDL.hpp"
#include "Util/AudioMixer.hpp"
#include "Sound/SoundModulePlayer.hpp"
#include "Sound/SoundSinewave.hpp"
#include "Global/StdStream.hpp"

using namespace std;

const char* sharedDig = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/dig.s3m";
const char* Title = "/home/legacy/zene/GameMusic/Unreal Tournament/mod/02 - Flight Castle (Unreal Menu) [Alexander Brandon].it";

int main()
{
	std::string str2;
	SDL_Init(SDL_INIT_AUDIO);
	Abstract::sFIO stream(new StdStream(Title,true));
	auto mod = std::make_shared<Sound::ModulePlayer>(stream);
	auto tester = std::make_shared<Sound::Sinewave>(1200.0f,1.0f/48000.0f);
	Driver::SDL audioDev(48000,2,2048);
	auto mixer = std::make_shared<Audio::Mixer>(1000,audioDev.getFreq(),audioDev.getChannels()) ;
	audioDev.setPlayable(mixer);
	mixer->insert(mod,0.5f);
	//mixer->insert(tester,0.1f);
	mixer->setActive(true);
	audioDev.pause(false);
	cout << "Hello World!" << endl;
	cin >> str2;
	SDL_Quit();
	return 0;
}
