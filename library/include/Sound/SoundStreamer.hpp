#ifndef SOUNDSTREAMER_HPP
#define SOUNDSTREAMER_HPP
#include <Abstract/AudioSeekable.hpp>
#include <Mh/SoundfileWrapper.hpp>

namespace Sound {
    DEFINE_CLASS( Streamer )
    class Streamer : public Audio::Seekable {
      protected:
        void
        receiveInput( Audio::Input &src ) const; // Gain access to the buffer
        void outputFeedback(
            Audio::FrameCount_T frames ); // Needed for things like advancing
                                          // the a ringbuffer's pointer
      private:
        Mh::SoundfileWrapper buff;
        Status state;
        bool looping;
        Streamer( const Streamer &cpy ) = delete;       // Copying disabled
        void operator=( const Streamer &cpy ) = delete; // Copying disabled
      public:
        Streamer( Mh::SoundfileWrapper &&mov );
        Streamer( Abstract::sFIO fio );
        Audio::FrameCount_T outputTo(
            const Audio::Output &dst );   // Return value: frames transmitted
        Streamer( Streamer &&mov );       // Move constructor
        void operator=( Streamer &&mov ); // Move assignment

        Status getState( ) const;
        void play( );
        void pause( );
        void stop( );
        bool isLooping( ) const;
        void setLooping( bool looping );

        double seek( double seconds, SeekPos whence = SeekPos::SET );
        double tell( ) const;
        double size( ) const;
    };
} // namespace Sound

#endif // SOUNDSTREAMER_HPP
