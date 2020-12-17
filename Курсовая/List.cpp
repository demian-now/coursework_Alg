#pragma once
#include "List.h"

BiList::BiList()
{
	head = NULL;
	last = NULL;
	size = 0;
}

BiList::~BiList()
{
	while (head)
	{
		last = head->next;
		delete head;
		head = last;
	}
}

//The function inserts a new node at back of the list.
void BiList::push_back(string value)
{
	Node* temp = new Node;
	temp->next = NULL;
	temp->data = value;
	if (!this->isEmpty())
	{
		temp->prev = last;
		last->next = temp;
		last = temp;
	}
	else {
		temp->prev = NULL;
		head = last = temp;
	}
	size++;
}

//The function inserts a new node at front of the list.
void BiList::push_front(string value)
{
	Node* temp = new Node;
	temp->prev = NULL;
	temp->data = value;
	if (!this->isEmpty())
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else 
	{
		temp->prev = NULL;
		temp->next = NULL;
		head = last = temp;
	}
	size++;
}

//The function deletes the last node in the list.
void BiList::pop_back()
{
	if(size==0)
		return;
	if (size == 1)
	{
		delete last;
		last = head = NULL;
		size--;
		return;
	}
	delete last->next;
	last = last->prev;
	last->next = NULL;
	size--;
}

//The function deletes the first node in the list.
void BiList::pop_front()
{
	if (size == 0)
		return;
	if (size == 1)
	{
		delete head;
		head = last = NULL;
		size--;
		return;
	}
	delete head->prev;
	head->prev = NULL;
	head = head->next;
	size--;
}

//The function gets the value from the node with the number "index".
string BiList::top()
{
	if (head)
		return head->data;
	else throw "is Empty";
}

void BiList::insert(string value, size_t index)
{
	if ((size == 0 && index == 0) || index >= size)
		throw "Incorrect index.";
	if (index == 0)
	{
		this->push_front(value);
		return;
	}
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	Node* temp = new Node;
	temp->data = value;
	temp->next = cursor;
	temp->prev = cursor->prev;
	cursor->prev = temp;
	temp->prev->next = temp;
	size++;
}

//The function gets the number of items in the list
size_t BiList::get_size()
{
	return size;
}

void BiList::set(size_t index, string value)
{
	if (index >= size || index < 0)
		throw"Incorrect index.";
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	cursor->data = value;
}

//The function gets the value from the node with the number "index".
string BiList::at(size_t index)
{
	if (index >= size || index < 0)
		throw "Incorrect index.";
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	return cursor->data;
}

//The function deletes all node in list.
void BiList::clear()
{
	while (head != NULL)
		this->pop_front();
	head = last = NULL;
}

//The function prints all list in console.
void BiList::print_to_console()
{
	Node* cursor = head;
	if (head)
	{
		while (cursor->next)
		{
			std::cout << cursor->data << " ";
			cursor = cursor->next;
		}
		std::cout << cursor->data;
		std::cout << std::endl;
	}
	else throw "List is empty.";
}

//The function checks the list for emptiness.
bool BiList::isEmpty()
{
	if (head==NULL) return true;
	return false;
}

//The function reverses a list.
void BiList::reverse()
{
	if (!head || !head->next)
		return;
	last = head;
	Node* temp = NULL;
	Node* current = head;
	while (current != NULL)
	{
		temp = current->prev;
		current->prev = current->next;
		current->next = temp;
		current = current->prev;
	}
	head = temp->prev;
}

//The function deletes the node with the "index" number.
void BiList::remove(size_t index)
{
	if (index >= size || index < 0)
		throw "Incorrect index.";
	if (index == 0)
	{
		this->pop_front();
		return;
	}
	if (index == size - 1)
	{
		this->pop_back();
		return;
	}
	Node* cursor = head;
	for (size_t i = 0; i < index; i++)
		cursor = cursor->next;
	Node* temp = cursor;
	cursor->prev->next = cursor->next;
	cursor->next->prev = cursor->prev;
	delete temp;
	size--;
}