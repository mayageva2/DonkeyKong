#include "results.h"
#include <limits>
#include <iostream> 
#include <fstream>

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
	while (!results_file.eof() && size-- != 0) {
		size_t iteration;
		int result;
		int score;
		results_file >> iteration >> result >> score;
		addResult( iteration, static_cast<ResultValue>(result), score);
	}
}