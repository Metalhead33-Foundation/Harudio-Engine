#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP
#include "../Io/Global.hpp"
#include "../Io/SoundFile.hpp"
#include <vector>
#include <mutex>

namespace Audio {

typedef std::pair<const float*,long> BufferOutput;

DEFINE_CLASS(Buffer)
class Buffer
{
protected:
	int frameRate;
	int channelNum;
	std::vector<float> buff;
	std::recursive_mutex locker;
	Buffer(sf_count_t buffsize=0);
	Buffer(Abstract::sFIO readah);
	Buffer(sSoundFile file, sf_count_t offset = 0, sf_count_t frameNum=0);
	Buffer(const float* input, size_t frameNum, int frameRate, int channelNum);
public:
	Buffer(int frameRate, int channelNum);
	int getFrameRate() const;
	int getChannelNum() const;
	size_t getFrameCount() const;

	virtual ~Buffer() = default;
	virtual void getAudioData(BufferOutput* out, size_t index) const;
	virtual size_t getSampleCount() const;
	static sBuffer create(sf_count_t buffsize=0);
	static sBuffer create(Abstract::sFIO readah);
	static sBuffer create(sSoundFile file, sf_count_t offset = 0, sf_count_t frameNum=0);
	static sBuffer create(const float* input, size_t frameNum, int frameRate, int channelNum);
	void bufferData(const float* input, size_t frameNum, int frameRate, int channelNum, size_t bufferOffset=0, bool forceResize=false);
	void bufferData(const sSoundFile file, sf_count_t offset = 0, sf_count_t frameNum=0, size_t bufferOffset=0, bool forceResize=false);
	void bufferData(Abstract::sFIO readah);
};

}
#endif // AUDIOBUFFER_HPP
