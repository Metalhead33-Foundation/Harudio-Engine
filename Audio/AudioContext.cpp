#include "AudioContext.hpp"
#include <stdexcept>
#include <cstring>
#include <vector>
#include <climits>

namespace Audio {

int Context::numContexts;
std::recursive_mutex Context::locker;

void Context::queryDevices(PaStreamParameters* inputParams, PaStreamParameters* outputParams, double desiredSamplerate)
{
	int numDevices = Pa_GetDeviceCount();
	if( numDevices < 0 )
	{
		throw std::runtime_error("There are no audio devices at all in your system!");
	}
	const PaDeviceInfo *deviceInfo;
	std::vector<std::pair<int,int>> fittingDevices;
	for(int i=0; i<numDevices; i++ )
	{
		deviceInfo = Pa_GetDeviceInfo(i);
		inputParams->device = i;
		outputParams->device = i;
		inputParams->suggestedLatency = deviceInfo->defaultLowInputLatency;
		outputParams->suggestedLatency = deviceInfo->defaultLowOutputLatency;
		PaError err = Pa_IsFormatSupported(inputParams, outputParams, desiredSamplerate);
		if( err == paFormatIsSupported )
		{
			fittingDevices.push_back(std::make_pair(i,0));
		}
	}
	if(fittingDevices.empty()) throw std::runtime_error("No fitting audio device was found!");
	// Let's find out about the maximal
	PaTime maxLowInputLatency = 0.00;
	PaTime maxLowOutputLatency = 0.00;
	PaTime maxHighInputLatency = 0.00;
	PaTime maxHighOutputLatency = 0.00;
	for(auto it = fittingDevices.begin(); it != fittingDevices.end();++it)
	{
		deviceInfo = Pa_GetDeviceInfo(it->first);
		maxLowInputLatency = std::max(deviceInfo->defaultLowInputLatency,maxLowInputLatency);
		maxLowOutputLatency = std::max(deviceInfo->defaultLowOutputLatency,maxLowOutputLatency);
		maxHighInputLatency = std::max(deviceInfo->defaultHighInputLatency,maxHighInputLatency);
		maxHighOutputLatency = std::max(deviceInfo->defaultHighOutputLatency,maxHighOutputLatency);
	}
	for(auto it = fittingDevices.begin(); it != fittingDevices.end();++it)
	{
		deviceInfo = Pa_GetDeviceInfo(it->first);
		it->second += int(maxHighInputLatency / deviceInfo->defaultHighInputLatency * 100.00);
		it->second += int(maxHighOutputLatency / deviceInfo->defaultHighOutputLatency * 100.00);
		it->second += int(maxLowInputLatency / deviceInfo->defaultLowInputLatency * 100.00);
		it->second += int(maxLowOutputLatency / deviceInfo->defaultLowOutputLatency * 100.00);
		if(!strcmp(deviceInfo->name,"pulse")) it->second = INT_MAX;
		else if(!strcmp(deviceInfo->name,"jack_mixer")) it->second = INT_MIN;
		std::cout << deviceInfo->name << ": " << it->second << std::endl;
	}
	int bestFit = 0;
	for(size_t i = 0; i < fittingDevices.size();++i)
	{
		if(fittingDevices[i].second >= fittingDevices[bestFit].second )
		{
			bestFit = i;
		}
	}
	deviceInfo = Pa_GetDeviceInfo(fittingDevices[bestFit].first);
	std::cout << "Chosen audio device: " << deviceInfo->name << std::endl;
	inputParams->device = fittingDevices[bestFit].first;
	outputParams->device = fittingDevices[bestFit].first;
	inputParams->suggestedLatency = deviceInfo->defaultLowInputLatency;
	outputParams->suggestedLatency = deviceInfo->defaultLowOutputLatency;
}
Context::Context(int intendedFramerate, int intendedBumChannels, long intendedBufferSize)
	: Mixer(intendedBumChannels,intendedFramerate,intendedBufferSize), stream(nullptr)
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
	PaStreamParameters outputParameters;
	PaStreamParameters inputParameters;
	std::memset(&outputParameters,0,sizeof(PaStreamParameters));
	std::memset(&inputParameters,0,sizeof(PaStreamParameters));
	outputParameters.channelCount = intendedBumChannels;
	inputParameters.channelCount = intendedBumChannels;
	outputParameters.sampleFormat = paFloat32;
	inputParameters.sampleFormat = paFloat32;
	PaError err;
	if(!numContexts) { err = Pa_Initialize();
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
	}
	++numContexts;
	queryDevices(&inputParameters,&outputParameters,double(intendedFramerate));
	err = Pa_OpenStream(&stream,&inputParameters,&outputParameters,intendedFramerate,intendedBufferSize,paNoFlag,
						patestCallback,this);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}

long Context::pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate)
{
	mixDown();
	long maxFrames = std::min(maxFrameNum,frameCount);
	if(channelNum != channelNumber) throw std::runtime_error("Context - I/O Channel number mismatch! Please use a panner or channel mixer!");
	if(frameRate != this->frameRate) throw std::runtime_error("Context - I/O Framerate mismatch! Please use a samplerate converter!");
	memcpy(output,buffer.data(),maxFrames * channelNum * sizeof(float));
	return maxFrames;
}
Context::~Context()
{
	std::unique_lock<std::recursive_mutex> locker(this->locker);
	PaError err;
	if(stream)
	{
		err = Pa_CloseStream(stream);
		if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
	}
	--numContexts;
	if(!numContexts)
	{
		err = Pa_Terminate();
		if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
	}
}
void Context::suspend()
{
	PaError err = Pa_StopStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Context::unsuspend()
{
	PaError err = Pa_StartStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
void Context::abort()
{
	PaError err = Pa_AbortStream(stream);
	if( err != paNoError ) throw std::runtime_error(Pa_GetErrorText(err));
}
bool Context::isStopped()
{
	PaError err = Pa_IsStreamStopped(stream);
	return err != 0;
}
bool Context::isActive()
{
	PaError err = Pa_IsStreamActive(stream);
	return err != 0;
}

}
