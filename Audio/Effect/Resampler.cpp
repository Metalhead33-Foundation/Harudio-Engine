#include "Resampler.hpp"
#include <cstring>
namespace Audio {

sResampler Resampler::create(int converterType)
{
	return sResampler(new Resampler(converterType));
}
float Resampler::getSpeed() const
{
	return speed;
}
void Resampler::setSpeed(float newSpeed)
{
	speed = newSpeed;
}
double Resampler::getRatio(int outputFramerate) const
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
		inFrames = input->pullAudio(sampler->inputBuffer.data(),inFrames,
									input->getChannelCount(),input->getFramerate());
		*data = sampler->inputBuffer.data();
		std::cout << inFrames << std::endl;
		return inFrames;
	} else return 0;
}
Resampler::Resampler(int converterType)
	: converter(nullptr), converterType(converterType), speed(1.0f),
	  inputBuffer(TINYBUFF), outputBuffer(TINYBUFF)
{
	;
}
void Resampler::cleanBuffers()
{
	memset(inputBuffer.data(),0,inputBuffer.size() * sizeof(float));
}
void Resampler::onChangedInput()
{
	sPlayable tmp = input.lock();
	int err;
	if(converter)
	{
		src_delete(converter);
	}
	converter = src_callback_new(converterCallback,converterType,tmp->getChannelCount(),&err,this);
}
long Resampler::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	if(!output) throw std::runtime_error("Invalid output!");
	if(input.expired()) return 0;
	if(channelNum != getChannelCount()) throw std::runtime_error("Resampler - I/O Channel number mismatch! Please use a panner or channel mixer!");
	cleanBuffers();
	double ratio = getRatio(frameRate);
	long processedFrames = 0;
	long readFrames = 0;
	do {
		readFrames = std::min(long(TINYBUFF/channelNum),maxFrameNum-processedFrames);
		readFrames = src_callback_read(converter,ratio,readFrames,outputBuffer.data());
		for(long frameCursor = 0; frameCursor < readFrames; ++frameCursor,++processedFrames)
		{
			long inputCursor = frameCursor*channelNum;
			long outputCursor = processedFrames*channelNum;
			for(int i = 0; i < channelNum; ++i)
			{
				output[outputCursor+i] += outputBuffer[inputCursor+i];
			}
		}
		std::cout << readFrames << std::endl;
	} while(readFrames);
	return processedFrames;
}

}
