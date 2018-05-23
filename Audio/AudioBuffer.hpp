#ifndef AUDIOBUFFER_HPP
#define AUDIOBUFFER_HPP
#include "../Io/Global.hpp"
#include "../Io/SoundFile.hpp"
#include <vector>
#include <mutex>

namespace Audio {

struct BufferOutput
{
	const float* audioData;
	long numberOfRemainingFrames;
};

DEFINE_CLASS(Buffer)
class Buffer
{
private:
	std::vector<float> buff;
	int frameRate;
	int channelNum;
	std::mutex locker;
public:
	void getAudioData(BufferOutput* out, size_t index) const;
	int getFrameRate() const;
	int getChannelNum() const;
	size_t getFrameCount() const;
	size_t getBufferSize() const;

	void bufferData(const float* input, size_t frameNum, int frameRate, int channelNum);
	void bufferData(sSoundFile file, sf_count_t offset = 0, sf_count_t frameNum=0, bool forceResize=false);
	void bufferData(Abstract::sFIO readah);

	~Buffer() = default;
	Buffer();
	Buffer(Abstract::sFIO readah);
	Buffer(sSoundFile file, sf_count_t offset = 0, sf_count_t frameNum=0);
	Buffer(const float* input, size_t frameNum, int frameRate, int channelNum);
};

}
#endif // AUDIOBUFFER_HPP
