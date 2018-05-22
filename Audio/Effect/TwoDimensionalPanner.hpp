#ifndef TWODIMENSIONALPANNER_HPP
#define TWODIMENSIONALPANNER_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

class TwoDimensionalPanner : public Effect
{
private:
	float balance;
	float inverseBalance;
	float compensator;
	int inputChannelCount;
protected:
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
public:
	TwoDimensionalPanner();
	float getBalance() const;
	void setBalance(float newBalance);
	int getInputChannelCount() const;
	void setInputChannelCount(int newChannelCount);
};

}
}

#endif // TWODIMENSIONALPANNER_HPP
