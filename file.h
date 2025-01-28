#ifndef _FILE_H
#define _FILE_H

#include <iostream>
#include <fstream>
#include <string>
class File
{
	std::string filePath;
public:
	explicit File(const std::string& path) : filePath(path) {}
	const std::string& getPath() const { return filePath; }
	virtual ~File() = default;

	File operator+(const File& other) const 
	{
		std::string combinedPath = filePath + "/" + other.filePath;
		return File(combinedPath);
	}
};
#endif
