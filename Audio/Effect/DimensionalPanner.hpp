#ifndef DIMENSIONALPANNER_HPP
#define DIMENSIONALPANNER_HPP
#include "Panner.hpp"
namespace Audio {
namespace FX {

template <int outputChannelCount> class DimensionalPanner : public Panner<outputChannelCount>
{
public:
	typedef Panner<outputChannelCount> baseType;
private:
	const int dimensions = outputChannelCount / 2;
	float balance[outputChannelCount / 2];
	float inverseBalance[outputChannelCount / 2];
	float compensator;
	void updateVolumes()
	{
		float largestCommonDenominator = 0.00f;
		for(int i = 0; i < dimensions; ++i)
		{
			largestCommonDenominator = std::max(balance[i],largestCommonDenominator);
			largestCommonDenominator = std::max(inverseBalance[i],largestCommonDenominator);
		}
		compensator = 1.00f - largestCommonDenominator;
		for(int i = 0; i < dimensions;++i)
		{
			int volumeCursor = dimensions * 2;
			setVolumeLevel(volumeCursor,inverseBalance[i] + compensator);
			setVolumeLevel(volumeCursor+1,balance[i] + compensator);
		}
	}
public:
	DimensionalPanner()
		: baseType()
	{
		;
	}
	DimensionalPanner(int inputChCount)
		: baseType(inputChCount)
	{
		;
	}
	float getDimension(int index)
	{
		return balance[index % dimensions];
	}
	void setDimension(int index, float newF)
	{
		balance[index % dimensions] = newF;
		updateVolumes();
	}
};
typedef DimensionalPanner<2> StereoDimensionalPanner;
typedef DimensionalPanner<4> QuadDimensionalPanner;

}
}
#endif // DIMENSIONALPANNER_HPP
