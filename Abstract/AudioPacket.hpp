#ifndef AUDIOPACKET_HPP
#define AUDIOPACKET_HPP
#include <cstddef>
#include <cstdint>

namespace Audio {

enum class InterleavingType : std::int8_t
{
	DONT_CARE = -1, // We don't really care
	INTERLACED = 0, // Each channels are stored separately, channel by channel
	INTERLEAVED = 1 // Each channels are stored together frame by frame
};
typedef std::uint32_t FrameCount_T;
typedef std::uint32_t Framerate_T;
typedef std::uint32_t SampleCount_T;
typedef std::uint8_t ChannelCount_T;

inline constexpr SampleCount_T framesToSamples(FrameCount_T frameCnt, ChannelCount_T channelCnt)  { return frameCnt * channelCnt; }
inline constexpr std::size_t samplesToBytes(SampleCount_T sampleCnt)  { return std::size_t(sampleCnt)*sizeof(float); }
inline constexpr std::size_t framesToBytes(FrameCount_T frameCnt, ChannelCount_T channelCnt) { return samplesToBytes(framesToSamples(frameCnt,channelCnt));}

struct Output {

	float* dst; // Destination
	FrameCount_T frameCnt; // How many frames requested/allowed at max?
	Framerate_T frameRate; // Sampling rate of the audio
	ChannelCount_T channelCnt; // How many channels?
	InterleavingType interleavingType; // Should channels be interleaved, or should they be separated?

	inline constexpr SampleCount_T sampleCnt() const { return framesToSamples(frameCnt,channelCnt); }
	inline constexpr std::size_t byteCnt() const { return framesToBytes(frameCnt,channelCnt); }
};
struct Input {
	const float* src; // Source
	FrameCount_T frameCnt; // How many frames do we have?
	Framerate_T frameRate; // Sampling rate of the audio
	ChannelCount_T channelCnt; // How many channels do we have?
	InterleavingType interleavingType; // Is the source audio interleaved?

	inline constexpr SampleCount_T sampleCnt() const { return framesToSamples(frameCnt,channelCnt); }
	inline constexpr std::size_t byteCnt() const { return framesToBytes(frameCnt,channelCnt); }
};

}

#endif // AUDIOPACKET_HPP
