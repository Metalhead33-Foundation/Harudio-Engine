#include "Sound/SoundModulePlayer.hpp"
namespace Sound {

    ModulePlayer::ModulePlayer( Abstract::sFIO fio ) : mod( fio ) {}

    ModulePlayer::ModulePlayer( ModulePlayer &&mov )
        : mod( std::move( mov.mod ) ) {}

    void ModulePlayer::operator=( ModulePlayer &&mov ) {
        this->mod = std::move( mov.mod );
    }

    Audio::FrameCount ModulePlayer::outputTo( const Audio::Output &dst ) {
        if ( state != Status::PLAYING )
			return Audio::FrameCount::Zero();
		Audio::FrameCount readFrames = Audio::FrameCount::Zero();
        if ( dst.interleavingType == Audio::InterleavingType::INTERLEAVED ) {
            switch ( dst.channelCnt ) {
            case 1:
				readFrames.value =
                    mod.readMono( dst.frameRate, dst.frameCnt, dst.dst );
                break;
            case 2:
				readFrames.value = mod.readInterleavedStereo( dst.frameRate,
                                                        dst.frameCnt, dst.dst );
                break;
            case 4:
				readFrames.value = mod.readInterleavedQuad( dst.frameRate,
                                                      dst.frameCnt, dst.dst );
                break;
            default:
                break;
            }
        } else {
            switch ( dst.channelCnt ) {
            case 1:
				readFrames.value =
                    mod.readMono( dst.frameRate, dst.frameCnt, dst.dst );
                break;
            case 2:
				readFrames.value =
                    mod.readStereo( dst.frameRate, dst.frameCnt, &dst.dst[0],
                                    &dst.dst[dst.frameCnt] );
                break;
            case 4:
				readFrames.value = mod.readQuad( dst.frameRate, dst.frameCnt,
                                           &dst.dst[0], &dst.dst[dst.frameCnt],
                                           &dst.dst[dst.frameCnt * 2],
                                           &dst.dst[dst.frameCnt * 3] );
                break;
            default:
                break;
            }
        }
        if ( !readFrames ) {
            state = Status::STOPPED;
            mod.setPosition( 0.0 );
        }
        return readFrames;
    }

    ModulePlayer::Status ModulePlayer::getState( ) const { return state; }

    void ModulePlayer::play( ) {
        if ( state == Status::STOPPED ) {
            mod.setPosition( 0.0 );
        }
        state = Status::PLAYING;
    }

    void ModulePlayer::pause( ) {
        if ( state != Status::STOPPED )
            state = Status::PAUSED;
    }

    void ModulePlayer::stop( ) {
        state = Status::STOPPED;
        mod.setPosition( 0.0 );
    }

    bool ModulePlayer::isLooping( ) const { return mod.isRepeating( ); }

    void ModulePlayer::setLooping( bool looping ) {
        mod.setRepeating( looping );
    }

    double ModulePlayer::seek( double seconds,
                               Audio::Seekable::SeekPos whence ) {
        switch ( whence ) {
        case SeekPos::CUR:
            return mod.setPosition( mod.getPosition( ) + seconds );
        case SeekPos::SET:
            return mod.setPosition( seconds );
        case SeekPos::END:
            return mod.setPosition( mod.getDuration( ) - seconds );
        }
        return 0;
    }

    double ModulePlayer::tell( ) const { return mod.getPosition( ); }

    double ModulePlayer::size( ) const { return mod.getDuration( ); }

} // namespace Sound
