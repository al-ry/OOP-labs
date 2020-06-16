#include "CMyList.h"
#include <iostream>
int main()
{
	CMyList<int> list;

	list.AppendBack(1);
	list.AppendBack(2);
	list.AppendBack(3);
	list.AppendBack(4);
	list.AppendBack(5);
	for (auto it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it;
	}

	return 0;
}