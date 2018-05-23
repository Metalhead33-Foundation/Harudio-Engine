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
	virtual void onBufferRequest();
public:
	Source(Audio::sBuffer nBuffer=nullptr);
	const Audio::sBuffer getBuffer() const;
	void setBuffer(Audio::sBuffer nBuffer);
};

}

#endif // SOUNDSOURCE_HPP
