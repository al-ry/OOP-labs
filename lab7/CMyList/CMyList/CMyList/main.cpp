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
	CMyList<int> list1(list);
	//CMyList<int> list1 = std::move(list);
	//CMyList<int> list2(std::move(list1));
	CMyList<int>list2 = (list1);
	return 0;
}