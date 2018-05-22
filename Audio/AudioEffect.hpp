#ifndef AUDIOEFFECT_HPP
#define AUDIOEFFECT_HPP

namespace Audio {

class Effect
{
public:
	virtual ~Effect() = 0;
	virtual long process(float* inBuffer, float* outBuffer, long maxFrames, int channelNum, int frameRate) = 0;
};

}

#endif // AUDIOEFFECT_HPP
