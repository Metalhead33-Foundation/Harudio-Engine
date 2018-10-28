#ifndef AUDIOBUFFER_IMPL_HPP
#define AUDIOBUFFER_IMPL_HPP
#include "../harudio-headers/Audio/AudioBuffer.hpp"
#include <vector>

namespace Software {

class Buffer : public Audio::Buffer
{
private:
	int frameRate;
	int channelNum;
	std::vector<float> buff;
public:
	Buffer();
	long bufferData(const float* input, size_t frameNum,
							int frameRate, int channelNum, size_t bufferOffset=0,
							bool forceResize=false);
	long bufferData(Audio::Importer* import, size_t frameNum,
							int frameRate, int channelNum, size_t bufferOffset=0,
							bool forceResize=false);

	int getFrameRate() const;
	int getChannelNum() const ;
	void setFrameRate(int frameRate);
	size_t getFrameCount() const;
	size_t getSampleCount() const;

	void getAudioData(Audio::BufferOutput* out, size_t index) const;
};

}
#endif // AUDIOBUFFER_IMPL_HPP
