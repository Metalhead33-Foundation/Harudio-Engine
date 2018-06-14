#ifndef DEGRADER_HPP
#define DEGRADER_HPP
#include "../AudioEffect.hpp"
namespace Audio {
namespace FX {

DEFINE_CLASS(Degrader)
class Degrader : public Effect
{
protected:
	int lowEnd;
	Degrader(int nLowEnd);
public:
	static sDegrader create(int nLowEnd);
	int getLowEnd() const;
	void setLowEnd(int nLowEnd);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
};

}
}
#endif // DEGRADER_HPP
