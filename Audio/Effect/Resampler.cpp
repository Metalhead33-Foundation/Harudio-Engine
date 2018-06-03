#include "Resampler.hpp"
#include <cstring>
namespace Audio {

std::array<float,TINYBUFF> Resampler::inputBuffer;

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
void Resampler::refreshRatio(int outputFramerate)
{
	ratio = getRatio(outputFramerate);
}
long Resampler::converterCallback(void *self, float **data)
{
	if(self)
	{
		pResampler sampler = reinterpret_cast<pResampler>(self);
		if(sampler->input.expired()) return 0;
		sPlayable input = sampler->input.lock();
		long inFrames;
		if(sampler->ratio <= 1.0f) inFrames = long(float(sampler->inputBuffer.size()/input->getChannelCount())*sampler->ratio);
		else inFrames = long(float(sampler->inputBuffer.size()/input->getChannelCount()));
		inFrames = input->pullAudio(sampler->inputBuffer.data(),inFrames,
									input->getChannelCount(),input->getFramerate());
		*data = sampler->inputBuffer.data();
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
	refreshRatio(frameRate);
	long processedFrames = 0;
	long readFrames = 0;
	do {
		readFrames = std::min(long(inputBuffer.size()/channelNum),maxFrameNum-processedFrames);
		readFrames = src_callback_read(converter,ratio,readFrames,output);
		processedFrames += readFrames;
	} while(readFrames);
	return processedFrames;
}

}
