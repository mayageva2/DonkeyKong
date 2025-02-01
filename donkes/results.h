#ifndef _RESULTS_H
#define _RESULTS_H
#include <list>
#include <string>
#include <tuple>

class Results
{
public:
	enum ResultValue { hitGhost, hitBarrel, finished, falling, noResult };
private:
	std::list<std::tuple<size_t, ResultValue, int>> results; // pair: iteration, result
public:
	void loadResults(const std::string& filename);
	void saveResults(const std::string& filename) const;
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
		return results.empty() || std::get<0>(results.back()) <= iteration;
	}
	void clear() { results.clear(); }
};
#endif
