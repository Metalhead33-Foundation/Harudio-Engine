#ifndef AUDIOPLAYABLE_HPP
#define AUDIOPLAYABLE_HPP
#include <Global/Global.hpp>
#include "AudioPacket.hpp"

namespace Audio {
DEFINE_CLASS(Playable)
class Playable
{
public:
	virtual ~Playable() = default;
	virtual FrameCount_T outputTo(const Output& dst) = 0; // Return value: frames transmitted
	virtual bool isPlaying() const = 0; // Is this thing even on?
};

}

#endif // AUDIOPLAYABLE_HPP
