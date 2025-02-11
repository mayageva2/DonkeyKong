#include "results.h"
#include "general.h"
#include <limits>
#include <iostream> 
#include <fstream>
#include <conio.h>


void Results::saveResults(const std::string& filename) const 
{
	std::ofstream results_file(filename);
	results_file << results.size();
	for (const auto& result : results) {
		results_file << '\n' << std::get<0>(result) << ' ' << std::get<1>(result) << ' ' << std::get<2>(result);
	}
	results_file.close();
}

void Results::loadResults(const std::string& filename)
{
	std::ifstream results_file(filename);
	size_t size;
	results_file >> size;
	while (!results_file.eof() && size>0)
	{
		size_t iteration;
		int result;
		int score;
		results_file >> iteration >> result >> score;
		addResult( iteration, static_cast<ResultValue>(result), score);
		size--;
	}
}

void Results::reportResultError(const std::string& message, const std::string& filename, size_t iteration) {
	
	clrscr();
	std::cout << "Screen " << filename << " - " << message << '\n';
	std::cout << "Iteration: " << iteration << '\n';
	std::cout << "Press any key to continue to next screens (if any)" << std::endl;
	_getch();
}

size_t Results::getNextEnemyIteration() const 
{
	if (!results.empty() && ((std::get<1>(results.front()) == hitGhost) || (std::get<1>(results.front()) == hitBarrel)))
	{
		return std::get<0>(results.front()); // number of iteration
	}
	else return std::numeric_limits<size_t>::max(); // a big number we will never reach
}