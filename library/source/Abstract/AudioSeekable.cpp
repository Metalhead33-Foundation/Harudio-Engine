#include "Abstract/AudioSeekable.hpp"

namespace Audio {

bool Seekable::isPlaying() const
{
	return getState() == Status::PLAYING;
}

}
