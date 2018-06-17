#ifndef SONGLIBRARY_HPP
#define SONGLIBRARY_HPP
#include "../Io/FIOSys.hpp"
#include <vector>
#include <string>
#include <functional>
namespace Sound {

struct Song
{
	std::string fullPaath;
	std::string title;
	std::string artist;
	std::string album;
	std::string date;
};

class SongLibrary
{
public:
	typedef std::vector<std::string> stringVector;
	typedef std::function<stringVector(const std::string&)> ListCreator;
private:
	std::vector<Song> lib;
	std::string folderPath;
	const Abstract::sFIOSys sys;
	const ListCreator listCreator;
public:
	SongLibrary();
	void fillLibrary();
};

}
#endif // SONGLIBRARY_HPP
