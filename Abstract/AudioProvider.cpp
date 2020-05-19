#include "AudioProvider.hpp"
#include "AudioMismatchError.hpp"
#include <cstring>
#include <algorithm>

namespace Audio {

bool Provider::isPlaying() const
{
	return getState() == Status::PLAYING;
}

FrameCount_T Provider::outputTo(const Output &dst)
{
	Input in;
	receiveInput(in);
	if(in.src) { // Input is valid
	if( (dst.frameRate != in.frameRate) ||
			(dst.channelCnt != in.channelCnt) ||
			( dst.interleavingType != InterleavingType::DONT_CARE && (dst.interleavingType != in.interleavingType)))
	{
		throw MismatchError(dst.frameRate,in.frameRate,dst.channelCnt,in.channelCnt,dst.interleavingType,in.interleavingType);
	}
	const FrameCount_T framesToGo = std::min(in.frameCnt,dst.frameCnt);
	std::memcpy(dst.dst,in.src,framesToBytes(framesToGo,dst.channelCnt));
	outputFeedback(framesToGo);
	return framesToGo;
	} else return 0; // Input is invalid
}

}
