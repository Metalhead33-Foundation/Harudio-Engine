/*
 * File:   StdStream.hpp
 * Author: metalhead33
 *
 * Created on 2017. február 23., 17:46
 */

#ifndef STDSTREAM_HPP
#define STDSTREAM_HPP
#include "FIO.hpp"
#include <cstdio>
#include <string>
class StdStream : public Abstract::FIO {
public:
	StdStream();
	StdStream(std::string newpath, bool ro = false);
	~StdStream();
	virtual int64_t read(void* data, int64_t size);
	virtual int64_t seek(int64_t position);
	virtual int64_t tell();
	virtual int64_t size();
	virtual int64_t write(void* data, int64_t size);
	virtual char getc();
	std::string GetPath();
	void close();
	bool IsActive();
	bool open(std::string newpath, bool ro = false);

	static Abstract::sFIO createReader(std::string newpath);
	static Abstract::sFIO createWriter(std::string newpath);

	virtual Abstract::byteBuffer loadIntoBuffer();
	virtual std::string stringize();
private:
	std::string path;
	FILE* chandle;
	bool active;
};
#endif /* STDSTREAM_HPP */
