#ifndef LOWPASSFILTER_HPP
#define LOWPASSFILTER_HPP
#include "../AudioEffect.hpp"

namespace Audio {
namespace FX {

DEFINE_CLASS(LowpassFilter)
DEFINE_CLASS(HighpassFilter)
DEFINE_CLASS(BandpassFilter)
DEFINE_CLASS(BandRejectFilter)
DEFINE_STRUCT(SP_private)
DEFINE_STRUCT(BP_private)

class LowpassFilter : public Effect
{
private:
	const uSP_private imp;
protected:
	LowpassFilter(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency);
	LowpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency);
public:
	int getCutoff() const;
	void setCutoff(int setto);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	static sLowpassFilter create(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency);
	static sLowpassFilter create(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency);
};
class HighpassFilter : public Effect
{
private:
	const uSP_private imp;
protected:
	HighpassFilter(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency);
	HighpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency);
public:
	int getCutoff() const;
	void setCutoff(int setto);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	static sHighpassFilter create(size_t blockSize, int channelNum, int frameRate, int CutoffFrequency);
	static sHighpassFilter create(size_t tail, size_t head, int channelNum, int frameRate, int CutoffFrequency);
};
class BandpassFilter : public Effect
{
private:
	const uBP_private imp;
protected:
	BandpassFilter(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff);
	BandpassFilter(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff);
public:
	int getLowCutoff() const;
	void setLowCutoff(int setto);
	int getHighCutoff() const;
	void setHighCutoff(int setto);
	void setBoth(int low, int high);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	static sBandpassFilter create(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff);
	static sBandpassFilter create(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff);
};
class BandRejectFilter : public Effect
{
private:
	const uBP_private imp;
protected:
	BandRejectFilter(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff);
	BandRejectFilter(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff);
public:
	int getLowCutoff() const;
	void setLowCutoff(int setto);
	int getHighCutoff() const;
	void setHighCutoff(int setto);
	void setBoth(int low, int high);
	long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate);
	static sBandRejectFilter create(size_t blockSize, int channelNum, int frameRate, int lowCutoff, int highCutoff);
	static sBandRejectFilter create(size_t tail, size_t head, int channelNum, int frameRate, int lowCutoff, int highCutoff);
};

}
}
#endif // LOWPASSFILTER_HPP
