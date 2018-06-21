#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "ImpulseResponseGenerator.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(LowpassFilter)
DEFINE_CLASS(HighpassFilter)
DEFINE_CLASS(BandpassFilter)
DEFINE_CLASS(BandRejectFilter)

class SinglepassFilter : public ImpulseResponseGenerator
{
protected:
	int cutoffFrequency;
	int inputSamplerate;
	virtual void reset() = 0;
	SinglepassFilter(int inputSamplerate,int cutoffFrequency=-1,int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	virtual ~SinglepassFilter() = default;
	int getCutoffFrequency() const;
	void setCutoffFrequency(int setto);
	int getInputSamplerate() const;
	void setInputSamplerate(int setto);
};
class DoublepassFilter : public ImpulseResponseGenerator
{
protected:
	int lowCutoff;
	int highCutoff;
	int inputSamplerate;
	virtual void reset() = 0;
	DoublepassFilter(int inputSamplerate, int lowCutoff=-1, int highCutoff=-1, int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	virtual ~DoublepassFilter() = default;
	int getLowCutoff() const;
	void setLowCutoff(int setto);
	int getHighCutoff() const;
	void setHighCutoff(int setto);
	void setCutoff(int low, int high);
	int getInputSamplerate() const;
	void setInputSamplerate(int setto);
};

class LowpassFilter : public SinglepassFilter
{
private:
	LowpassFilter(int inputSamplerate, int cutoffFrequency=-1,int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	sLowpassFilter create(int inputSamplerate, int cutoffFrequency=-1,int channelId=0, const sAdaptableConvolver setto=nullptr);
protected:
	void reset();
};
class HighpassFilter : public SinglepassFilter
{
private:
	HighpassFilter(int inputSamplerate, int cutoffFrequency=-1,int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	sHighpassFilter create(int inputSamplerate, int cutoffFrequency=-1,int channelId=0, const sAdaptableConvolver setto=nullptr);
protected:
	void reset();
};
class BandpassFilter : public DoublepassFilter
{
private:
	BandpassFilter(int inputSamplerate, int lowCutoff=-1, int highCutoff=-1, int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	sBandpassFilter create(int inputSamplerate, int lowCutoff=-1, int highCutoff=-1, int channelId=0, const sAdaptableConvolver setto=nullptr);
protected:
	void reset();
};
class BandRejectFilter : public DoublepassFilter
{
private:
	BandRejectFilter(int inputSamplerate, int lowCutoff=-1, int highCutoff=-1, int channelId=0, const sAdaptableConvolver setto=nullptr);
public:
	sBandRejectFilter create(int inputSamplerate, int lowCutoff=-1, int highCutoff=-1, int channelId=0, const sAdaptableConvolver setto=nullptr);
protected:
	void reset();
};

}
}
#endif // LOWPASSFILTER_HPP
