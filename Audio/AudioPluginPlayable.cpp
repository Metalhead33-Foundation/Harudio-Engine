#include "AudioPluginPlayable.hpp"

namespace Audio {

bool PluginPlayable::isPlaying() const
{
	if(input.expired()) return false;
	else return true;
}
int PluginPlayable::getFramerate() const
{
	if(input.expired()) return 0;
	else
	{
		sPlayable tinput = input.lock();
		return tinput->getFramerate();
	}
}
int PluginPlayable::getChannelCount() const
{
	if(input.expired()) return 0;
	else
	{
		sPlayable tinput = input.lock();
		return tinput->getChannelCount();
	}
}
void PluginPlayable::setInput(sPlayable ninput)
{
	input = ninput;
	onChangedInput();
}
const sPlayable PluginPlayable::getInput() const
{
	return  input.lock();
}

}
