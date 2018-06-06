#include "Convolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include <cstring>
#include <stdexcept>
#include <cmath>
#include <numeric>
#include <vector>

template<typename T> double sinc(T a)
{
	if(a == 0.00) return 1.00;
	else return sin(a)/a;
}

namespace Audio {
namespace FX {

Convolver::Convolver(const Convolver& cpy)
	: convolvers(cpy.convolvers.size())
{
	for(size_t i = 0; i < cpy.convolvers.size();++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
Convolver::Convolver(const Convolver& cpy, int channelCount)
	: convolvers(channelCount)
{
	if(channelCount <= 0) throw std::runtime_error("Convolved - invalid number of channels!");
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(*cpy.convolvers[0]);
	}
}
Convolver::Convolver(const sBuffer nIR, size_t blocksize, int channelCount)
	: convolvers(channelCount)
{
	if(channelCount <= 0) throw std::runtime_error("Convolved - invalid number of channels!");
	BufferOutput ptr;
	nIR->getAudioData(&ptr,0);
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(blocksize,ptr.first,ptr.second);
	}
}
Convolver::Convolver(const float* IR, size_t irSize, size_t blocksize, int channelCount)
	: convolvers(channelCount)
{
	if(channelCount <= 0) throw std::runtime_error("Convolved - invalid number of channels!");
	for(int i = 0; i < channelCount;++i)
	{
		convolvers[i] = fftconvolver::sFFTConvolver(new fftconvolver::FFTConvolver());
		convolvers[i]->init(blocksize,IR,irSize);
	}
}
sConvolver Convolver::create(sConvolver cpy)
{
	if(cpy) return sConvolver(new Convolver(*cpy));
	else return nullptr;
}
sConvolver Convolver::create(sConvolver cpy, int channelCount)
{
	if(cpy) return sConvolver(new Convolver(*cpy,channelCount));
	else return nullptr;
}
sConvolver Convolver::create(const sBuffer nIR, size_t blocksize, int channelCount)
{
	if(nIR) return sConvolver(new Convolver(nIR,blocksize,channelCount));
	else return nullptr;
}
sConvolver  Convolver::create(const float* IR, size_t irSize, size_t blocksize, int channelCount)
{
	return sConvolver(new Convolver(IR,irSize,blocksize,channelCount));
}
long Convolver::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	if(channelNum != convolvers.size()) throw std::runtime_error("Convolver - I/O Channel number mismatch! Please use a panner or channel mixer!");
	for(int i = 0; i < channelNum; ++i)
	{
		long sampleCursor=maxFrames*i;
		convolvers[i]->process(&inBuffer[sampleCursor],&outBuffer[sampleCursor],maxFrames);
	}
	return maxFrames;
}
sConvolver Convolver::create(IrBufferCreator& creator, size_t blocksiz, int channelCount)
{
	if(channelCount <= 0) return nullptr;
	std::vector<float> crt;
	creator(crt);
	return create(crt.data(),crt.size(),blocksiz,channelCount);
}
sConvolver Convolver::create(IrBufferFiller& creator, size_t blocksiz, int channelCount)
{
	if(channelCount <= 0) return nullptr;
	IrBuffer buff;
	creator(buff);
	return create(buff.audio,buff.sampleCount,blocksiz,channelCount);
}
sConvolver Convolver::createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount)
{
	const double fc = double(CutoffFrequency)/double(inputSamplerate);
	const double b = fc*0.8;
	int N = int(std::ceil(4.0/b));

	if ((N % 2) == 0) N++;

	std::vector<int> n(N,0);

	std::iota(n.begin(), n.end(), 0);

	std::vector<float> buff(N, 0.0);

	std::transform(n.begin(), n.end(), buff.begin(), [fc, b, N](int n){
		const double h = sinc(2.0 * fc * (n - (N - 1) / 2.0));

		const double w = 0.42 - 0.5 * std::cos(2 * M_PI * n / (N - 1)) +
			0.08 * std::cos(4 * M_PI * n / (N - 1));

		return float(h * w);
	});

	float h_sum = std::accumulate(buff.begin(), buff.end(), 0.0);

	std::for_each(buff.begin(), buff.end(), [h_sum](float h) {
		return h / h_sum;
	});
	return create(buff.data(),buff.size(),blocksiz,channelCount);
}
sConvolver Convolver::createFastLowpassFilter(int inputSamplerate,int outputFrequency, size_t blocksiz, int channelCount)
{
	std::vector<float> buff(blocksiz);
	// buff[0] = 1.0f;
	const double avg=double(inputSamplerate)/double(outputFrequency);
	for(size_t x=0;x<blocksiz;++x)
	{
		if(double(x) < std::ceil(avg))
			buff[x] = 1.0f / avg;
		else
			buff[x] = 0.0f;
	}
	return create(buff.data(),buff.size(),blocksiz,channelCount);
}

}
}
