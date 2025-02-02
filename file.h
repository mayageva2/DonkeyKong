#ifndef _FILE_H
#define _FILE_H

#include <iostream>
#include <fstream>
#include <string>

class File
{
	std::string filePath; //file adress
public:
	explicit File(const std::string& path) : filePath(path) {} //constructor
	const std::string& getPath() const { return filePath; } //returns adress of file
	virtual ~File() = default;  //destructor

	File operator+(const File& other) const  //+ operator
	{
		std::string combinedPath = filePath + "/" + other.filePath;
		return File(combinedPath);
	}
};
#endif
