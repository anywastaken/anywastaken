#pragma once
#include "turing_header.h"

class TransitionRule {
public:
	bool move_is_first;
	int current_state;
	int new_state;
	char current_symbol;
	char new_symbol;
	int move_direction;

	void print();
};