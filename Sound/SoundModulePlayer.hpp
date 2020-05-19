#ifndef SOUNDMODULEPLAYER_HPP
#define SOUNDMODULEPLAYER_HPP
#include "../Abstract/AudioPlayable.hpp"
#include "../Global/FIO.hpp"
#include "../Wrappers/MhModuleRenderer.hpp"

DEFINE_STRUCT(openmpt_module)

namespace Sound {
class ModulePlayer : public Audio::Playable
{
private:
	Mh::ModuleRenderer mod;
	ModulePlayer(const ModulePlayer& cpy) = delete;
	void operator=(const ModulePlayer& cpy) = delete;
public:
	ModulePlayer(Abstract::sFIO fio);
	ModulePlayer(ModulePlayer&& mov);
	void operator=(ModulePlayer&& mov);
	Audio::FrameCount_T outputTo(const Audio::Output& dst); // Return value: frames transmitted
	bool isPlaying() const; // Is this thing even on?
};
}

#endif // SOUNDMODULEPLAYER_HPP
