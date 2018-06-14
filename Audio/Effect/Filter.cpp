#include "Filter.hpp"
#include "Convolver.hpp"
#include "TwoStageConvolver.hpp"
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <vector>


namespace Audio {
namespace FX {

sLowpassFilter LowpassFilter::create(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency)
{
	return sLowpassFilter(new LowpassFilter(blockSize,channelNum,frameRate,CutoffFrequency));
}
sLowpassFilter LowpassFilter::create(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency)
{
	return sLowpassFilter(new LowpassFilter(tail,head,channelNum,frameRate,CutoffFrequency));
}
sHighpassFilter HighpassFilter::create(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency)
{
	return sHighpassFilter(new HighpassFilter(blockSize,channelNum,frameRate,CutoffFrequency));
}
sHighpassFilter HighpassFilter::create(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency)
{
	return sHighpassFilter(new HighpassFilter(tail,head,channelNum,frameRate,CutoffFrequency));
}
sBandpassFilter BandpassFilter::create(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff)
{
	return sBandpassFilter(new BandpassFilter(blockSize,channelNum,frameRate,lowCutoff,highCutoff));
}
sBandpassFilter BandpassFilter::create(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff)
{
	return sBandpassFilter(new BandpassFilter(tail,head,channelNum,frameRate,lowCutoff,highCutoff));
}
sBandRejectFilter BandRejectFilter::create(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff)
{
	return sBandRejectFilter(new BandRejectFilter(blockSize,channelNum,frameRate,lowCutoff,highCutoff));
}
sBandRejectFilter BandRejectFilter::create(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff)
{
	return sBandRejectFilter(new BandRejectFilter(tail,head,channelNum,frameRate,lowCutoff,highCutoff));
}

enum FilterType : uint8_t
{
	lowpass,
	highpass,
	bandpass,
	bandreject
};

// Lowpass filters
sConvolver createLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageLowpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount);
// Highpass filters
sConvolver createHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageHighpassFilter(int inputSamplerate,int CutoffFrequency, size_t head_blocksize, size_t tail_blocksize, int channelCount);
// Bandpass filters
sConvolver createBandpassFilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageBandpassFilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t head_blocksize, size_t tail_blocksize, int channelCount);
// Band-Rejject filters
sConvolver createBandRejectfilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t blocksiz, int channelCount);
sTwoStageConvolver createTwoStageBandRejectfilter(int inputSamplerate,int lowCutoff, int highCutoff, size_t head_blocksize, size_t tail_blocksize, int channelCount);

struct SP_private
{
	virtual const sEffect getEffect() const = 0;
	virtual ~SP_private() = default;
	virtual void resetSelf() = 0;
	int inputSamplerate;
	int CutoffFrequency;
	int channelCount;
	FilterType type;
};
struct BP_private
{
	virtual const sEffect getEffect() const = 0;
	virtual ~BP_private() = default;
	virtual void resetSelf() = 0;
	int inputSamplerate;
	int lowCutoff;
	int highCutoff;
	int channelCount;
	FilterType type;
};

struct NormalSinglepass : public SP_private
{
	sConvolver conv;
	size_t blocksize;
	NormalSinglepass(FilterType type, int inputSamplerate,int CutoffFrequency, size_t blocksiz, int channelCount)
	{
		this->type = type;
		this->inputSamplerate = inputSamplerate;
		this->CutoffFrequency = CutoffFrequency;
		this->blocksize = blocksiz;
		this->channelCount = channelCount;
		switch (type) {
		case lowpass:
			conv = createLowpassFilter(inputSamplerate,CutoffFrequency,blocksiz,channelCount);
			break;
		case highpass:
			conv = createHighpassFilter(inputSamplerate,CutoffFrequency,blocksiz,channelCount);
			break;
		default:
			break;
		}
	}
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		switch (type) {
		case lowpass:
			conv = createLowpassFilter(inputSamplerate,CutoffFrequency,blocksize,channelCount);
			break;
		case highpass:
			conv = createHighpassFilter(inputSamplerate,CutoffFrequency,blocksize,channelCount);
			break;
		default:
			break;
		}
	}
};
struct TwoStageSinglepass : public SP_private
{
	sTwoStageConvolver conv;
	size_t head,tail;
	TwoStageSinglepass(FilterType type, int inputSamplerate,int CutoffFrequency, size_t head, size_t tail, int channelCount)
	{
		this->type = type;
		this->inputSamplerate = inputSamplerate;
		this->CutoffFrequency = CutoffFrequency;
		this->head = head;
		this->tail = tail;
		this->channelCount = channelCount;
		switch (type) {
		case lowpass:
			conv = createTwoStageLowpassFilter(inputSamplerate,CutoffFrequency,head,tail,channelCount);
			break;
		case highpass:
			conv = createTwoStageHighpassFilter(inputSamplerate,CutoffFrequency,head,tail,channelCount);
			break;
		default:
			break;
		}
	}
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		switch (type) {
		case lowpass:
			conv = createTwoStageLowpassFilter(inputSamplerate,CutoffFrequency,head,tail,channelCount);
			break;
		case highpass:
			conv = createTwoStageHighpassFilter(inputSamplerate,CutoffFrequency,head,tail,channelCount);
			break;
		default:
			break;
		}
	}
};
struct NormalBandpass : public BP_private
{
	sConvolver conv;
	size_t blocksize;
	NormalBandpass(FilterType type, int inputSamplerate,int lowCutoff, int highCutoff, size_t blocksiz, int channelCount)
	{
		this->type = type;
		this->inputSamplerate = inputSamplerate;
		this->lowCutoff = lowCutoff;
		this->highCutoff = highCutoff;
		this->blocksize = blocksiz;
		this->channelCount = channelCount;
		switch (type) {
		case bandpass:
			conv = createBandpassFilter(inputSamplerate,lowCutoff,highCutoff,blocksiz,channelCount);
			break;
		case bandreject:
			conv = createBandRejectfilter(inputSamplerate,lowCutoff,highCutoff,blocksiz,channelCount);
			break;
		default:
			break;
		}
	}
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		switch (type) {
		case bandpass:
			conv = createBandpassFilter(inputSamplerate,lowCutoff,highCutoff,blocksize,channelCount);
			break;
		case bandreject:
			conv = createBandRejectfilter(inputSamplerate,lowCutoff,highCutoff,blocksize,channelCount);
			break;
		default:
			break;
		}
	}
};
struct TwoStageBandpass : public BP_private
{
	sTwoStageConvolver conv;
	size_t head,tail;
	TwoStageBandpass(FilterType type, int inputSamplerate,int lowCutoff, int highCutoff, size_t head, size_t tail, int channelCount)
	{
		this->type = type;
		this->inputSamplerate = inputSamplerate;
		this->lowCutoff = lowCutoff;
		this->highCutoff = highCutoff;
		this->head = head;
		this->tail = tail;
		this->channelCount = channelCount;
		switch (type) {
		case bandpass:
			conv = createTwoStageBandpassFilter(inputSamplerate,lowCutoff,highCutoff,head,tail,channelCount);
			break;
		case bandreject:
			conv = createTwoStageBandRejectfilter(inputSamplerate,lowCutoff,highCutoff,head,tail,channelCount);
			break;
		default:
			break;
		}
	}
	const sEffect getEffect() const { return conv; }
	void resetSelf()
	{
		switch (type) {
		case bandpass:
			conv = createTwoStageBandpassFilter(inputSamplerate,lowCutoff,highCutoff,head,tail,channelCount);
			break;
		case bandreject:
			conv = createTwoStageBandRejectfilter(inputSamplerate,lowCutoff,highCutoff,head,tail,channelCount);
			break;
		default:
			break;
		}
	}
};

