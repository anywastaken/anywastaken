#include "Tape.h"

void Tape::move(int direction) {
	if (direction == 0) { return; }
	if (pointer == begin && direction < 0) { body.push_front('_'); }
	if (pointer == end && direction > 0) { body.push_back('_'); }
	pointer += direction;
}

char Tape::read() {
	return body[pointer];
}

void Tape::write(char symbol) {
	body[pointer] = symbol;
}

void Tape::print() {
	cout << "...";
	for (int i = begin; i <= end; i++) { cout << body[i]; }
	cout << "..." << endl;
}

void Tape::create(vector<char> a) {
	body.clear();
	for (char i : a) {
		body.push_back(i);
	}
	end = a.size() - 1;
}