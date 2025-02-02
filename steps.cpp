#include "steps.h"
#include <fstream>
#include <iostream>

void Steps::saveSteps(const std::string& filename) const  //saves steps to file
{
	std::ofstream steps_file(filename);
	steps_file << randomSeed << '\n' << steps.size() << '\n' << colorModeGame;
	for (const auto& step : steps) {
		steps_file << '\n' << step.first << ' ' << step.second;
	}
	steps_file.close();
}

bool Steps::checkSaveMode(int argc, char** argv) //checks if should save data
{
	for (int i = 1; i < argc; ++i)
	{
		if (std::string(argv[i]) == "-save")
			return true;
	}
	return false;
}

void Steps::loadSteps(const std::string& filename) //loads steps from file
{
	std::ifstream steps_file(filename);
	steps_file >> randomSeed; //read randomSeed
	size_t size; 
	steps_file >> size;// read number of steps
	steps_file >> colorModeGame; //read colorMode
	while (!steps_file.eof() && size >0 ) {
		size_t iteration;
		char step;
		steps_file >> iteration >> step;
		addStep(iteration, step);
		size--;
	}
	steps_file.close();
}