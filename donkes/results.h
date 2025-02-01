#ifndef _RESULTS_H
#define _RESULTS_H
#include <list>
#include <string>
#include <tuple>
#include <iostream>

class Results
{
public:
	enum ResultValue { hitGhost, hitBarrel, finished, falling, noResult };
	std::string filename;
private:
	std::list<std::tuple<size_t, ResultValue, int>> results; // pair: iteration, result
public:
	void loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration);
	void addResult(size_t iteration, ResultValue result, size_t score) {
		results.push_back({ iteration, result, score });
	}
	std::tuple<size_t, ResultValue, int> popResult() {
		if (results.empty()) return { 0, Results::noResult, 0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	void clear() { results.clear(); }
	size_t getNextEnemyIteration() const;
	bool isEmpty() { return results.empty(); }
	std::tuple<size_t, Results::ResultValue, int> getFirstResult() const
	{
			return results.front();  
	}
	bool isFinishedBy(size_t iteration) const 
	{
		return results.empty() || std::get<0>(results.back()) < iteration;
	}
	int getLastResultIteration()const {return std::get<0>(results.back());}
	int getSize() { return results.size(); }
};
#endif
