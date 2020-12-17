#include "prefix.h"
#include "prefix_math.h"

bool isOperator(string oper, size_t index = 0, size_t ctrl = 0) // + - * / ^
{
	if(ctrl==0 && oper[1] >= '0' && oper[1] <= '9')
		return false;
	if (oper[index] == '+' || oper[index] == '-' || oper[index] == '*' || oper[index] == '/' || oper[index] == '^')
		return true;
	return false;
}

char isFunc(string oper, size_t index=0) //cos, sin, tg, ctg, ln, log, sqrt, abs
{
	if (oper[index] == 't' && oper[index + 1] == 'g') //tg
		return 2;
	else if (oper[index] == 'l' && oper[index + 1] == 'n') //ln
		return 2;
	else if (oper[index] == 'c' && oper[index + 1] == 'o' && oper[index + 2] == 's') //cos
		return 3;
	else if (oper[index] == 'c' && oper[index + 1] == 't' && oper[index + 2] == 'g') //ctg
		return 3;
	else if (oper[index] == 'l' && oper[index + 1] == 'o' && oper[index + 2] == 'g') //log
		return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'i' && oper[index + 2] == 'n') //sin
		return 3;
	else if (oper[index] == 'a' && oper[index + 1] == 'b' && oper[index + 2] == 's') //abs
		return 3;
	else if (oper[index] == 's' && oper[index + 1] == 'q' && oper[index + 2] == 'r' && oper[index+3]=='t') //sqrt
		return 4;
	return 0;
}

char isConst(string oper, size_t index=0) //pi, e
{
	if (oper[index] == 'p' && oper[index + 1] == 'i') //pi
		return 2;
	else if (oper[index] == 'e') //e
		return 1;
	return 0;
}

bool isNumber(string str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return true;
	if (str[0] == '-' && str[1] >= '0' && str[1] <= '9')
		return true;
	if (isConst(str))
		return true;
	return false;
}

char get_priority(string oper)
{
	if (isNumber(oper) || isFunc(oper, 0) || isConst(oper, 0))
		return 0;
	if (oper[0] == '+' || oper[0] == '-')
		return 0;
	if (oper[0] == '*' || oper[0] == '/')
		return 1;
	return 2;
}

void prefix::get_normal_string() //���������� ��������� � ������� ��� ������� ���
{
	for (size_t i = 0; i < temp.get_size(); i++)
	{
		string new_str;
		if (isFunc(temp.at(i)))
			continue;
		else if (i == 0 && temp.at(i) == "-" && temp.at(i + 1) != ")" && !isFunc(temp.at(i+1))) //��������� �������� ������ ��� ������� �����
		{
			new_str += temp.at(i) + temp.at(i + 1);
			temp.remove(i + 1);
			temp.set(i, new_str);
		}
		else if (i == 0 && temp.at(i) == "-" && temp.at(i + 1) == ")") //������ ��������� �������� ������, ���� ������� ������
		{
			temp.push_front("0");
			i++;
		}
		else if (temp.at(i) == ")" && i+1<temp.get_size() && temp.at(i + 1) == "-" && !isFunc(temp.at(i + 1))) //��������� �������� ������ ��� ����� ������ ������
		{
			new_str += temp.at(i+1) + temp.at(i + 2);
			temp.remove(i + 1);
			temp.set(i+1, new_str);
		}
	}
}

void prefix::break_into_pieces(string input) //��������� �� ������������
{
	string temp;
	for (size_t i = 0; i < input.size(); i++)
	{
		temp.clear();
		size_t control = 0;
		while (((input[i] >= 48 && input[i] <= 57)||(input[i]=='.')) && i < input.size()) //��������� �����
			temp.push_back(input[i++]);
		if (temp.size() != 0)
		{
			this->temp.push_back(temp);
			temp.clear();
			i--;
			continue;
		}
		if (isOperator(input, i,1)) //��������� ��������� ���������� ��� ������
			temp.push_back(input[i]);
		if (input[i] == '(')
			temp.push_back(')');
		else if (input[i] == ')')
			temp.push_back('(');
		if (temp.size() != 0)
		{
			this->temp.push_back(temp);
			temp.clear();
			continue;
		}
		if (input[i] == ' ')
			continue;
		try
		{
			size_t temp_2 = isFunc(input, i); //��������� ������� ������ ���������
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++) //������� ����� �������
					temp.push_back(input[j]);
				temp_2--;
				size_t control = 0;
				do
				{
					temp_2++;
					if (input[i + temp_2] == '(')
						control++;
					if (input[i + temp_2] == ')')
						control--;
					temp.push_back(input[i + temp_2]);
				} while (control != 0 && input.size() > i + temp_2); //������� ��������� �������
				if (control != 0)
					throw "Incorrect input: error 4";
				this->temp.push_back(temp);
				temp.clear();
				i += temp_2;
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "error symbols: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			return;
		}
		try
		{
			size_t temp_2 = isConst(input, i); //��������� �������� - �� � ����������
			if (temp_2)
			{
				for (size_t j = i; j < i + temp_2; j++)
					temp.push_back(input[j]);
				this->temp.push_back(temp);
				temp.clear();
				i += temp_2-1;
				continue;
			}
		}
		catch (const char* error)
		{
			cout << error << endl;
			cout << "error symbols: ";
			for (size_t j = i; j < input.size(); j++)
				cout << input[j];
			return;
		}
		throw "Unknown symbols";
	}
	get_normal_string();
	this->temp.reverse();
}

