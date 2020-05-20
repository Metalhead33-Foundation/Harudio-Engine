#ifndef AUDIOCONVOLVER_HPP
#define AUDIOCONVOLVER_HPP
#include <Abstract/AudioPlayable.hpp>
#include <Sound/SoundBuffer.hpp>
#include <fftw3.h>

namespace Audio {
class Convolver : public Playable
{
private:
	SampleCount_T nc;
	SampleCount_T convSigLen;
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
	void convolve(const float *sigOne, SampleCount_T lenOne, float *convolvedSig);
public:
	Convolver(Sound::sBuffer&& mov, SampleCount_T sampleCnt);
	Convolver(const Sound::sBuffer& cpy, SampleCount_T sampleCnt);
	Convolver(Abstract::sFIO fio, SampleCount_T sampleCnt);
	FrameCount_T outputTo(const Output& dst); // Return value: frames transmitted
	bool isPlaying() const; // Is this thing even on?
	Audio::sPlayable getPlayable() const;
	void setPlayable(const Audio::sPlayable &value);
};
}

#endif // AUDIOCONVOLVER_HPP