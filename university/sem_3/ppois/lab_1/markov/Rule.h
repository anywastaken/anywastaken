#pragma once
#include <string>

using namespace std;

class Rule {
public:
	string pattern;
	string result;
	Rule() {}

	Rule(string newpattern, string newresult) {
		pattern = newpattern;
		result = newresult;
	}

	bool operator==(const Rule& other) const {
		return (pattern == other.pattern &&
			result == other.result);
	}
};