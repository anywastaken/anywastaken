#include "Markov.h"

void Markov::addRule(string pattern, string result) {
	Rule rule;
	rule.pattern = pattern;
	rule.result = result;
	for (auto i : rules) {
		if (i == rule) {
			//cerr << "rule alredy exist" << endl;
			return;
		}
	}
	rules.push_back(rule);
}

void Markov::deleteRule(string pattern, string result) {
	Rule rule;
	rule.pattern = pattern;
	rule.result = result;
	for (int i = 0; i < rules.size(); i++) {
		if (rules[i] == rule) {
			rules.erase(rules.begin() + i);
			return;
		}
	}
	//cerr << "rule not found" << endl;
}

void Markov::editRule(string pattern, string result, int position) {
	if (position<1 or position>rules.size()) {
		//cerr << "incorrect position" << endl;
		return;
	}

	rules[position - 1].pattern = pattern;
	rules[position - 1].result = result;
}

void Markov::readRule(string filename) {
	fstream file(filename, ios::in);
	if (!file.is_open()) {
		//cerr << "invalid file name" << endl; 
		return;
	}
	getline(file, start);
	string pattern, result;
	while (file >> pattern and file >> result) {
		Rule rule(pattern, result);
		rules.push_back(rule);
	}
	file.close();
}

void Markov::printRules() {
	for (Rule i : rules) {
		cout << i.pattern << " -> " << i.result << endl;
	}
}

void Markov::run(bool log) {
	bool flag = true;
	int counter=0;
	while (flag and counter < 1000) {
		counter++;
		flag = false;
		int n = rules.size(), position;
		for (int i = 0; i < n; i++) {
			position = start.find(rules[i].pattern);
			if (position != string::npos) {
				flag = true;
				start.erase(position, rules[i].pattern.size());
				start.insert(position, rules[i].result);
				if (log) cout << start << endl;
				break;
			}
		}
	}
}

Markov Markov:: operator++(int) {
	Markov temp = *this;
	int n = rules.size(), position;
	for (int i = 0; i < n; i++) {
		position = start.find(rules[i].pattern);
		if (position != string::npos) {
			start.erase(position, rules[i].pattern.size());
			start.insert(position, rules[i].result);
			cout << start << endl;
			break;
		}
	}
	return *this;
}