void prefix::get_prefix() //��������� ����������� ��������� �� ����������
{
	BiList stack; //��������������� ����
	for (size_t i = 0; i < temp.get_size(); i++)
	{
		if (isNumber(temp.at(i)) || isFunc(temp.at(i))) //� ������ ��������� ����� � ������� ������ ��������� �����
			calculate.push_back(temp.at(i));
		else if (isOperator(temp.at(i))) //��������� ����������
		{
			if (stack.isEmpty())
				stack.push_front(temp.at(i));
			else if (stack.top() == "(")
				stack.push_front(temp.at(i));
			else if (get_priority(temp.at(i)) >= get_priority(stack.top()))
				stack.push_front(temp.at(i));
			else
			{
				while (!stack.isEmpty()&&stack.top() != "(" && get_priority(temp.at(i)) < get_priority(stack.top()))
				{
					calculate.push_back(stack.top());
					stack.pop_front();
				}
				stack.push_front(temp.at(i));
			}
		}
		else if (temp.at(i) == "(")
			stack.push_front(temp.at(i));
		else if (temp.at(i) == ")")
		{
			while (!stack.isEmpty()&&stack.top() != "(")
			{
				calculate.push_back(stack.top());
				stack.pop_front();
			}
			stack.pop_front();
		}
	}
	while (!stack.isEmpty()) //�������� ����� � ���������
	{
		calculate.push_back(stack.top());
		stack.pop_front();
	}
	calculate.reverse();
}

void prefix::make_prefix(string input)
{
	try {
		break_into_pieces(input);
		get_prefix();
		temp.clear();
	}
	catch (const char* error)
	{
		temp.clear();
	}
}

string prefix::print_prefix()
{
	string result;
	for (size_t i = 0; i < calculate.get_size(); i++)
		result += calculate.at(i) + " ";
	return result;
}

string prefix::get_result()
{
	string result;
	size_t control = 0;
	if (calculate.get_size() == 0)
		result = "0";
	else if (calculate.get_size() == 1)
	{
		try {
			if (isFunc(calculate.at(0)))
				calculate.set(0, make_func(calculate.at(0)));
			else if (isConst(calculate.at(0)))
				if (calculate.at(0) == "pi")
					result = to_string(pi);
				else result = to_string(e);
			else if (calculate.at(0) == "-pi")
				result = to_string(-1 * pi);
			else if (calculate.at(0) == "-e")
				result = to_string(-1 * e);
			else if (isNumber(calculate.at(0)))
				result = calculate.at(0);
			else
			{
				calculate.clear();
				throw "Incorrect input: error 1";
			}
		}
		catch (const char* error)
		{
			calculate.clear();
			throw "Incorrect input: error 5";
		}
	}
	else if (calculate.get_size() == 2)
	{
		if (isFunc(calculate.at(1)))
			calculate.set(1, make_func(calculate.at(1)));
		if (calculate.at(0) != "-" && calculate.at(0) != "+")
		{
			calculate.clear();
			throw "Incorrect input: error 2";
		}
		if (calculate.at(0) == "-")
			calculate.set(0, "-" + calculate.at(1));
		else calculate.set(0, calculate.at(1));
		calculate.pop_back();
	} else
	while (calculate.get_size()>1)
	{
		control = 0;
		for (size_t i = 0; i<calculate.get_size(); i++)
		{
			if (calculate.get_size()>=3 && isOperator(calculate.at(i)) && isNumber(calculate.at(i+1)) && isNumber(calculate.at(i+2)))
			{
				calculate.set(i, make_operator(calculate.at(i), calculate.at(i + 1), calculate.at(i + 2)));
				calculate.remove(i + 1);
				calculate.remove(i + 1);
				control++;
			}
			if (isFunc(calculate.at(i)))
			{
				calculate.set(i, make_func(calculate.at(i)));
				control++;
			}
		}
		if (control == 0)
		{
			calculate.clear();
			throw "Incorrect input: error 3";
		}
	}
	result = calculate.at(0);
	calculate.clear();
	return result;
}
