#ifndef _STEPS_H
#define _STEPS_H
#include <list>
#include <string>
#include <ctime> 

class Steps
{
	long randomSeed = 0; // Seed for randomization
	char colorModeGame; // Game color mode
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	void saveSteps(const std::string& filename) const; // Save steps to a file
	static bool checkSaveMode(int argc, char** argv); // Check if save mode
	void loadSteps(const std::string& filename);  // Load steps from a file
	long getRandomSeed() const { //get seed in file
		return randomSeed;
	}
	void setRandomSeed(long seed) { //set new seed 
		randomSeed = seed;
	}
	void addStep(size_t iteration, char step) { //add step to lst
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const { //checks if next step on iteration
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep() { //pop step from list
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}
	void setSeed() { randomSeed = static_cast<int>(time(0));} //set seed according to time
	char getColorMode() const {return colorModeGame;} //get color mode from file
	void setColorMode(char colorMode) { colorModeGame=colorMode; } //set color mode
	bool isEmpty() const {return steps.empty();} //check if list is empty
	void clear() { steps.clear(); } //clears list
};
#endif
