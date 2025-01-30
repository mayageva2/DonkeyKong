#include "steps.h"
#include <fstream>
#include <iostream>

void Steps::saveSteps(const std::string& filename) const 
{
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size() << '\n' << colorModeGame;
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

void Steps::loadSteps(const std::string& filename)
{
	std::ifstream steps_file(filename);
	steps_file >> randomSeed; //read randomSeed
	steps_file >> colorModeGame; //read colorMode
	size_t size;
	steps_file >> size;// read number of steps
	while (!steps_file.eof() && size-- != 0) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		addStep(iteration, step);
	}
	steps_file.close();
}