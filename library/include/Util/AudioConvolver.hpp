#ifndef AUDIOCONVOLVER_HPP
#define AUDIOCONVOLVER_HPP
#include <Abstract/AudioPlayable.hpp>
#include <Sound/SoundBuffer.hpp>
#include <fftw3.h>

namespace Audio {
class Convolver
{
private:
	SampleCount_T nc;
	SampleCount_T convSigLen;
	// Buffers
	Sound::sBuffer IR;
	DynamicBuffer inBuff;
	DynamicBuffer sigOnePadded;
	DynamicBuffer sigTwoPadded;
	ComplexBuffer outfftwOne;
	ComplexBuffer outfftwTwo;
	ComplexBuffer fftMulti;
	void convolve(const float *sigOne, SampleCount_T lenOne, float *convolvedSig);
public:
	Convolver(Sound::sBuffer&& mov, SampleCount_T sampleCnt);
	Convolver(const Sound::sBuffer& cpy, SampleCount_T sampleCnt);
	Convolver(Abstract::sFIO fio, SampleCount_T sampleCnt);
};
}

#endif // AUDIOCONVOLVER_HPP
