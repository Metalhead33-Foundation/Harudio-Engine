#ifndef AUDIOMIXER_HPP
#define AUDIOMIXER_HPP
#include "../Abstract/AudioPlayable.hpp"
#include "../Abstract/AudioBuffer.hpp"
#include <map>

namespace Audio {
DEFINE_CLASS(Mixer)
class Mixer : public Playable
{
public:
	typedef std::map<wPlayable,float,std::owner_less<wPlayable>> ElementType;
	typedef ElementType::iterator iterator;
	typedef ElementType::const_iterator const_iterator;
	typedef ElementType::reverse_iterator reverse_iterator;
	typedef ElementType::const_reverse_iterator const_reverse_iterator;
private:
	FrameCount_T frameCnt;
	Framerate_T framerate;
	ChannelCount_T channelCnt;
	bool isActive;

	ElementType elements;
	DynamicBuffer buffA;
	Mixer(const Mixer& cpy) = delete; // No copying
	void operator=(const Mixer& cpy) = delete; // No copying
	FrameCount_T fillBuffers(FrameCount_T maxFrames, float *buffB);
public:
	Mixer(FrameCount_T nframeCnt, Framerate_T nframerate, ChannelCount_T nchannelCnt);
	Mixer(Mixer&& mov); // Move constructor
	void operator=(Mixer&& mov); // Move assignment

	FrameCount_T outputTo(const Output& dst); // Return value: frames transmitted
	bool isPlaying() const; // Is this thing even on?
	FrameCount_T getFrameCnt() const;
	Framerate_T getFramerate() const;
	ChannelCount_T getChannelCnt() const;
	float getVolume(const sPlayable& playable) const;
	float isPresent(const sPlayable& playable) const;
	void clearExpired();

	// Iterator stuff
	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;
	iterator end();
	const_iterator end() const;
	const_iterator cend() const;
	reverse_iterator rbegin();
	const_reverse_iterator rbegin() const;
	const_reverse_iterator crbegin() const;
	reverse_iterator rend();
	const_reverse_iterator rend() const;
	const_reverse_iterator crend() const;
	iterator find(const sPlayable& playable);
	const_iterator find(const sPlayable& playable) const;
	void insert(const sPlayable& playable, float nvolume);
	void setVolume(const sPlayable& playable, float nvolume);
	iterator erase(const_iterator deletable);
	bool getActive() const;
	void setActive(bool value);
};
}

#endif // AUDIOMIXER_HPP
