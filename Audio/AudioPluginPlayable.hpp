#ifndef AUDIOPLUGINPLAYABLE_HPP
#define AUDIOPLUGINPLAYABLE_HPP
#include "AudioPlayable.hpp"
namespace Audio {

#define TINYBUFF 256

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
};

}
#endif // AUDIOPLUGINPLAYABLE_HPP
