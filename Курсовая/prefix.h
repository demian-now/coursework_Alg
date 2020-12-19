#pragma once
#include "List.h"

class prefix {
private:

	BiList calculate;
	BiList temp;

	void get_normal_string();
	void break_into_pieces(string);
	void get_prefix();
	friend string make_func(string input);
	void clone();
	void clear();

public:
	void make_prefix(string input);
	string print_prefix();
	string get_result();

};