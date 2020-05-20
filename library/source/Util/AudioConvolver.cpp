#include "Util/AudioConvolver.hpp"
#include <cstring>
#include <stdexcept>

namespace Audio {
    Audio::sPlayable Convolver::getPlayable( ) const {
        return playable.lock( );
    }

    void Convolver::setPlayable( const sPlayable &value ) { playable = value; }

    void Convolver::convolve( const float *sigOne, SampleCount lenOne,
                              float *convolvedSig ) {
        // zero-pad the dry signal
        for ( Sample i : convSigLen ) {
            sigOnePadded[i] = ( i < lenOne ) ? sigOne[i] : 0;
        }
        // create and execute forward FFT plans
        fftwf_plan forward_sigOne = fftwf_plan_dft_r2c_1d(
            convSigLen, sigOnePadded.data( ),
            reinterpret_cast< fftwf_complex * >( outfftwOne.data( ) ),
            FFTW_ESTIMATE );
        fftwf_execute( forward_sigOne );
        // Backward (inverse) FFT plan
        // Complex multiplication
        for ( Sample i : SampleCount{nc} ) {
            // real component
            fftMulti[i][0] = outfftwOne[i][0] * outfftwTwo[i][0] -
                             outfftwOne[i][1] * outfftwTwo[i][1];
            // imaginary component
            fftMulti[i][1] = outfftwOne[i][0] * outfftwTwo[i][1] +
                             outfftwOne[i][1] * outfftwTwo[i][0];
        }
        fftwf_plan backward_convolution = fftwf_plan_dft_c2r_1d(
            convSigLen, reinterpret_cast< fftwf_complex * >( fftMulti.data( ) ),
            convolvedSig, FFTW_ESTIMATE );
        fftwf_execute( backward_convolution );
        fftwf_destroy_plan( forward_sigOne );
        fftwf_destroy_plan( backward_convolution );
    }

    Convolver::Convolver( Sound::sBuffer &&mov, SampleCount sampleCnt )
        : IR( std::move( mov ) ), inBuff( sampleCnt ) {
        if ( !IR->getSampleCount( ) )
            throw std::runtime_error( "Invalid IR!" );
        this->convSigLen = IR->getSampleCount( ) + sampleCnt - SampleCount{1};
        nc = convSigLen / 2 + 1;
        sigOnePadded.resize( convSigLen );
        sigTwoPadded.resize( convSigLen );
        outfftwOne.resize( convSigLen );
        outfftwTwo.resize( convSigLen );
        fftMulti.resize( nc );
        convolved.resize( convSigLen );
        // zero-pad the IR signal
        auto lenTwo = IR->getSampleCount( );
        for ( Sample i : convSigLen ) {
            sigTwoPadded[i] = ( i < lenTwo ) ? ( *IR )[i] : 0;
        }
        fftwf_plan forward_sigTwo = fftwf_plan_dft_r2c_1d(
            convSigLen, sigTwoPadded.data( ),
            reinterpret_cast< fftwf_complex * >( outfftwTwo.data( ) ),
            FFTW_ESTIMATE );
        fftwf_execute( forward_sigTwo );
        fftwf_destroy_plan( forward_sigTwo );
    }
    Convolver::Convolver( const Sound::sBuffer &cpy, SampleCount sampleCnt )
        : IR( cpy ), inBuff( sampleCnt ) {
        if ( !IR->getSampleCount( ) )
            throw std::runtime_error( "Invalid IR!" );
        this->convSigLen = IR->getSampleCount( ) + sampleCnt - SampleCount{1};
        nc = convSigLen / 2 + 1;
        sigOnePadded.resize( convSigLen );
        sigTwoPadded.resize( convSigLen );
        outfftwOne.resize( convSigLen );
        outfftwTwo.resize( convSigLen );
        fftMulti.resize( nc );
        convolved.resize( convSigLen );
        // zero-pad the IR signal
        auto lenTwo = IR->getSampleCount( );
        for ( Sample i : convSigLen ) {
            sigTwoPadded[i] = ( i < lenTwo ) ? ( *IR )[i] : 0;
        }
        fftwf_plan forward_sigTwo = fftwf_plan_dft_r2c_1d(
            convSigLen, sigTwoPadded.data( ),
            reinterpret_cast< fftwf_complex * >( outfftwTwo.data( ) ),
            FFTW_ESTIMATE );
        fftwf_execute( forward_sigTwo );
        fftwf_destroy_plan( forward_sigTwo );
    }
    Convolver::Convolver( Abstract::sFIO fio, SampleCount sampleCnt )
        : Convolver( std::make_shared< Sound::Buffer >( fio ), sampleCnt ) {}

    FrameCount Convolver::outputTo( const Output &dst ) {
        if ( playable.expired( ) )
            return FrameCount::Zero();
        auto ptim = playable.lock( );
        Output toBuffer;
        toBuffer.dst = inBuff.data( );
        toBuffer.frameCnt = FrameCount{inBuff.size( )};
        toBuffer.frameRate = IR->getFramerate( );
        toBuffer.channelCnt = IR->getChannels( );
        toBuffer.interleavingType = Audio::InterleavingType::DONT_CARE;
        auto received = SampleCount{ptim->outputTo( toBuffer )};
        convolve( inBuff.data( ), received, convolved.data( ) );
        memcpy( dst.dst, convolved.data( ),
                 std::min( received, dst.frameCnt.toSamples(ChannelCount{1}) ).toBytes( ) );
        return  std::min( received, dst.frameCnt.toSamples(ChannelCount{1}) ).toFrames(ChannelCount{1});
    }

    bool Convolver::isPlaying( ) const {
        if ( playable.expired( ) )
            return 0;
        else
            return playable.lock( )->isPlaying( );
    }

} // namespace Audio
