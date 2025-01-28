#include "steps.h"
#include <fstream>
#include <iostream>

void Steps::saveSteps(const std::string& filename) const 
{
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size();
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}

bool Steps::checkSaveMode(int argc, char** argv)
{
	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "-save")
			return true;
	}
	return false;
}