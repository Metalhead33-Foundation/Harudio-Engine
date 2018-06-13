#include "LowpassFilter.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>

template<typename T> double sinc(T a)
{
	if(a == 0.00) return 1.00;
	else return sin(a)/a;
}

namespace Audio {
namespace FX {

static void fillLowpassFilter(std::vector<float>& vec, int inputSamplerate,int CutoffFrequency)
{
	const double fc = double(CutoffFrequency)/double(inputSamplerate);
	const double b = fc*0.8;
	int N = int(std::ceil(4.0/b));

	if ((N % 2) == 0) N++;

	std::vector<int> n(N,0);

	std::iota(n.begin(), n.end(), 0);

	vec.resize(N);
	memset(vec.data(),0,sizeof(float)*vec.size());

	std::transform(n.begin(), n.end(), vec.begin(), [fc, b, N](int n){
		const double h = sinc(2.0 * fc * (n - (N - 1) / 2.0));

		const double w = 0.42 - 0.5 * std::cos(2 * M_PI * n / (N - 1)) +
			0.08 * std::cos(4 * M_PI * n / (N - 1));

		return float(h * w);
	});

	float h_sum = std::accumulate(vec.begin(), vec.end(), 0.0);

	std::for_each(vec.begin(), vec.end(), [h_sum](float h) {
		return h / h_sum;
	});
}
sConvolver createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount)
{
	std::vector<float> vec;
	fillLowpassFilter(vec,inputSamplerate,CutoffFrequency);
	return Convolver::create(vec.data(),vec.size(),blocksiz,channelCount);
}
sTwoStageConvolver createTwoStageLowpassFilter(int inputSamplerate, int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount)
{
	std::vector<float> vec;
	fillLowpassFilter(vec,inputSamplerate,CutoffFrequency);
	return TwoStageConvolver::create(vec.data(),vec.size(),head_blocksize,tail_blocksize,channelCount);
}

}
}
