#include "Abstract/AudioMismatchError.hpp"

namespace Audio {
	MismatchError::MismatchError( Framerate expectedFramerate,
								  Framerate receivedFramerate,
								  ChannelCount expectedChannelCnt,
								  ChannelCount receivedChannelCnt,
                                  InterleavingType expectedInterleavingType,
                                  InterleavingType receivedInterleavingType ) {
        errMsg = "Mismatch in audio attributes!\n";
        if ( expectedFramerate != receivedFramerate ) {
            errMsg +=
                "Expected framerate: " + static_cast<std::string>( expectedFramerate ) +
                "\n";
            errMsg +=
                "Received framerate: " + static_cast<std::string>( receivedFramerate ) +
                "\n";
        }
        if ( expectedChannelCnt != receivedChannelCnt ) {
            errMsg += "Expected framerate: " +
                      std::to_string( int( expectedChannelCnt ) ) + "\n";
            errMsg += "Received framerate: " +
                      std::to_string( int( receivedChannelCnt ) ) + "\n";
        }
        if ( ( expectedInterleavingType != InterleavingType::DONT_CARE ) &&
             ( expectedInterleavingType != receivedInterleavingType ) ) {
            switch ( expectedInterleavingType ) {
            case InterleavingType::INTERLACED:
                errMsg += "Expected interleaving type: Interlaced\n";
                break;
            case InterleavingType::INTERLEAVED:
                errMsg += "Expected interleaving type: Interleaved\n";
                break;
            case InterleavingType::DONT_CARE:
                errMsg += "Expected interleaving type: Unknown\n";
                break;
            }
            switch ( receivedInterleavingType ) {
            case InterleavingType::INTERLACED:
                errMsg += "Received interleaving type: Interlaced\n";
                break;
            case InterleavingType::INTERLEAVED:
                errMsg += "Received interleaving type: Interleaved\n";
                break;
            case InterleavingType::DONT_CARE:
                errMsg += "Received interleaving type: Unknown\n";
                break;
            }
        }
    }

    const char *MismatchError::what( ) const noexcept {
        return errMsg.c_str( );
    }
} // namespace Audio
