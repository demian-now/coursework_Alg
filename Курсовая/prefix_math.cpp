#include "prefix_math.h"
#include "prefix.h"
#include <iostream>

string make_func(string input) //расчёт функций одного аргумента
{
	string func, num;
	char control = 0;
	for (size_t i = 0; i < input.size()-1; i++)
	{
		if (input[i] == '(' && control == 0)
		{
			control++;
			continue;
		}
		if (control)
			num += input[i];
		else func += input[i];
	}
	double result = 0, number;
	if (num == "pi")
		number = pi;
	else if (num == "e")
		number = e;
	else
	{
		prefix temp; //обработка неконстантного или составного аргумента 
		temp.break_into_pieces(num);
		temp.get_normal_string();
		temp.clone();
		temp.calculate.reverse();
		number = stod(temp.get_result());
	}
	if (func == "cos") result = cos(number);
	else if (func == "sin") result = sin(number);
	else if (func == "tg") result = tan(number);
	else if (func == "ctg") result = 1 / tan(number);
	else if (func == "ln") result = log(number);
	else if (func == "log") result = log10(number);
	else if (func == "sqrt") result = sqrt(number);
	else if (func == "abs") result = abs(number);
	else throw "Unknown error";
	return to_string(result);
}

string make_operator(string input, string number_1, string number_2) //вычисления для операторов
{
	double result = 0, num_1, num_2;
	if (number_1 == "pi")
		num_1 = pi;
	else if (number_1 == "e")
		num_1 = e;
	else num_1 = stod(number_1);
	if (number_2 == "pi")
		num_2 = pi;
	else if (number_2 == "e")
		num_2 = e;
	else num_2 = stod(number_2);
	if (input == "+") result = num_1 + num_2;
	if (input == "-") result = num_1 - num_2;
	if (input == "*") result = num_1 * num_2;
	if (input == "/") result = num_1 / num_2;
	if (input == "^") result = pow(num_1, num_2);
	return to_string(result);
};