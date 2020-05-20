#include "Driver/SDL.hpp"
#include "Global/StdStream.hpp"
#include "Sound/SoundModulePlayer.hpp"
#include "Sound/SoundSinewave.hpp"
#include "Sound/SoundSource.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Util/AudioConvolver.hpp"
#include "Util/AudioMixer.hpp"
#include <iostream>

using namespace std;

const char *sharedDig = "extra/05 - Shared Dig [Alexander Brandon].s3m";
const char *Title =
    "extra/02 - Flight Castle (Unreal Menu) [Alexander Brandon].it";
const char *digging =
    "extraSoul Reaver - Ozar Midrashim 20th Anniversary Cover-9f9wiAiu_8E.ogg";
const char *starwars_ogg = "extra/rjedi_select.ogg";
const char *starwars_opus = "extra/rjedi_select.opus";
const char *motika = "extra/Motika.opus";
const char *blastereo_wav = "extra/blastereo.wav";
const char *blastereo_ogg = "extra/blastereo.ogg";
const char *blastereo_opus = "extra/blastereo.opus";
const char *IR = "extra/eloxl-wav01.wav";

int main( ) {
    std::string str2;
    SDL_Init( SDL_INIT_AUDIO );
    Abstract::sFIO stream1( new StdStream( sharedDig, true ) );
    Abstract::sFIO irstream( new StdStream( IR, true ) );
    auto mod = std::make_shared< Sound::ModulePlayer >( stream1 );
    auto convolver = std::make_shared< Audio::Convolver >( irstream, Audio::SampleCount{1024} );
    // streamer->checkQueue();
    auto tester =
        std::make_shared< Sound::Sinewave >( 1200.0f, 1.0f / 48000.0f );
    Driver::SDL audioDev( 48000, 1, 2048 );
    auto mixer = std::make_shared< Audio::Mixer >( Audio::FrameCount{1000U}, Audio::Framerate{audioDev.getFreq( )},
                                                   Audio::ChannelCount{audioDev.getChannels( )} );
    audioDev.setPlayable( mixer );
    convolver->setPlayable( mod );
	mixer->insert( mod, 0.5f );
    mod->play( );
    // streamer->play();
    // mixer->insert(tester,0.1f);
    mixer->setActive( true );
    audioDev.pause( false );
    cout << "Hello World!" << endl;
    /*do {
            SDL_Delay(1000);
            streamer->checkQueue();
    } while(true);*/
    cin >> str2;
    SDL_Quit( );
    return 0;
}
