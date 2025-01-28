#ifndef _RESULTS_H
#define _RESULTS_H
#include <list>
#include <string>

class Results
{
public:
	enum ResultValue { hitGhost, hitBarrel, finished, noResult };
private:
	std::list<std::pair<size_t, ResultValue>> results; // pair: iteration, result
public:
	void saveResults(const std::string& filename) const;
	void addResult(size_t iteration, ResultValue result) {
		results.push_back({ iteration, result });
	}
	std::pair<size_t, ResultValue> popResult() {
		if (results.empty()) return { 0, Results::noResult };
		auto result = results.front();
		results.pop_front();
		return result;
	}
	bool isFinishedBy(size_t iteration) const {
		return results.empty() || results.back().first <= iteration;
	}
};
#endif
