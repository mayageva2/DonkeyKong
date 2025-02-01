#ifndef _STEPS_H
#define _STEPS_H
#include <list>
#include <string>
#include <ctime> 

class Steps
{
	long randomSeed = 0;
	char colorModeGame;
	std::list<std::pair<size_t, char>> steps; // pair: iteration, step
public:
	void saveSteps(const std::string& filename) const;
	static bool checkSaveMode(int argc, char** argv);
	void loadSteps(const std::string& filename);
	long getRandomSeed() const {
		return randomSeed;
	}
	void setRandomSeed(long seed) {
		randomSeed = seed;
	}
	void addStep(size_t iteration, char step) {
		steps.push_back({ iteration, step });
	}
	bool isNextStepOnIteration(size_t iteration) const {
		return !steps.empty() && steps.front().first == iteration;
	}
	char popStep() {
		char step = steps.front().second;
		steps.pop_front();
		return step;
	}
	void setSeed() { randomSeed = static_cast<int>(time(0));}
	char getColorMode() const {return colorModeGame;}
	void setColorMode(char colorMode) { colorModeGame=colorMode; }
	bool isEmpty() const {return steps.empty();}
	void clear() { steps.clear(); }
};
#endif
