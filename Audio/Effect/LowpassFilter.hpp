#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "../AudioEffect.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(LowpassFilter)
class LowpassFilter : public Effect
{
protected:
	int lowEnd;
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	LowpassFilter(int nLowEnd);
public:
	static sLowpassFilter create(int nLowEnd);
	int getLowEnd() const;
	void setLowEnd(int nLowEnd);
};

}
}
#endif // LOWPASSFILTER_HPP
