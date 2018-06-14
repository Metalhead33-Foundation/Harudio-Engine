#include "Filter.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <vector>

template<typename T> double sinc(T a)
{
	if(a == 0.00) return 1.00;
	else return sin(a)/a;
}

template<typename T>
std::vector<T>
conv(std::vector<T> const &f, std::vector<T> const &g) {
  int const nf = f.size();
  int const ng = g.size();
  int const n  = nf + ng - 1;
  std::vector<T> out(n, T());
  for(auto i(0); i < n; ++i) {
	int const jmn = (i >= ng - 1)? i - (ng - 1) : 0;
	int const jmx = (i <  nf - 1)? i            : nf - 1;
	for(auto j(jmn); j <= jmx; ++j) {
	  out[i] += (f[j] * g[i - j]);
	}
  }
  return out;
}

template<typename T>
std::vector<T>
conv_valid(std::vector<T> const &f, std::vector<T> const &g) {
  int const nf = f.size();
  int const ng = g.size();
  std::vector<T> const &min_v = (nf < ng)? f : g;
  std::vector<T> const &max_v = (nf < ng)? g : f;
  int const n  = std::max(nf, ng) - std::min(nf, ng) + 1;
  std::vector<T> out(n, T());
  for(auto i(0); i < n; ++i) {
	for(int j(min_v.size() - 1), k(i); j >= 0; --j) {
	  out[i] += min_v[j] * max_v[k];
	  ++k;
	}
  }
  return out;
}

namespace Audio {
namespace FX {

enum FilterType : uint8_t
{
	lowpass,
	highpass,
	bandpass,
	bandreject
};

static void fillSingleFilter(std::vector<float>& vec, FilterType type, int inputSamplerate,int CutoffFrequency)
{
	const double fc = double(CutoffFrequency)/(double(inputSamplerate)/2.0);
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

	float h_sum = std::accumulate(vec.begin(), vec.end(), 0.0f);
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		switch(type)
		{
		case lowpass:
			*it /= h_sum;
			break;
		case highpass:
			*it /= h_sum;
			*it *= -1.0f;
			break;
		default:
			*it /= h_sum;
			break;
		}
	}
	if(type == highpass)
	{
		vec[(N - 1) / 2] += 1.0f;
	}
	const float divisor=1 / *std::max_element(vec.begin(),vec.end());
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		*it *= divisor;
	}
}
static void fillBandFilter(std::vector<float>& vec, FilterType type, int inputSamplerate,int lowCutoff,int highCutoff)
{
	const double fL = double(lowCutoff)/(double(inputSamplerate)/2.0);
	const double fH = double(highCutoff)/(double(inputSamplerate)/2.0);
	const double b = fH*0.8; // Transition band
	int N = int(std::ceil(4.0/b));

	if ((N % 2) == 0) N++;

	std::vector<int> n(N,0);

	std::iota(n.begin(), n.end(), 0);

	vec.resize(N);
	memset(vec.data(),0,sizeof(float)*vec.size());
	std::vector<float> lowpass(N);
	std::vector<float> highpass(N);
	memset(lowpass.data(),0,sizeof(float)*lowpass.size());
	memset(highpass.data(),0,sizeof(float)*highpass.size());

	/* Calculate passes */
	std::transform(n.begin(), n.end(), lowpass.begin(), [fH, b, N](int n){
		const double h = sinc(2.0 * fH * (n - (N - 1) / 2.0));

		const double w = 0.42 - 0.5 * std::cos(2 * M_PI * n / (N - 1)) +
			0.08 * std::cos(4 * M_PI * n / (N - 1));

		return float(h * w);

	});
	std::transform(n.begin(), n.end(), highpass.begin(), [fL, b, N](int n){
		const double h = sinc(2.0 * fL * (n - (N - 1) / 2.0));

		const double w = 0.42 - 0.5 * std::cos(2 * M_PI * n / (N - 1)) +
			0.08 * std::cos(4 * M_PI * n / (N - 1));

		return float(h * w);
	});

	float h_sum = std::accumulate(lowpass.begin(), lowpass.end(), 0.0f);
	for(auto it = lowpass.begin(); it != lowpass.end(); ++it)
	{
		*it /= h_sum;
	}
	h_sum = std::accumulate(highpass.begin(), highpass.end(), 0.0f);
	for(auto it = highpass.begin(); it != highpass.end(); ++it)
	{
		*it /= h_sum;
		*it *= -1.0f;
	}
	highpass[(N - 1) / 2] += 1.0f;

	switch(type)
	{
	case bandpass:
		vec = conv(lowpass,highpass);
		break;
	case bandreject:
		for(size_t i = 0; i < vec.size();++i) vec[i] = lowpass[i] + highpass[i];
		break;
	default:
		break;
	}
	const float divisor=1 / *std::max_element(vec.begin(),vec.end());
	for(auto it = vec.begin(); it != vec.end(); ++it)
	{
		*it *= divisor;
	}
}
sConvolver createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount)
{
	std::vector<float> vec;
	fillSingleFilter(vec,lowpass,inputSamplerate,CutoffFrequency);
	return Convolver::create(vec.data(),vec.size(),blocksiz,channelCount);
}
sTwoStageConvolver createTwoStageLowpassFilter(int inputSamplerate, int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount)
{
	std::vector<float> vec;
	fillSingleFilter(vec,lowpass,inputSamplerate,CutoffFrequency);
	return TwoStageConvolver::create(vec.data(),vec.size(),head_blocksize,tail_blocksize,channelCount);
}
sConvolver createHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount)
{
	std::vector<float> vec;
	fillSingleFilter(vec,highpass,inputSamplerate,CutoffFrequency);
	return Convolver::create(vec.data(),vec.size(),blocksiz,channelCount);
}
sTwoStageConvolver createTwoStageHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount)
{
	std::vector<float> vec;
	fillSingleFilter(vec,highpass,inputSamplerate,CutoffFrequency);
	return TwoStageConvolver::create(vec.data(),vec.size(),head_blocksize,tail_blocksize,channelCount);
}
// Bandpass filters
sConvolver createBandpassFilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t blocksiz, int channelCount)
{
	std::vector<float> vec;
	fillBandFilter(vec,bandpass,inputSamplerate,lowCutoff,highCutoff);
	return Convolver::create(vec.data(),vec.size(),blocksiz,channelCount);
}
sTwoStageConvolver createTwoStageBandpassFilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t head_blocksize, size_t tail_blocksize, int channelCount)
{
	std::vector<float> vec;
	fillBandFilter(vec,bandpass,inputSamplerate,lowCutoff,highCutoff);
	return TwoStageConvolver::create(vec.data(),vec.size(),head_blocksize,tail_blocksize,channelCount);
}
// Band-Rejject filters
sConvolver createBandRejectfilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t blocksiz, int channelCount)
{
	std::vector<float> vec;
	fillBandFilter(vec,bandreject,inputSamplerate,lowCutoff,highCutoff);
	return Convolver::create(vec.data(),vec.size(),blocksiz,channelCount);
}
sTwoStageConvolver createTwoStageBandRejectfilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t head_blocksize, size_t tail_blocksize, int channelCount)
{
	std::vector<float> vec;
	fillBandFilter(vec,bandreject,inputSamplerate,lowCutoff,highCutoff);
	return TwoStageConvolver::create(vec.data(),vec.size(),head_blocksize,tail_blocksize,channelCount);
}



}
}
