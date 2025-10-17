#include "TuringMachine.h"

void TuringMachine::add_TransitionRule(TransitionRule rule){
	rules.push_back(rule);
}

TuringMachine TuringMachine:: operator++(int) {
	TuringMachine temp = *this;
	for (int i : final_state) {
		if (i == current_state) { return *this; }
	}
	TransitionRule rule;
	bool flag = false;
	for (TransitionRule& i : rules) {
		if (current_state == i.current_state && tape.body[tape.pointer] == i.current_symbol) {
			rule = i;
			flag = true;
		}
	}
	if (flag == false) {
		cerr << "rule find error" << endl;
		return *this;
	}

	if (rule.move_is_first) {
		tape.move(rule.move_direction);
		tape.write(rule.new_symbol);
	}
	else {
		tape.write(rule.new_symbol);
		tape.move(rule.move_direction);
	}
	current_state = rule.new_state;
	tape.print();
	return temp;
}

void TuringMachine::run(bool log) {
	while(true) {
		for (int i : final_state) {
			if (i == current_state) { return; }
		}
		TransitionRule rule;
		bool flag = false;
		for (TransitionRule &i : rules) {
			if (current_state == i.current_state && tape.body[tape.pointer] == i.current_symbol) {
				rule = i;
				flag = true;
			}
		}
		if (flag == false) { 
			cerr << "rule find error" << endl; 
			return; 
		}

		if (rule.move_is_first) {
			tape.move(rule.move_direction);
			tape.write(rule.new_symbol);
		}
		else {
			tape.write(rule.new_symbol);
			tape.move(rule.move_direction);
		}
		current_state = rule.new_state;
		if (log) tape.print();
	}
}

void TuringMachine::readRule(string filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cerr << "Error: unable to open file " << filename << endl;
		return;
	}

	string line;

	
	if (getline(file, line)) {
		vector<char> tapeData(line.begin(), line.end());
		tape.create(tapeData);
	}

	
	if (getline(file, line)) {
		current_state = stoi(line);
	}

	
	while (getline(file, line)) {
		if (line.empty()) continue;

		if (line.find("end:")==0) { 
			
			string states = line.substr(4);
			stringstream ss(states);
			int st;
			while (ss >> st) {
				final_state.push_back(st);
			}
			break;
		}

		stringstream ss(line);
		TransitionRule rule;

		ss >> rule.move_is_first
			>> rule.current_state
			>> rule.new_state
			>> rule.current_symbol
			>> rule.new_symbol
			>> rule.move_direction;

		rules.push_back(rule);
	}

	file.close();
}

void TuringMachine::printRules() {
	for (int i = 0; i < rules.size(); i++) {
		cout << "Rule " << i << ":" << endl;
		rules[i].print();
	}
}

void TuringMachine::edit_TransitionRule(TransitionRule rule, int position) {
	if (position<1 or position>rules.size()) {
		cerr << "incorrect position" << endl;
		return;
	}
	rules[position - 1] = rule;
}

