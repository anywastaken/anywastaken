#include "TransitionRule.h"

void TransitionRule::print() {
	cout << "move_is_first=" << move_is_first << ", "
		<< "current_state=" << current_state << ", "
		<< "new_state=" << new_state << ", "
		<< "current_symbol=" << (current_symbol == ' ' ? '_' : current_symbol) << ", "
		<< "new_symbol=" << (new_symbol == ' ' ? '_' : new_symbol) << ", "
		<< "move_direction=" << move_direction
		<< endl;
}