#include "Convolver.hpp"
#include "../FFTConvolver/FFTConvolver.h"
#include "../FFTConvolver/TwoStageFFTConvolver.h"
#include <vector>

namespace Audio {
namespace FX {

struct Convolver_private
{
	virtual ~Convolver_private() = default;
	Convolver_private()
	{
		;
	}
	virtual void init(const sBuffer nIR) = 0;
	virtual void init(const float* IR, size_t irSize) = 0;
	virtual void init(const fftconvolver::FFTConvolver& conv) = 0;
	virtual void init(const Convolver_private& conv) = 0;
	virtual void process(float* inBuffer, float* outBuffer, size_t sampleCount) = 0;
	virtual const fftconvolver::FFTConvolver& getReference() const = 0;
};

struct NormalSimpleConvolver : public Convolver_private
{
	fftconvolver::FFTConvolver conv;
	const size_t blockSize;
	void init(const sBuffer nIR)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv.init(blockSize,ptr.first,ptr.second);
	}
	void init(const float* IR, size_t irSize)
	{
		conv.init(blockSize,IR,irSize);
	}
	void init(const fftconvolver::FFTConvolver& conv)
	{
		this->conv.init(blockSize,conv.getBuffer());
	}
	void init(const Convolver_private& conv)
	{
		init(conv.getReference());
	}
	void process(float* inBuffer, float* outBuffer, size_t sampleCount)
	{
		conv.process(inBuffer,outBuffer,sampleCount);
	}
	const fftconvolver::FFTConvolver& getReference() const
	{
		return conv;
	}
	NormalSimpleConvolver(size_t blocksize)
		: blockSize(blocksize)
	{
		;
	}
};

struct TwoStageSimpleConvolver : public Convolver_private
{
	fftconvolver::TwoStageFFTConvolver conv;
	const size_t head, tail;
	void init(const sBuffer nIR)
	{
		BufferOutput ptr;
		nIR->getAudioData(&ptr,0);
		conv.init(head,tail,ptr.first,ptr.second);
	}
	void init(const float* IR, size_t irSize)
	{
		conv.init(head,tail,IR,irSize);
	}
	void init(const fftconvolver::FFTConvolver& conv)
	{
		this->conv.init(head,tail,conv);
	}
	void init(const Convolver_private& conv)
	{
		init(conv.getReference());
	}
	void process(float* inBuffer, float* outBuffer, size_t sampleCount)
	{
		conv.process(inBuffer,outBuffer,sampleCount);
	}
	const fftconvolver::FFTConvolver& getReference() const
	{
		return conv.getHead();
	}
	TwoStageSimpleConvolver(size_t head, size_t tail)
		: head(head), tail(tail)
	{
		;
	}
};

Convolver::Convolver(size_t blocksize)
: impl(new NormalSimpleConvolver(blocksize))
{
	;
}
Convolver::Convolver(size_t head, size_t tail)
: impl(new TwoStageSimpleConvolver(head,tail))
{
	;
}
void Convolver::reset(size_t blocksize)
{
	impl = uConvolver_private(new NormalSimpleConvolver(blocksize));
}
void Convolver::reset(size_t head, size_t tail)
{
	impl = uConvolver_private(new TwoStageSimpleConvolver(head,tail));
}
void Convolver::init(const sBuffer nIR)
{
	impl->init(nIR);
}
void Convolver::init(const float* IR, size_t irSize)
{
	impl->init(IR,irSize);
}
void Convolver::init(const Convolver& cyp)
{
	impl->init(*cyp.impl);
}
void Convolver::process(float* inBuffer, float* outBuffer, size_t sampleCount)
{
	impl->process(inBuffer,outBuffer,sampleCount);
}

}
}
