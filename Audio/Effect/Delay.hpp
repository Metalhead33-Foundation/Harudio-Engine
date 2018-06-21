#ifndef DELAY_HPP
#define DELAY_HPP
#include "ImpulseResponseGenerator.hpp"
namespace Audio {
namespace FX {

DEFINE_STRUCT(Delay_private)
DEFINE_CLASS(Delay)
class Delay : public ImpulseResponseGenerator
{
private:
	Delay(size_t offset,float delayVolume, int channelId=0,const sAdaptableConvolver setto=nullptr);
	void reset();
	size_t sampleOffset;
	float delayVolume;
public:
	static sDelay create(size_t offset,float delayVolume, int channelId=0,const sAdaptableConvolver setto=nullptr);
	size_t getSampleOffset() const;
	void setSampleOffset(size_t setto);
	float getDelayVolume() const;
	void setDelayVolume(float setto);
};

}
}
#endif // DELAY_HPP
