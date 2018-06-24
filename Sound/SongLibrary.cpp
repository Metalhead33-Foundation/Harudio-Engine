#include "SongLibrary.hpp"
namespace Sound {

Audio::sSoundFile Song::getSong(const Abstract::FIOSys &sys) const
{
	if(sys.exists(fullPath))
	{
		auto file = sys.openRead(fullPath);
		return Audio::SoundFile::createSoundFile(file);
	} else return nullptr;
}
Audio::sSoundFile Song::getSong(const FileOpener& opener) const
{
	auto file = opener(fullPath);
	return Audio::SoundFile::createSoundFile(file);
}

SongLibrary::SongLibrary(const std::string &path, const ListCreator &creator, Abstract::sFIOSys sys)
	: folderPath(path), listCreator(creator), sys(sys)
{
	stringVector paths = listCreator(folderPath);
	for(auto it = paths.begin(); it != paths.end(); ++it)
	{
		Song tmp;
		auto file = sys->openRead(*it);
		auto sndfile = Audio::SoundFile::createSoundFile(file);
		tmp.fullPath = *it;
		tmp.title = sndfile->getString(SF_STR_TITLE);
		tmp.album = sndfile->getString(SF_STR_ALBUM);
		tmp.artist = sndfile->getString(SF_STR_ARTIST);
		tmp.date = sndfile->getString(SF_STR_DATE);
		lib.push_back(tmp);
	}
}
SongLibrary::SongLibrary(const std::string& path, const ListCreator& creator, const Song::FileOpener& opener)
	: folderPath(path), listCreator(creator), sys(nullptr)
{
	stringVector paths = listCreator(folderPath);
	for(auto it = paths.begin(); it != paths.end(); ++it)
	{
		Song tmp;
		auto file = opener(*it);
		auto sndfile = Audio::SoundFile::createSoundFile(file);
		tmp.fullPath = *it;
		if(sndfile->getString(SF_STR_TITLE)) tmp.title = sndfile->getString(SF_STR_TITLE);
		if(sndfile->getString(SF_STR_ALBUM)) tmp.album = sndfile->getString(SF_STR_ALBUM);
		if(sndfile->getString(SF_STR_ARTIST)) tmp.artist = sndfile->getString(SF_STR_ARTIST);
		if(sndfile->getString(SF_STR_DATE)) tmp.date = sndfile->getString(SF_STR_DATE);
		lib.push_back(tmp);
	}
}
sSongLibrary SongLibrary::create(const std::string& path, const ListCreator& creator, Abstract::sFIOSys sys)
{
	return sSongLibrary(new SongLibrary(path,creator,sys));
}
sSongLibrary SongLibrary::create(const std::string& path, const ListCreator& creator, const Song::FileOpener& opener)
{
	return sSongLibrary(new SongLibrary(path,creator,opener));
}
const Song& SongLibrary::getSong(size_t id) const
{
	return lib[id];
}
const Song& SongLibrary::operator[](size_t id) const
{
	return lib[id];
}
size_t SongLibrary::getLibrarySize() const
{
	return lib.size();
}
SongLibrary::SongIterator SongLibrary::begin() const
{
	return lib.begin();
}
SongLibrary::SongIterator SongLibrary::end() const
{
	return lib.end();
}

}
