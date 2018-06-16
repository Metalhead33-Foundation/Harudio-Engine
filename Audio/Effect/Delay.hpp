#ifndef DELAY_HPP
#define DELAY_HPP
#include "../AudioEffect.hpp"
#include <vector>
namespace Audio {
namespace FX {

DEFINE_STRUCT(Delay_private)
DEFINE_CLASS(Delay)
class Delay : public Effect
{
private:
	const uDelay_private impl;
	Delay(size_t blocksize, size_t offset, int channelCount);
	Delay(size_t head, size_t tail, size_t offset, int channelCount);
public:
	static sDelay create(size_t blocksize, size_t offset, int channelCount);
	static sDelay create(size_t head, size_t tail, size_t offset, int channelCount);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	size_t getSampleOffset() const;
	void setSampleOffset(size_t setto);
};

}
}
#endif // DELAY_HPP
