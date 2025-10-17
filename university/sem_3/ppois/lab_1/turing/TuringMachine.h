#pragma once
#include "turing_header.h"
#include "Tape.h"
#include "TransitionRule.h"

class TuringMachine {
public:
	Tape tape;
	vector<TransitionRule> rules;
	int current_state = 0;
	vector<int> final_state;

	TuringMachine() {}

	TuringMachine(string filename) {
		readRule(filename);
	}

	void add_TransitionRule(TransitionRule rule);
	void edit_TransitionRule(TransitionRule rule, int position);
	void run(bool log);
	void readRule(string filename);
	void printRules();

	TuringMachine operator++(int);
};