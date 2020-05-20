#include "Sound/SoundStreamer.hpp"
#include "Abstract/AudioMismatchError.hpp"

namespace Sound {
    Streamer::Streamer( Mh::SoundfileWrapper &&mov )
        : buff( std::move( mov ) ), state( Status::STOPPED ) {}
    Streamer::Streamer( Abstract::sFIO fio )
        : buff( fio, true ), state( Status::STOPPED ) {}

    Audio::FrameCount Streamer::outputTo( const Audio::Output &dst ) {
        if ( state != Status::PLAYING )
			return Audio::FrameCount::Zero();
		if ( ( dst.frameRate != buff.getSamplerate( ) ) ||
             ( dst.channelCnt != buff.getChannels( ) ) ||
             ( dst.interleavingType != Audio::InterleavingType::DONT_CARE &&
               ( dst.interleavingType !=
                 Audio::InterleavingType::INTERLEAVED ) ) ) {
            throw Audio::MismatchError( dst.frameRate, buff.getSamplerate( ),
                                        dst.channelCnt, Audio::ChannelCount{buff.getChannels( )},
                                        dst.interleavingType,
                                        Audio::InterleavingType::INTERLEAVED );
        }
        const Audio::FrameCount readframes =
            Audio::FrameCount{ buff.readf( dst.dst, dst.frameCnt ) };
        if ( !readframes ) {
            if ( !looping )
                state = Status::STOPPED;
            buff.seekSet( 0 );
        }
        return readframes;
    }
    Streamer::Streamer( Streamer &&mov )
        : buff( std::move( mov.buff ) ), state( mov.state ) {
        mov.state = Status::STOPPED;
    }
    void Streamer::operator=( Streamer &&mov ) {
        this->buff = std::move( mov.buff );
        this->state = mov.state;
        mov.state = Status::STOPPED;
    }
    Streamer::Status Streamer::getState( ) const { return state; }

    void Streamer::play( ) {
        if ( state == Status::STOPPED ) {
            buff.seekSet( 0 );
        }
        state = Status::PLAYING;
    }

    void Streamer::pause( ) {
        if ( state != Status::STOPPED )
            state = Status::PAUSED;
    }

    void Streamer::stop( ) {
        state = Status::STOPPED;
        buff.seekSet( 0 );
    }

    bool Streamer::isLooping( ) const { return looping; }

    void Streamer::setLooping( bool looping ) { this->looping = looping; }

    double Streamer::seek( double seconds, SeekPos whence ) {
        switch ( whence ) {
        case SeekPos::SET:
            return double( buff.seekSet(
                       long( seconds * double( buff.getSamplerate( ) ) ) ) ) /
                   double( buff.getSamplerate( ) );
        case SeekPos::CUR:
            return double( buff.seekCur(
                       long( seconds * double( buff.getSamplerate( ) ) ) ) ) /
                   double( buff.getSamplerate( ) );
        case SeekPos::END:
            return double( buff.seekEnd(
                       long( seconds * double( buff.getSamplerate( ) ) ) ) ) /
                   double( buff.getSamplerate( ) );
        }
        return 0;
    }

    double Streamer::tell( ) const {
        return double( buff.seekCur( 0 ) ) / double( buff.getSamplerate( ) );
    }

    double Streamer::size( ) const {
        return double( buff.getFrameNum( ) ) / double( buff.getSamplerate( ) );
    }

} // namespace Sound
