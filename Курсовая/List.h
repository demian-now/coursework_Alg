#pragma once
#include <cstddef>
#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string  data;
	Node* prev = NULL;
	Node* next = NULL;
};

class BiList
{
public:
	BiList();
	~BiList();
	void push_back(string);
	void push_front(string);
	void pop_back();
	void pop_front();
	void remove(size_t);
	void insert(string,size_t);
	string at(size_t);
	string top();
	size_t get_size();
	void set(size_t index, string value);
	void print_to_console();
	bool isEmpty();
	void reverse();
	void clear();

private:
	Node* head; 
	Node* last;
	size_t size;
};