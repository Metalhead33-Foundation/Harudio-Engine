#include "AudioImporter.hpp"
namespace Software {

Importer::Importer(Abstract::sFIO fio)
	: file(fio)
{
	;
}
long Importer::writeToBuffer(float* input, size_t frameNum)
{
	file.readf(input,frameNum);
}

}
