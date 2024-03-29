#ifndef SOUNDBUFFER_HPP
#define SOUNDBUFFER_HPP
#include <Abstract/AudioBuffer.hpp>
#include <Abstract/AudioPacket.hpp>
#include <Mh/SoundfileWrapper.hpp>

namespace Sound {
    DEFINE_CLASS( Buffer )
    class Buffer {
      private:
        Audio::DynamicBuffer buff;
        Audio::Framerate framerate;
        Audio::ChannelCount channels;
        Audio::FrameCount totalFrames;
        Audio::InterleavingType interleavingType;

      public:
        typedef Audio::DynamicBuffer::iterator iterator;
        typedef Audio::DynamicBuffer::const_iterator const_iterator;
        typedef Audio::DynamicBuffer::reverse_iterator reverse_iterator;
        typedef Audio::DynamicBuffer::const_reverse_iterator
            const_reverse_iterator;

        Buffer( Audio::DynamicBuffer &&mov, Audio::Framerate nframerate,
                Audio::ChannelCount nchannelcnt,
                Audio::InterleavingType ninterleavingType );
        Buffer( const Audio::DynamicBuffer &cpy, Audio::Framerate nframerate,
                Audio::ChannelCount nchannelcnt,
                Audio::InterleavingType ninterleavingType );
        Buffer( const float *src, Audio::FrameCount nframes,
                Audio::Framerate nframerate,
                Audio::ChannelCount nchannelcnt,
                Audio::InterleavingType ninterleavingType );
        Buffer( const Mh::SoundfileWrapper &soundfile );
        // Copy and move constructors + assignments
        Buffer( Buffer &&mov );
        Buffer( const Buffer &cpy );
        void operator=( Buffer &&mov );
        void operator=( const Buffer &cpy );
        // Functions
        void setInput( Audio::Input &dst, Audio::FrameCount cursor ) const;
        // Getters
        Audio::Framerate getFramerate( ) const;
        Audio::ChannelCount getChannels( ) const;
        Audio::FrameCount getFrameCount( ) const;
        Audio::SampleCount getSampleCount( ) const;
        // Iterator stuff - necessary for convolution later down the line
        float &at( std::size_t index );
        const float &at( std::size_t index ) const;
        float &operator[]( std::size_t index );
        const float &operator[]( std::size_t index ) const;
        float *data( );
        const float *data( ) const;

        iterator begin( );
        const_iterator begin( ) const;
        iterator end( );
        const_iterator end( ) const;
        reverse_iterator rbegin( );
        const_reverse_iterator rbegin( ) const;
        reverse_iterator rend( );
        const_reverse_iterator rend( ) const;
    };
} // namespace Sound

#endif // SOUNDBUFFER_HPP
