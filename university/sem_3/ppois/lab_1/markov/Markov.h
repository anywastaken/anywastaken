#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Rule.h"

using namespace std;

class Markov {
	vector<Rule> rules;
public:
	string start;

	Markov(){}

	Markov(string filename) {
		readRule(filename);
	}

	void run(bool log);
	void deleteRule(string pattern, string result);
	void addRule(string pattern, string result);
	void editRule(string pattern, string result, int position);
	void readRule(string filename);
	void printRules();

	Markov operator++(int);
};

