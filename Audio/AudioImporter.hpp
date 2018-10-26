#ifndef AUDIOIMPORTER_IMP_HPP
#define AUDIOIMPORTER_IMP_HPP
#include "../harudio-headers/Audio/AudioImporter.hpp"
#include "../harudio-headers/Io/FIO.hpp"
#include "../Sound/SoundFile.hpp"

namespace Software {

class Importer : public Audio::Importer
{
private:
	Audio::SoundFile file;
public:
	Importer(Abstract::sFIO fio);
	long writeToBuffer(float* input, size_t frameNum);
};

}

#endif // AUDIOIMPORTER_IMP_HPP
