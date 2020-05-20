#include "Sound/SoundSinewave.hpp"
#include <cmath>

namespace Sound {
    float Sinewave::getB( ) const { return b; }

    void Sinewave::setB( float value ) {
        b = value;
        calculateForBnT( );
    }

    float Sinewave::getT( ) const { return T; }

    void Sinewave::setT( float value ) {
        T = value;
        calculateForBnT( );
    }

    void Sinewave::setBnT( float nB, float nT ) {
        b = nB;
        T = nT;
        calculateForBnT( );
    }

    Audio::FrameCount Sinewave::outputTo( const Audio::Output &dst ) {
		for ( Audio::FrameCount i = {0}; i < dst.frameCnt; ++i ) {
			const Audio::SampleCount index = {i * dst.channelCnt};
            y[0] = ( sinTb * x[1] ) + ( cosTb2 * y[1] ) - y[2];
			for ( Audio::ChannelCount j = {0}; j < dst.channelCnt; ++j ) {
                dst.dst[index + j] = y[0];
            }
            x[1] = x[0];
            x[0] = 0.0f;
            y[2] = y[1];
            y[1] = y[0];
        }
        return dst.frameCnt;
    }

    bool Sinewave::isPlaying( ) const { return true; }

    void Sinewave::calculateForBnT( ) {
        const float bxT = b * T;
        sinTb = std::sin( bxT );
        cosTb2 = std::cos( bxT ) * 2.0f;
    }

    Sinewave::Sinewave( float nb, float nT ) : b( nb ), T( nT ) {
        calculateForBnT( );
        y[0] = 0.0f;
        y[1] = 0.0f;
        y[2] = 0.0f;
        x[0] = 1.0f;
        x[1] = 0.0f;
    }
} // namespace Sound
