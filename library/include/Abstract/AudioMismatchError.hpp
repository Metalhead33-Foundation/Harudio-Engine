#ifndef AUDIOMISMATCHERROR_HPP
#define AUDIOMISMATCHERROR_HPP
#include "exception"
#include <Abstract/AudioPacket.hpp>
#include <string>

namespace Audio {

    class MismatchError : public std::exception {
      private:
        std::string errMsg;

      public:
        MismatchError( Framerate_T expectedFramerate,
                       Framerate_T receivedFramerate,
                       ChannelCount_T expectedChannelCnt,
                       ChannelCount_T receivedChannelCnt,
                       InterleavingType expectedInterleavingType,
                       InterleavingType receivedInterleavingType );
        char const *what( ) const noexcept;
    };
} // namespace Audio

#endif // AUDIOMISMATCHERROR_HPP
