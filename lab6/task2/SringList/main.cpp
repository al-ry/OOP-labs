
#include "StringList.h"
#include <iostream>


int main()
{
	CStringList list;

	list.AppendBack("3");
	list.AppendBack("2");
	list.AppendBack("1");
	list.AppendFront("5");
	list.AppendFront("6");
	list.AppendFront("7");
	list.AppendFront("8");

	CStringList list2;
	
	list2 = list;

	for (auto it = list.rbegin(); it !=
		list.rend(); ++it)
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