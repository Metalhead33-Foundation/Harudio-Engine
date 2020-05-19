#include "Util/AudioConvolver.hpp"

namespace Audio {
void Convolver::convolve(const float *sigOne, SampleCount_T lenOne, float *convolvedSig)
{
	//zero-pad the dry signal
	for (SampleCount_T i = 0; i < convSigLen; i++)
	{
		sigOnePadded[i] = (i < lenOne) ? sigOne[i] : 0;
	}
	//create and execute forward FFT plans
	fftwf_plan forward_sigOne = fftwf_plan_dft_r2c_1d(convSigLen, sigOnePadded.data(), reinterpret_cast<fftwf_complex*>(outfftwOne.data()), FFTW_ESTIMATE);
	fftwf_execute(forward_sigOne);
	//Backward (inverse) FFT plan
	//Complex multiplication
	for (SampleCount_T i = 0; i < nc; i++ )
	{
		//real component
		fftMulti[i][0] = outfftwOne[i][0] * outfftwTwo[i][0] - outfftwOne[i][1] * outfftwTwo[i][1];
		//imaginary component
		fftMulti[i][1] = outfftwOne[i][0] * outfftwTwo[i][1] + outfftwOne[i][1] * outfftwTwo[i][0];
	}
	fftwf_plan backward_convolution = fftwf_plan_dft_c2r_1d(convSigLen, reinterpret_cast<fftwf_complex*>(fftMulti.data()), convolvedSig, FFTW_ESTIMATE);
	fftwf_execute(backward_convolution);
	fftwf_destroy_plan(forward_sigOne);
	fftwf_destroy_plan(backward_convolution);
}

Convolver::Convolver(Sound::sBuffer &&mov, SampleCount_T sampleCnt)
	: IR(std::move(mov)), inBuff(sampleCnt)
{
	this->convSigLen = IR->getSampleCount() + sampleCnt - 1;
	this->nc = convSigLen/2 + 1;
	sigOnePadded.resize(convSigLen);
	sigTwoPadded.resize(convSigLen);
	outfftwOne.resize(convSigLen);
	outfftwTwo.resize(convSigLen);
	fftMulti.resize(nc);
	//zero-pad the IR signal
	auto lenTwo = IR->getSampleCount();
	for (SampleCount_T i = 0; i < convSigLen; i++)
	{
		sigTwoPadded[i] = (i < lenTwo) ? (*IR)[i] : 0;
	}
	fftwf_plan forward_sigTwo = fftwf_plan_dft_r2c_1d(convSigLen, sigTwoPadded.data(), reinterpret_cast<fftwf_complex*>(outfftwTwo.data()), FFTW_ESTIMATE);
	fftwf_execute(forward_sigTwo);
	fftwf_destroy_plan(forward_sigTwo);
}
Convolver::Convolver(const Sound::sBuffer& cpy, SampleCount_T sampleCnt)
	: IR(cpy), inBuff(sampleCnt)
{
	this->convSigLen = IR->getSampleCount() + sampleCnt - 1;
	this->nc = convSigLen/2 + 1;
	sigOnePadded.resize(convSigLen);
	sigTwoPadded.resize(convSigLen);
	outfftwOne.resize(convSigLen);
	outfftwTwo.resize(convSigLen);
	fftMulti.resize(nc);
	//zero-pad the IR signal
	auto lenTwo = IR->getSampleCount();
	for (SampleCount_T i = 0; i < convSigLen; i++)
	{
		sigTwoPadded[i] = (i < lenTwo) ? (*IR)[i] : 0;
	}
	fftwf_plan forward_sigTwo = fftwf_plan_dft_r2c_1d(convSigLen, sigTwoPadded.data(), reinterpret_cast<fftwf_complex*>(outfftwTwo.data()), FFTW_ESTIMATE);
	fftwf_execute(forward_sigTwo);
	fftwf_destroy_plan(forward_sigTwo);
}
Convolver::Convolver(Abstract::sFIO fio, SampleCount_T sampleCnt)
	: Convolver(std::make_shared<Sound::Buffer>(fio),sampleCnt)
{

}

}
