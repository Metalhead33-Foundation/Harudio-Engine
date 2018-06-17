#include "SongLibrary.hpp"
#include "../Io/SoundFile.hpp"
namespace Sound {

SongLibrary::SongLibrary()
{
	;
}
void SongLibrary::fillLibrary()
{
	lib.clear();
	lib.resize(0);
	stringVector paths = listCreator(folderPath);
	for(auto it = paths.begin(); it != paths.end(); ++it)
	{
		Song tmp;
		auto file = sys->openRead(*it);
		auto sndfile = Audio::SoundFile::createSoundFile(file);
		tmp.fullPaath = *it;
		tmp.title = sndfile->getString(SF_STR_TITLE);
		tmp.album = sndfile->getString(SF_STR_ALBUM);
		tmp.artist = sndfile->getString(SF_STR_ARTIST);
		tmp.date = sndfile->getString(SF_STR_DATE);
		lib.push_back(tmp);
	}
}

}
