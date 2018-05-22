#include "AudioPlayable.hpp"

namespace Audio {


int Playable::patestCallback( const void *inputBuffer, void *outputBuffer,
						   unsigned long framesPerBuffer,
						   const PaStreamCallbackTimeInfo* timeInfo,
						   PaStreamCallbackFlags statusFlags,
						   void *userData )
{
	if(userData) {
	pPlayable data = reinterpret_cast<pPlayable>(userData);
	float *out = reinterpret_cast<float*>(outputBuffer);
	data->pullAudio(out, framesPerBuffer, data->getChannelCount(), data->getFramerate());
	return paContinue;
	} else return paAbort;
}
float Playable::getVolume() const
{
	return volume;
}
void Playable::setVolume(float nVolume)
{
	volume = nVolume;
}
/*void Playable::mixChannels(const float* frameIn, float* frameOut, int chanIn, int chanOut, float vol,size_t frameCount)
{
	MixingType mixType;
	float channelRatio = float(chanOut) / float(chanIn);
	if(chanOut == chanIn) mixType = EQUAL_MIX;
	else if(chanOut < chanIn) mixType = DOWNMIX;
	else mixType = UPMIX;
	for(size_t frameCursor = 0; frameCursor < frameCount; ++frameCursor)
	{
		size_t inCursor = frameCursor * chanIn;
		size_t outCursor = frameCursor * chanOut;
		switch(mixType)
		{
			case EQUAL_MIX:
			{
				for(int i = 0; i < chanIn; ++i)
				{
					frameOut[outCursor+i] += frameIn[inCursor+i] * vol;
				}
				break;
			}
			case UPMIX:
			{
				for(int i = 0; i < chanOut; ++i)
				{
					frameOut[outCursor+i] += frameIn[inCursor+ (i%chanIn)] * vol;
				}
				break;
			}
			case DOWNMIX:
			{
				for(int i = 0; i < chanIn; ++i)
				{
					frameOut[outCursor+(i%chanOut)] += frameIn[inCursor+i] * channelRatio * vol;
				}
				break;
			}
		}
	}
}*/

}