LowpassFilter::LowpassFilter(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency)
	: imp(new NormalSinglepass(lowpass,frameRate,CutoffFrequency,blockSize,channelNum))
{
	;
}
LowpassFilter::LowpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency)
	: imp(new TwoStageSinglepass(lowpass,frameRate,CutoffFrequency,head,tail,channelNum))
{
	;
}
long LowpassFilter::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	return imp->getEffect()->process(inBuffer,outBuffer,maxFrames,channelNum,frameRate);
}
int LowpassFilter::getCutoff() const
{
	return imp->CutoffFrequency;
}
void LowpassFilter::setCutoff(int setto)
{
	imp->CutoffFrequency = setto;
	imp->resetSelf();
}

HighpassFilter::HighpassFilter(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency)
	: imp(new NormalSinglepass(highpass,frameRate,CutoffFrequency,blockSize,channelNum))
{
	;
}
HighpassFilter::HighpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency)
	: imp(new TwoStageSinglepass(highpass,frameRate,CutoffFrequency,head,tail,channelNum))
{
	;
}
long HighpassFilter::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	return imp->getEffect()->process(inBuffer,outBuffer,maxFrames,channelNum,frameRate);
}
int HighpassFilter::getCutoff() const
{
	return imp->CutoffFrequency;
}
void HighpassFilter::setCutoff(int setto)
{
	imp->CutoffFrequency = setto;
	imp->resetSelf();
}

BandpassFilter::BandpassFilter(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff)
	: imp(new NormalBandpass(bandpass,frameRate,lowCutoff,highCutoff,blockSize,channelNum))
{
	;
}
BandpassFilter::BandpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff)
	: imp(new TwoStageBandpass(bandpass,frameRate,lowCutoff,highCutoff,head,tail,channelNum))
{
	;
}
int BandpassFilter::getLowCutoff() const
{
	return imp->lowCutoff;
}
void BandpassFilter::setLowCutoff(int setto)
{
	imp->lowCutoff = setto;
	imp->resetSelf();
}
int BandpassFilter::getHighCutoff() const
{
	return imp->highCutoff;
}
void BandpassFilter::setHighCutoff(int setto)
{
	imp->highCutoff = setto;
	imp->resetSelf();
}
void BandpassFilter::setBoth(int low, int high)
{
	imp->lowCutoff = low;
	imp->highCutoff = high;
	imp->resetSelf();
}
long BandpassFilter::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	imp->getEffect()->process(inBuffer,outBuffer,maxFrames,channelNum,frameRate);
}
BandRejectFilter::BandRejectFilter(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff)
	: imp(new NormalBandpass(bandreject,frameRate,lowCutoff,highCutoff,blockSize,channelNum))
{
	;
}
BandRejectFilter::BandRejectFilter(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff)
	: imp(new TwoStageBandpass(bandreject,frameRate,lowCutoff,highCutoff,head,tail,channelNum))
{
	;
}
int BandRejectFilter::getLowCutoff() const
{
	return imp->lowCutoff;
}
void BandRejectFilter::setLowCutoff(int setto)
{
	imp->lowCutoff = setto;
	imp->resetSelf();
}
int BandRejectFilter::getHighCutoff() const
{
	return imp->highCutoff;
}
void BandRejectFilter::setHighCutoff(int setto)
{
	imp->highCutoff = setto;
	imp->resetSelf();
}
void BandRejectFilter::setBoth(int low, int high)
{
	imp->lowCutoff = low;
	imp->highCutoff = high;
	imp->resetSelf();
}
long BandRejectFilter::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	imp->getEffect()->process(inBuffer,outBuffer,maxFrames,channelNum,frameRate);
}

}
}

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
