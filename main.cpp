#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Io/StdStream.hpp"
#include <time.h>

using namespace std;

int main()
{
	Audio::Context context(44100,2,1024);
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 500;
	auto sndfile = StdStream::createReader("/tmp/dancso.ogg");
	auto stream = Sound::Streamer::create(sndfile,32000);
	context.unsuspend();
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
