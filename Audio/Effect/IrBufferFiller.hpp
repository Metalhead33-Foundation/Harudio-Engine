#ifndef IRBUFFERFILLER_HPP
#define IRBUFFERFILLER_HPP
#include <functional>
#include <vector>

struct IrBuffer {
	float* audio;
	size_t sampleCount;
};
typedef std::function<void(IrBuffer&)> IrBufferFiller;
typedef std::function<void(std::vector<float>&)> IrBufferCreator;

#endif // IRBUFFERFILLER_HPP
