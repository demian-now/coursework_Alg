#include <iostream>
#include <string>
#include "prefix.h"

using namespace std;

int main()
{
	prefix Test;
	string input;
	setlocale(LC_ALL, "Rus");
	cout << "Отрицательные степени вводить в скобках.\n Для вызода введите exit\n ";
	while (1)
	{
		cout << "\nВведите выражение:\n";
		getline(cin, input);
		if (input == "exit")
			break;
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
