#include "Resampler.hpp"
#include <cstring>
namespace Audio {

float Resampler::getSpeed() const
{
	return speed;
}
void Resampler::setSpeed(float newSpeed)
{
	speed = newSpeed;
}
double Resampler::getRatio() const
{
	if(input.expired()) return 0;
	else
	{
		return double(outputFramerate) / double(getFramerate()) / double(speed);
	}
}
long Resampler::converterCallback(void *self, float **data)
{
	if(self)
	{
		pResampler sampler = reinterpret_cast<pResampler>(self);
		if(sampler->input.expired()) return 0;
		sPlayable input = sampler->input.lock();
		long inFrames = long(TINYBUFF/input->getChannelCount());
		double ratio = sampler->getRatio();
		if(ratio >= 1.00) // If we are upsampling, we need to put fewer frames in the buffer
		{
			inFrames = long(double(inFrames) / ratio);
		}
		inFrames = input->pullAudio(sampler->inputBuffer,inFrames,
									input->getChannelCount(),input->getFramerate());
		*data = sampler->inputBuffer;
		return inFrames;
	} else return 0;
}
Resampler::Resampler(int converterType)
	: converter(nullptr), converterType(converterType), speed(1.0f)
{
	;
}
void Resampler::cleanBuffers()
{
	memset(inputBuffer,0,TINYBUFF * sizeof(float));
}
void Resampler::onChangedInput()
{
	sPlayable tmp = input.lock();
	if(converter)
	{
		src_delete(converter);
		int err;
		converter = src_callback_new(converterCallback,converterType,tmp->getChannelCount(),&err,this);
	}
}
long Resampler::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(input.expired()) return 0;
	if(channelNum != getChannelCount()) throw std::runtime_error("Resampler - I/O Channel number mismatch! Please use a panner or channel mixer!");
	cleanBuffers();
	outputFramerate = frameRate;
	long processedFrames = 0;
	long readFrames = 0;
	do {
		long framesToRead = std::min(long(TINYBUFF/channelNum),maxFrameNum-processedFrames);
		readFrames = src_callback_read(converter,ratio,framesToRead,outputBuffer);
		for(long frameCursor = 0; frameCursor < readFrames; ++frameCursor,++processedFrames)
		{
			long inputCursor = frameCursor*channelNum;
			long outputCursor = processedFrames*channelNum;
			for(int i = 0; i < channelNum; ++i)
			{
				output[outputCursor+i] += outputBuffer[inputCursor+i];
			}
		}
	} while(readFrames);
	return processedFrames;
}

}
