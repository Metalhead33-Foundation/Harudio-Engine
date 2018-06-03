#include <iostream>
#include "Audio/AudioContext.hpp"
#include "Sound/SoundStreamer.hpp"
#include "Sound/SoundSource.hpp"
#include "Io/StdStream.hpp"
#include <time.h>

using namespace std;

// /home/legacy/zene/others/Eurobeat/maybetonight.ogg
// /home/legacy/zene/Jmusic/flymesohigh.ogg

int main()
{
	std::cout << "Creating context!" << std::endl;
	Audio::Context context(44100,2,8000);
	std::cout << "Created context!" << std::endl;
	bool isPlaying = false;
	struct timespec tim, tim2;
	tim.tv_sec  = 0;
	tim.tv_nsec = 10000;
	auto sndfile = StdStream::createReader("/home/legacy/zene/others/Eurobeat/maybetonight.ogg");
	auto buffread = StdStream::createReader("/home/legacy/zene/others/99 Red Balloons - GoldFinger.ogg");
	auto buff = Audio::Buffer::create(buffread);
	auto stream = Sound::Streamer::create(sndfile,48000);
	auto src = Sound::Source::create(buff);
	context.addToList(stream);
	context.addToList(src);
	src->setLooping(true);
	stream->play();
	// src->play();
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
