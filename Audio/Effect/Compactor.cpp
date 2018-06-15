#include "Compactor.hpp"
#include "../../Io/fsqrt.hpp"
#ifndef SSE_SUPPORTED
#include <cmath>
#endif
#include <cmath>

namespace Audio {
namespace FX {

float Compactor::compact(float num)
{
	bool isNegative = num < 0.0f;
	if(isNegative) num *= -1.0f;
	num *= 0.5f;
	num += 1.0f;
	return num;
}
float Compactor::uncompact(float num, float original)
{
	bool isNegative = original < 0.0f;
	num -= 1.0f;
	num = std::min(num,1.0f);
	if(isNegative) num *= -1.0f;
	return num;
}
Compactor::Compactor()
{
	;
}
sCompactor Compactor::create()
{
	return sCompactor(new Compactor());
}
long Compactor::process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate)
{
	const long sampleCount = maxFrames * channelNum;
	for(long i = 0; i < sampleCount;++i)
	{
		outBuffer[i] = uncompact(sqrt(compact(inBuffer[i])),inBuffer[i]);
	}
/*#ifdef SSE_SUPPORTED
	const long iterationCount = sampleCount % 4 ? ((sampleCount/4)+1) : sampleCount/4;
	for(long i = 0; i < iterationCount;++i)
	{
		const long sampleCursor = i * 4;
		SSE_FLOAT tmp;
		for(long j = sampleCursor; j < 4 && ((sampleCursor+j)<sampleCount); ++j)
		{
			tmp.f[j] = compact(inBuffer[sampleCursor+j]);
		}
		tmp.toMM();
		tmp.mm = _mm_fsqrt(tmp.mm);
		tmp.toF();
		for(long j = sampleCursor; j < 4 && ((sampleCursor+j)<sampleCount); ++j)
		{
			outBuffer[sampleCursor+j] = uncompact(tmp.f[j],inBuffer[sampleCursor+j]);
		}
	}
#else
	for(long i = 0; i < sampleCount;++i)
	{
		outBuffer[i] = uncompact(sqrt(compact(inBuffer[i])),inBuffer[i]);
	}
#endif
*/
	return maxFrames;
}

}
}
