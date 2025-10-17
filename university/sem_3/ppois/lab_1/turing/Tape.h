#pragma once
#include "turing_header.h"

class Tape {
public:
	deque <char> body;
	int pointer = 0;
	int begin = 0;
	int end = 0;

	char read();
	void write(char symbol);
	void move(int direction);
	void print();
	void create(vector<char> a);
};