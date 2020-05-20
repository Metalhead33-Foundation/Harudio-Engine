#ifndef SDL_HPP
#define SDL_HPP
#include <Abstract/AudioPlayable.hpp>
#include <SDL2/SDL.h>

namespace Driver {

    class SDL {
      private:
        SDL_AudioDeviceID id;
        SDL_AudioSpec have;
        Audio::sPlayable playable;

      public:
        SDL( int freq, uint8_t channels, uint16_t frameCnt );
        ~SDL( );
        static void SDL_AudioCallback( void *userdata, Uint8 *stream, int len );
        void lock( );
        void unlock( );
        void pause( bool val );
        Audio::sPlayable getPlayable( ) const;
        void setPlayable( const Audio::sPlayable &value );
        int getFreq( ) const;
        Uint8 getChannels( ) const;
        Uint16 getSamples( ) const;
    };

} // namespace Driver

#endif // SDL_HPP
