#include "Util/AudioMixer.hpp"
#include "Abstract/AudioMismatchError.hpp"
#include <cstring>

namespace Audio {

    Mixer::Mixer( FrameCount nframeCnt, Framerate nframerate,
                  ChannelCount nchannelCnt )
        : frameCnt( nframeCnt ), framerate( nframerate ),
          channelCnt( nchannelCnt ), buffA( nframeCnt * nchannelCnt ) {}

    Mixer::Mixer( Mixer &&mov )
        : frameCnt( mov.frameCnt ), framerate( mov.framerate ),
          channelCnt( mov.channelCnt ), elements( std::move( mov.elements ) ),
          buffA( std::move( mov.buffA ) ) {
        mov.frameCnt = 0;
        mov.framerate = 0;
        mov.channelCnt = 0;
    }

    FrameCount Mixer::getFrameCnt( ) const { return frameCnt; }

    Framerate Mixer::getFramerate( ) const { return framerate; }

    ChannelCount Mixer::getChannelCnt( ) const { return channelCnt; }

    bool Mixer::getActive( ) const { return isActive; }

    void Mixer::setActive( bool value ) { isActive = value; }

    void Mixer::operator=( Mixer &&mov ) {
        this->elements = std::move( mov.elements );
        this->buffA = std::move( mov.buffA );
        this->frameCnt = mov.frameCnt;
        mov.frameCnt = 0;
        this->framerate = mov.framerate;
        mov.framerate = 0;
        this->channelCnt = mov.channelCnt;
        mov.channelCnt = 0;
    }

    FrameCount Mixer::outputTo( const Output &dst ) {
        if ( ( dst.frameRate != this->framerate ) ||
             ( dst.channelCnt != this->channelCnt ) ||
             ( dst.interleavingType != InterleavingType::DONT_CARE &&
               ( dst.interleavingType != InterleavingType::INTERLEAVED ) ) ) {
            throw MismatchError( dst.frameRate, this->framerate, dst.channelCnt,
                                 this->channelCnt, dst.interleavingType,
                                 InterleavingType::INTERLEAVED );
        }
        if ( isActive && elements.size( ) ) {
            FrameCount toOutput = dst.frameCnt;
            FrameCount outFrames = 0;
            while ( toOutput ) {
                const FrameCount recFrames =
                    fillBuffers( toOutput, &dst.dst[outFrames * channelCnt] );
                if ( recFrames ) {
                    // memcpy(&dst.dst[outFrames*channelCnt],buffB.data(),framesToBytes(recFrames,channelCnt));
                    outFrames += recFrames;
                    toOutput -= recFrames;
                } else
                    break;
            }
            return outFrames;
        } else
            return 0;
    }

    bool Mixer::isPlaying( ) const {
        if ( isActive ) {
            if ( elements.size( ) ) {
                return true;
            } else
                return false;
        } else
            return false;
    }

    FrameCount Mixer::fillBuffers( FrameCount maxFrames, float *buffB ) {
        Output receiver;
        FrameCount finalFrameCnt = 0;
        receiver.dst = buffA.data( ); // Set pointer to receiving buffer
        receiver.frameCnt = std::min( maxFrames, frameCnt );
        receiver.frameRate = framerate;
        receiver.channelCnt = channelCnt;
        receiver.interleavingType = InterleavingType::INTERLEAVED;
        for ( auto it = std::begin( elements ); it != std::end( elements );
              ++it ) {
            if ( !it->first.expired( ) ) {
                auto source = it->first.lock( );
                if ( source->isPlaying( ) ) {
                    FrameCount receivedFrames = source->outputTo( receiver );
                    finalFrameCnt = std::max( finalFrameCnt, receivedFrames );
                    for ( FrameCount i = 0; i < receivedFrames; ++i ) {
                        const SampleCount index = i * channelCnt;
                        for ( ChannelCount j = 0; j < channelCnt; ++j )
                            buffB[index + j] += buffA[index + j] * it->second;
                    }
                }
            }
        }
        return finalFrameCnt;
    }

    void Mixer::setVolume( const sPlayable &playable, float nvolume ) {
        auto it = elements.find( playable );
        if ( it == std::end( elements ) ) {
            elements.emplace( playable, nvolume );
        } else {
            it->second = nvolume;
        }
    }

    Mixer::iterator Mixer::erase( Mixer::const_iterator deletable ) {
        return elements.erase( deletable );
    }

    float Mixer::getVolume( const sPlayable &playable ) const {
        auto it = elements.find( playable );
        if ( it == std::end( elements ) ) {
            return 0.0;
        } else {
            return it->second;
        }
    }

    float Mixer::isPresent( const sPlayable &playable ) const {
        auto it = elements.find( playable );
        if ( it == std::end( elements ) ) {
            return false;
        } else {
            return true;
        }
    }

    void Mixer::clearExpired( ) {
        for ( auto it = std::begin( elements ); it != std::end( elements ); ) {
            if ( it->first.expired( ) )
                it = elements.erase( it );
            else
                ++it;
        }
    }

    Mixer::iterator Mixer::begin( ) { return elements.begin( ); }
    Mixer::const_iterator Mixer::begin( ) const { return elements.begin( ); }
    Mixer::const_iterator Mixer::cbegin( ) const { return elements.cbegin( ); }
    Mixer::iterator Mixer::end( ) { return elements.end( ); }
    Mixer::const_iterator Mixer::end( ) const { return elements.end( ); }
    Mixer::const_iterator Mixer::cend( ) const { return elements.cend( ); }
    Mixer::reverse_iterator Mixer::rbegin( ) { return elements.rbegin( ); }
    Mixer::const_reverse_iterator Mixer::rbegin( ) const {
        return elements.rbegin( );
    }
    Mixer::const_reverse_iterator Mixer::crbegin( ) const {
        return elements.crbegin( );
    }
    Mixer::reverse_iterator Mixer::rend( ) { return elements.rend( ); }
    Mixer::const_reverse_iterator Mixer::rend( ) const {
        return elements.rend( );
    }
    Mixer::const_reverse_iterator Mixer::crend( ) const {
        return elements.crend( );
    }
    Mixer::iterator Mixer::find( const sPlayable &playable ) {
        return elements.find( playable );
    }
    Mixer::const_iterator Mixer::find( const sPlayable &playable ) const {
        return elements.find( playable );
    }
    void Mixer::insert( const sPlayable &playable, float nvolume ) {
        elements.emplace( playable, nvolume );
    }

} // namespace Audio
