#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "../Audio/AudioSource.hpp"

namespace Sound {

DEFINE_CLASS(Source)
class Source : public Audio::Source
{
private:
	Audio::sBuffer buff;
protected:
	virtual long onBufferRequest(Audio::BufferOutput* ptr, long len);
	virtual void onBufferEnd(bool looping);
	Source(Audio::sBuffer nBuffer=nullptr);
public:
	static sSource create(Audio::sBuffer nBuffer=nullptr);
	const Audio::sBuffer getBuffer() const;
	void setBuffer(Audio::sBuffer nBuffer);
};

}

#endif // SOUNDSOURCE_HPP
