#ifndef SOUNDSINEWAVE_HPP
#define SOUNDSINEWAVE_HPP
#include <Abstract/AudioPlayable.hpp>

namespace Sound {
    DEFINE_CLASS( Sinewave )
    class Sinewave : public Audio::Playable {
      private:
        float b, T, sinTb, cosTb2;
        float x[2];
        float y[3];
        void calculateForBnT( );

      public:
        Sinewave( float nb, float nT );
        float getB( ) const;
        void setB( float value );
        float getT( ) const;
        void setT( float value );
        void setBnT( float nB, float nT );

        Audio::FrameCount outputTo(
            const Audio::Output &dst ); // Return value: frames transmitted
        bool isPlaying( ) const;        // Is this thing even on?
    };
} // namespace Sound

#endif // SOUNDSINEWAVE_HPP
