#include "stack.hpp"
#include <stdlib.h>
#include <string>

int main()
{
	stack<int> Stack;
	std::string str;
	unsigned int i = 0;

	std::cout << "Add an element: +<Element>\nShow the last element: ?\nPop the last element: -\nShow the stack: =\n\n";
	std::getline(std::cin, str);

	while (str[i] != '\0')
	{
		switch (str[i])
		{
		case '+':
		{
					if (str[i + 1] == ' ' || str[i + 1] == '\0')
						std::cout << "Error! Error has occurred while reading arguments\n";
					else
					{
						Stack.push(stoi(str.substr(i + 1)));
					}
					break;
		}
		case '?':
		{
					std::cout << Stack.top();
					std::cout << std::endl;
					break;
		}
		case '-':
		{
					Stack.pop();
					break;
		}
		case '=':
		{
					Stack.print(std::cout);
					break;
		}
		defoult: break;
		}
		i++;
	}

	system("pause");
	return 0;
}
