#ifndef AUDIOPLAYABLE_HPP
#define AUDIOPLAYABLE_HPP
#include "AudioPacket.hpp"
#include <Global/Global.hpp>

namespace Audio {
    DEFINE_CLASS( Playable )
    class Playable {
      public:
        virtual ~Playable( ) = default;
		virtual FrameCount outputTo( const Output &dst ) = 0;   // Return value: frames transmitted
        virtual bool isPlaying( ) const = 0; // Is this thing even on?
    };

} // namespace Audio

#endif // AUDIOPLAYABLE_HPP
