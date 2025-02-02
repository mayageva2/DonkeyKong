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
	void reportResultError(const std::string& message, const std::string& filename, size_t iteration) const;
	void addResult(size_t iteration, ResultValue result, size_t score) {
		results.push_back({ iteration, result, score });
	}
	std::tuple<size_t, ResultValue, int> popResult() {
		if (results.empty()) return { 0, Results::noResult, 0 };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || std::get<0>(results.back()) < iteration;
	}
	void clear() { results.clear(); }
	size_t getNextEnemyIteration() const;
	bool isEmpty() const { return results.empty(); }
	std::tuple<size_t, Results::ResultValue, int> getFirstResult() const {return results.front();}
	size_t getLastResultIteration() { return std::get<0>(results.back()); }
	size_t getSize() const { return results.size(); }
};
#endif
