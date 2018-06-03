#ifndef AUDIOPLUGINPLAYABLE_HPP
#define AUDIOPLUGINPLAYABLE_HPP
#include "AudioPlayable.hpp"
#include <array>
namespace Audio {

#define TINYBUFF 2048

DEFINE_CLASS(PluginPlayable)
class PluginPlayable : public Playable
{
protected:
	wPlayable input;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate) = 0;
public:
	virtual ~PluginPlayable() = default;
	bool isPlaying() const;
	virtual int getFramerate() const;
	virtual int getChannelCount() const;
	void setInput(sPlayable ninput);
	const sPlayable getInput() const;
	virtual void onChangedInput() = 0;
	typedef std::array<float,TINYBUFF> PluggableBuffer;
};

}
#endif // AUDIOPLUGINPLAYABLE_HPP
