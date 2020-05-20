#ifndef AUDIOPACKET_HPP
#define AUDIOPACKET_HPP
#include <cstddef>
#include <cstdint>

namespace Audio {

    enum class InterleavingType : std::int8_t {
        DONT_CARE = -1, // We don't really care
        INTERLACED =
            0, // Each channels are stored separately, channel by channel
        INTERLEAVED = 1 // Each channels are stored together frame by frame
    };
	//typedef std::uint32_t FrameCount;
	struct Framerate {
		typedef std::uint32_t __type;
		__type __value;
		// operator std::uint32_t() { return __value; }
		operator __type&() { return __value; }
		operator const __type&() const { return __value; }
	};
	struct SampleCount {
		typedef std::uint32_t __type;
		__type __value;
		// operator std::uint32_t() { return __value; }
		operator __type&() { return __value; }
		operator const __type&() const { return __value; }
		inline constexpr std::size_t toBytes() const { return __value*sizeof(float); }
	};
	struct ChannelCount {
		typedef std::uint8_t __type;
		__type __value;
		// operator std::uint8_t() { return __value; }
		operator __type&() { return __value; }
		operator const __type&() const { return __value; }
	};
	struct FrameCount {
		typedef std::uint32_t __type;
		__type __value;
		// operator std::uint32_t() { return __value; }
		operator __type&() { return __value; }
		operator const __type&() const { return __value; }
		inline constexpr SampleCount toSamples(ChannelCount channels) const { return SampleCount{__value*channels.__value}; }
		inline constexpr std::size_t toBytes(ChannelCount channels) const { return toSamples(channels).toBytes(); }
	};

    struct Output {

        float *dst;                // Destination
		FrameCount frameCnt;     // How many frames requested/allowed at max?
		Framerate frameRate;     // Sampling rate of the audio
		ChannelCount channelCnt; // How many channels?
        InterleavingType interleavingType; // Should channels be interleaved, or
                                           // should they be separated?

		Output(float* ndst=nullptr,FrameCount nframeCnt={0},
			   Framerate nframeRate={0},ChannelCount nChannelCnt={0},
			   InterleavingType nInterleavingType=InterleavingType::DONT_CARE)
			: dst(ndst),frameCnt(nframeCnt),frameRate(nframeRate),channelCnt(nChannelCnt),
			  interleavingType(nInterleavingType)
		{

		}

		inline constexpr SampleCount sampleCnt( ) const {
			return frameCnt.toSamples(channelCnt);
        }
        inline constexpr std::size_t byteCnt( ) const {
			return sampleCnt().toBytes();
        }
    };
    struct Input {
        const float *src;                  // Source
		FrameCount frameCnt;             // How many frames do we have?
		Framerate frameRate;             // Sampling rate of the audio
		ChannelCount channelCnt;         // How many channels do we have?
        InterleavingType interleavingType; // Is the source audio interleaved?


		Input(const float* nsrc=nullptr,FrameCount nframeCnt={0},
			   Framerate nframeRate={0},ChannelCount nChannelCnt={0},
			   InterleavingType nInterleavingType=InterleavingType::DONT_CARE)
			: src(nsrc),frameCnt(nframeCnt),frameRate(nframeRate),channelCnt(nChannelCnt),
			  interleavingType(nInterleavingType)
		{

		}

		inline constexpr SampleCount sampleCnt( ) const {
			return frameCnt.toSamples(channelCnt);
        }
		inline constexpr std::size_t byteCnt( ) const {
			return sampleCnt().toBytes();
        }
    };

} // namespace Audio

#endif // AUDIOPACKET_HPP
