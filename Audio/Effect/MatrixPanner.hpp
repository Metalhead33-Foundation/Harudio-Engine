#ifndef MATRIXPANNER_HPP
#define MATRIXPANNER_HPP
#include "../AudioEffect.hpp"
#include <stdexcept>
#include <glm/glm.hpp>
namespace Audio {
namespace FX {

template <int inputChannelCount, int outputChannelCount> class MatrixPanner : public Effect
{
private:
	const int matrixTotalSize = inputChannelCount * outputChannelCount;
	float matrix[inputChannelCount*outputChannelCount];
public:
	float* operator[](int row)
	{
		return &matrix[(row % inputChannelCount)*outputChannelCount];
	}
	static int rowAndColumn2Raw(int row, int column)
	{
		return ((row%inputChannelCount)*outputChannelCount)+(column%outputChannelCount);
	}
};

}
}
#endif // MATRIXPANNER_HPP
