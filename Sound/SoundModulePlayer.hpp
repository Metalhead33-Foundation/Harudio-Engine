#ifndef SOUNDMODULEPLAYER_HPP
#define SOUNDMODULEPLAYER_HPP
#include "../Abstract/AudioSeekable.hpp"
#include "../Global/FIO.hpp"
#include "../Wrappers/MhModuleRenderer.hpp"

DEFINE_STRUCT(openmpt_module)

namespace Sound {
DEFINE_CLASS(ModulePlayer)
class ModulePlayer : public Audio::Seekable
{
private:
	Mh::ModuleRenderer mod;
	Status state;
	ModulePlayer(const ModulePlayer& cpy) = delete;
	void operator=(const ModulePlayer& cpy) = delete;
public:
	ModulePlayer(Abstract::sFIO fio);
	ModulePlayer(ModulePlayer&& mov);
	void operator=(ModulePlayer&& mov);
	Audio::FrameCount_T outputTo(const Audio::Output& dst); // Return value: frames transmitted

	Status getState() const;
	void play();
	void pause();
	void stop();
	bool isLooping() const;
	void setLooping(bool looping);

	double seek(double seconds, SeekPos whence = SeekPos::SET);
	double tell() const;
	double size() const;
};
}

#endif // SOUNDMODULEPLAYER_HPP
