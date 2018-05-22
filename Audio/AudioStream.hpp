#ifndef AUDIOSTREAM_HPP
#define AUDIOSTREAM_HPP
#include "AudioInputBuffer.hpp"

namespace Audio {

class Stream
{
private:
	PaStream *stream;
	const sInputBuffer buff;
public:
	Stream(const sInputBuffer nBuff, int samplerate, size_t buffsize);
	~Stream();
	void start();
	void stop();
	void abort();
	bool isStopped();
	bool isActive();
};

}
#endif // AUDIOSTREAM_HPP
