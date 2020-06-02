
#include "StringList.h"
#include <iostream>


int main()
{
	CStringList list;
	list.AppendFront("4");
	list.AppendFront("3");
	list.AppendFront("2");
	list.AppendFront("1");

	for (auto it = list.rbegin(); it != list.rend(); ++it)
	{
		std::cout << *it;
	}
	std::cout << "\n";
	for (auto it = list.begin(); it != list.end(); ++it)
	{
		std::cout << *it;
	}
	std::cout << "\n";
	for (const auto it : list)
	{
		std::cout << it;
	}
	std::cout << "\n";
	return 0;
}