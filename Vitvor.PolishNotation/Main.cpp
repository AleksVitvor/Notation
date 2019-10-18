#include <iostream>
#include <stack>
#include <sstream>
using namespace std;
int main() {
	setlocale(0, "rus");
	bool flag = false;
	string str;
	string str1{};
	string result{};
	cout << "Введите строку: ";
	getline(cin, str);
	short i = 0;
	while (str[i] != '=')
	{
		result += str[i];
		i++;
	}
	str.erase(0, i + 1);
	str.erase(str.length() - 1, 1);
	for (short i = 0; i < str.length(); i++)
	{
		if ((str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') && str[i - 1] != ')' && str[i - 1] != '(')
		{
			str1 += ' ';
			str1 += str[i];
		}
		else
		{
			str1 += str[i];
		}
	}
	stack<int> numbers;
	stack<char> symbols;
	int value = 0;
	short j = 0;
	char sign;
	char sign1;
	for (short i = 0; i < str1.length(); i++)
	{
		if (str1[i] >= '0' && str1[i] <= '9')
		{
			value = value * pow(10, j);
			j++;
			value = value + (str1[i] - 48);
		}
		else if (str1[i] == ' ')
		{

			numbers.push(value);
			j = 0;
			value = 0;
		}
		else
		{
			sign = str1[i];
			if (sign == '(')
			{
				flag = false;
				symbols.push(sign);
				continue;
			}
			else if (sign == ')')
			{
				numbers.push(value);
				value = 0;
				j = 0;
				while (symbols.top() != '(')
				{
					sign1 = symbols.top();
					symbols.pop();
					int left = numbers.top();
					numbers.pop();
					int right = numbers.top();
					if (!flag)
					{
						cout << right << " " << left << " ";
						flag = true;
						cout << sign1 << " ";
					}
					else
					{
						cout << right << " ";
						cout << sign1 << " ";
					}
					numbers.pop();
					switch (sign1) {
					case '+':   numbers.push(right + left); break;
					case '-':   numbers.push(right - left); break;
					case '*':   numbers.push(right * left); break;
					case '/':   numbers.push(right / left); break;
					default:
						cout << "неопознанный оператор " << sign << endl;
						return 0;
					}
				}
			}
			else if (symbols.size() == 0)
			{
				symbols.push(sign);
				continue;
			}
			else if (symbols.top() == '*' || symbols.top() == '/')
			{
				sign1 = symbols.top();
				symbols.pop();
				int left = numbers.top();
				numbers.pop();
				int right = numbers.top();
				numbers.pop();
				if (!flag)
				{
					cout << right << " " << left << " ";
					flag = true;
					cout << sign1 << " ";
				}
				else
				{
					cout << right << " ";
					cout << sign1 << " ";
				}
				switch (sign1) {
				case '+':   numbers.push(right + left); break;
				case '-':   numbers.push(right - left); break;
				case '*':   numbers.push(right * left); break;
				case '/':   numbers.push(right / left); break;
				default:
					cout << "неопознанный оператор " << sign << endl;
					return 0;
				}
			}
			symbols.push(sign);
			if (symbols.top() == ')')
			{
				symbols.pop();
				symbols.pop();
			}
		}
		
	}
	if (symbols.size() != 0)
	{
		while (symbols.size() != 0)
		{
			sign1 = symbols.top();
			symbols.pop();
			int left = numbers.top();
			numbers.pop();
			int right = numbers.top();
			numbers.pop();
			if (!flag)
			{
				cout << right << " " << left << " ";
				flag = true;
				cout << sign1 << " ";
			}
			else
			{
				cout << sign1 << " ";
			}
			switch (sign1) {
			case '+':   numbers.push(right + left); break;
			case '-':   numbers.push(right - left); break;
			case '*':   numbers.push(right * left); break;
			case '/':   numbers.push(right / left); break;
			default:
				cout << "неопознанный оператор " << sign1 << endl;
				return 0;
			}
		}
	}
	cout << endl << result << "=" << numbers.top() << ";" << endl;
	return 0;
}