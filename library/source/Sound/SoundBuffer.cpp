#include "Sound/SoundBuffer.hpp"
#include <cstring>

namespace Sound {

    Buffer::Buffer( Buffer &&mov )
        : buff( std::move( mov.buff ) ), framerate( mov.framerate ),
          channels( mov.channels ), totalFrames( mov.totalFrames ),
          interleavingType( mov.interleavingType ) {
    }
    Buffer::Buffer( const Buffer &cpy )
        : buff( cpy.buff ), framerate( cpy.framerate ),
          channels( cpy.channels ), totalFrames( cpy.totalFrames ),
          interleavingType( cpy.interleavingType ) {}
    void Buffer::operator=( Buffer &&mov ) {
        this->buff = std::move( mov.buff );
        this->framerate = mov.framerate;
        this->channels = mov.channels;
        this->interleavingType = mov.interleavingType;
        mov.interleavingType = Audio::InterleavingType::DONT_CARE;
        this->totalFrames = mov.totalFrames;
    }
    void Buffer::operator=( const Buffer &cpy ) {
        this->buff = cpy.buff;
        this->framerate = cpy.framerate;
        this->channels = cpy.channels;
        this->interleavingType = cpy.interleavingType;
        this->totalFrames = cpy.totalFrames;
    }

    Audio::Framerate Buffer::getFramerate( ) const { return framerate; }
    Audio::ChannelCount Buffer::getChannels( ) const { return channels; }

    Audio::FrameCount Buffer::getFrameCount( ) const { return totalFrames; }

    Audio::SampleCount Buffer::getSampleCount( ) const {
		return {static_cast<Audio::SampleCount::Type >(buff.size( ))};
    }

    Buffer::Buffer( Audio::DynamicBuffer &&mov, Audio::Framerate nframerate,
                    Audio::ChannelCount nchannelcnt,
                    Audio::InterleavingType ninterleavingType )
        : buff( mov ), framerate( nframerate ), channels( nchannelcnt ),
            totalFrames{static_cast<Audio::FrameCount::Type >(buff.size( ) / channels)},interleavingType( ninterleavingType ) {

    }
    Buffer::Buffer( const Audio::DynamicBuffer &cpy,
                    Audio::Framerate nframerate,
                    Audio::ChannelCount nchannelcnt,
                    Audio::InterleavingType ninterleavingType )
        : buff( cpy ), framerate( nframerate ), channels( nchannelcnt ),
          totalFrames{static_cast<Audio::FrameCount::Type >(buff.size( ) / channels)},interleavingType( ninterleavingType ) {
    }
    Buffer::Buffer( const float *src, Audio::FrameCount nframes,
                    Audio::Framerate nframerate,
                    Audio::ChannelCount nchannelcnt,
                    Audio::InterleavingType ninterleavingType )
        : buff( nframes * nchannelcnt ), framerate( nframerate ),
          channels( nchannelcnt ), totalFrames( nframes ),
          interleavingType( ninterleavingType ) {
		memcpy( buff.data( ), src, nframes.toBytes(channels ) );
    }

    Buffer::Buffer( const Mh::SoundfileWrapper &soundfile ) :
		framerate{Audio::Framerate::Type( soundfile.getSamplerate( ) )},
                channels{Audio::ChannelCount::Type( soundfile.getChannels( ) )},
                totalFrames{Audio::FrameCount::Type( soundfile.getFrameNum( ) )},
        interleavingType{Audio::InterleavingType::INTERLEAVED} {
        Audio::DynamicBuffer tmpbuff(
            std::size_t( this->totalFrames * this->channels ) );
        soundfile.readf( tmpbuff.data( ), this->totalFrames );
        this->buff = std::move( tmpbuff );
    }

    void Buffer::setInput( Audio::Input &dst,
                           Audio::FrameCount cursor ) const {
        if ( cursor >= totalFrames ) {
            dst = Audio::Input{};
        } else {
            dst.src = &buff[cursor * channels];
            dst.channelCnt = channels;
            dst.frameRate = framerate;
            dst.frameCnt = totalFrames - cursor;
            dst.interleavingType = interleavingType;
        }
    }

    float &Buffer::at( std::size_t index ) { return buff.at( index ); }
    const float &Buffer::at( std::size_t index ) const {
        return buff.at( index );
    }
    float &Buffer::operator[]( std::size_t index ) { return buff[index]; }
    const float &Buffer::operator[]( std::size_t index ) const {
        return buff[index];
    }
    float *Buffer::data( ) { return buff.data( ); }
    const float *Buffer::data( ) const { return buff.data( ); }

    Buffer::iterator Buffer::begin( ) { return buff.begin( ); }
    Buffer::const_iterator Buffer::begin( ) const { return buff.begin( ); }
    Buffer::iterator Buffer::end( ) { return buff.end( ); }
    Buffer::const_iterator Buffer::end( ) const { return buff.end( ); }
    Buffer::reverse_iterator Buffer::rbegin( ) { return buff.rbegin( ); }
    Buffer::const_reverse_iterator Buffer::rbegin( ) const {
        return buff.rbegin( );
    }
    Buffer::reverse_iterator Buffer::rend( ) { return buff.rend( ); }
    Buffer::const_reverse_iterator Buffer::rend( ) const {
        return buff.rend( );
    }

} // namespace Sound
