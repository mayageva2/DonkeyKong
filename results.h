#ifndef _RESULTS_H
#define _RESULTS_H
#include <list>
#include <string>
#include <tuple>
#include <iostream>

class Results
{
public:
	enum ResultValue { hitGhost, hitBarrel, finished, falling, noResult }; //possible result outcomes
	std::string filename; //results file
private:
	std::list<std::tuple<size_t, ResultValue, int>> results; // pair: iteration, result
public:
	void loadResults(const std::string& filename); // Load results from a file
	void saveResults(const std::string& filename) const; // Save results to a file
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration) const; // Report an error
	void addResult(size_t iteration, ResultValue result, size_t score) { // Add a new result
		results.push_back({ iteration, result, score });
	}
	std::tuple<size_t, ResultValue, int> popResult() { // Retrieve and remove the first result, or return default if empty
		if (results.empty()) return { 0, Results::noResult, 0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {  //	// Check if results are finished
		return results.empty() || std::get<0>(results.back()) < iteration;
	}
	void clear() { results.clear(); } // Clear all results
	size_t getNextEnemyIteration() const;  //gets next iterarion
	bool isEmpty() const { return results.empty(); } //Check if empty
	std::tuple<size_t, Results::ResultValue, int> getFirstResult() const {return results.front();} // Get first result
	size_t getLastResultIteration() { return std::get<0>(results.back()); } // Get last result's iteration
	size_t getSize() const { return results.size(); } // Get number of results
};
#endif
