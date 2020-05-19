#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP
#include <Global/FftwMallocator.hpp>
#include <array>
#include <vector>

namespace Audio {

using DynamicBuffer = std::vector<float,FftwMallocator<float>>;
//using DynamicBuffer = std::vector<float>;
template<std::size_t Q> using StaticBuffer = std::array<float,Q>;

}
#endif // AUDIOBUFFER_HPP
