#include "results.h"
#include <limits>
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
