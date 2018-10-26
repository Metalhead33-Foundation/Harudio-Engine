#ifndef SOUNDFILE_HPP
#define SOUNDFILE_HPP
#include "sndfile.hh"
#include "../harudio-headers/Io/FIO.hpp"
#include <vector>
namespace Audio {

typedef float SoundItem;
struct FramePair
{
	SoundItem left;
	SoundItem right;
};

DEFINE_CLASS(SoundFile)
class SoundFile : public SndfileHandle
{
private:
	const Abstract::sFIO ioHandle;
public:
	typedef std::vector<SoundItem> FrameVector;
	SoundFile(Abstract::sFIO nhandle, int mode = SFM_READ,
	  int format = 0, int channels = 0, int samplerate = 0);
	static sSoundFile createSoundFile(Abstract::sFIO nhandle, int mode = SFM_READ,
		  int format = 0, int channels = 0, int samplerate = 0);
	size_t bufferSound(FrameVector& buff, size_t* incrementer);
};

}
extern SF_VIRTUAL_IO sndFileIO;

#endif // SOUNDFILE_HPP
