#ifndef CONVOLVER_HPP
#define CONVOLVER_HPP
#include "../AudioBuffer.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(Convolver)
DEFINE_STRUCT(Convolver_private)
class Convolver
{
private:
	uConvolver_private impl;
public:
	Convolver(size_t blocksize);
	Convolver(size_t head, size_t tail);
	void reset(size_t blocksize);
	void reset(size_t head, size_t tail);
	void init(const sBuffer nIR);
	void init(const float* IR, size_t irSize);
	void init(const Convolver& cyp);
	void process(float* inBuffer, float* outBuffer, size_t sampleCount);
};

}
}
#endif // CONVOLVER_HPP
