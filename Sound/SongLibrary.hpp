#ifndef SONGLIBRARY_HPP
#define SONGLIBRARY_HPP
#include "../Io/FIOSys.hpp"
#include <vector>
#include <string>
#include <functional>
#include "../Io/SoundFile.hpp"
namespace Sound {

struct Song
{
	typedef std::function<Abstract::sFIO(const std::string&)> FileOpener;
	std::string fullPath;
	std::string title;
	std::string artist;
	std::string album;
	std::string date;
	Audio::sSoundFile getSong(const Abstract::FIOSys& sys) const;
	Audio::sSoundFile getSong(const FileOpener& opener) const;
};

DEFINE_CLASS(SongLibrary)
class SongLibrary
{
public:
	typedef std::vector<std::string> stringVector;
	typedef std::function<stringVector(const std::string&)> ListCreator;
	typedef std::vector<Song> SongLib;
	typedef SongLib::const_iterator SongIterator;
private:
	SongLib lib;
	std::string folderPath;
	const Abstract::sFIOSys sys;
	const ListCreator listCreator;
	SongLibrary(const std::string& path, const ListCreator& creator, Abstract::sFIOSys sys);
	SongLibrary(const ListCreator& creator, const Song::FileOpener& opener);
public:
	static sSongLibrary create(const std::string& path, const ListCreator& creator, Abstract::sFIOSys sys);
	static sSongLibrary create(const ListCreator& creator, const Song::FileOpener& opener);
	const Song& getSong(size_t id) const;
	const Song& operator[](size_t id) const;
	size_t getLibrarySize() const;
	SongIterator begin() const;
	SongIterator end() const;
};

}
#endif // SONGLIBRARY_HPP
