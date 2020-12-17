#include <iostream>
#include <string>
#include "prefix.h"

using namespace std;

int main()
{
	prefix Test;
	string input;
	setlocale(LC_ALL, "Rus");
	cout << "Отрицательные степени вводить в скобках. \nВложенные функции в функциях одного аргумента не подлежат преобразованию в префикс\n";
	while (input != "exit")
	{
		cout << "\nВведите выражение:\n";
		getline(cin, input);
		try {
			Test.make_prefix(input);
			cout << "Результат преобразования: " << Test.print_prefix() << endl;
			cout << "Результат вычисления: " << Test.get_result() << endl;
		}
		catch(const char* error)
		{
			cout << error << endl;
		}
	}
}
