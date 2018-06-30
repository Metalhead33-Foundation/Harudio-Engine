#ifndef AUDIOPLUGINPLAYABLE_HPP
#define AUDIOPLUGINPLAYABLE_HPP
#include "AudioPlayable.hpp"
#include <array>
namespace Audio {

DEFINE_CLASS(PluginPlayable)
class PluginPlayable : public Playable
{
protected:
	wPlayable input;
public:
	virtual ~PluginPlayable() = default;
	bool isPlaying() const;
	virtual int getFramerate() const;
	virtual int getChannelCount() const;
	void setInput(sPlayable ninput);
	const sPlayable getInput() const;
	virtual void onChangedInput() = 0;
	virtual long pullAudio(float* output, long maxFrameNum, int channelNum, int frameRate) = 0;
};

}
#endif // AUDIOPLUGINPLAYABLE_HPP
