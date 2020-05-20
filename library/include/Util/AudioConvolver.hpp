#ifndef AUDIOCONVOLVER_HPP
#define AUDIOCONVOLVER_HPP
#include <Abstract/AudioPlayable.hpp>
#include <Sound/SoundBuffer.hpp>
#include <fftw3.h>

namespace Audio {
    class Convolver : public Playable {
      private:
        SampleCount nc;
        SampleCount convSigLen;
        Audio::wPlayable playable;
        // Buffers
        Sound::sBuffer IR;
        DynamicBuffer inBuff;
        DynamicBuffer sigOnePadded;
        DynamicBuffer sigTwoPadded;
        ComplexBuffer outfftwOne;
        ComplexBuffer outfftwTwo;
        ComplexBuffer fftMulti;
        DynamicBuffer convolved;
        void convolve( const float *sigOne, SampleCount lenOne,
                       float *convolvedSig );

      public:
        Convolver( Sound::sBuffer &&mov, SampleCount sampleCnt );
        Convolver( const Sound::sBuffer &cpy, SampleCount sampleCnt );
        Convolver( Abstract::sFIO fio, SampleCount sampleCnt );
        FrameCount
        outputTo( const Output &dst ); // Return value: frames transmitted
        bool isPlaying( ) const;       // Is this thing even on?
        Audio::sPlayable getPlayable( ) const;
        void setPlayable( const Audio::sPlayable &value );
    };
} // namespace Audio

#endif // AUDIOCONVOLVER_HPP
