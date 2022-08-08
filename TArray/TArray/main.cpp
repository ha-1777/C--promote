#include <iostream>
#include "TArray.hpp"
#include "TList.hpp"

int main()
{
	TArray<int> arr = TArray<int>();
	 arr.reserve(2);
	arr.push(1);
	arr.push(2);
	arr.push(3);
	arr.push(4);
	arr.insert(1, 3);
	arr.remove(1);
	arr.pop();
	arr.clear();
	int index = arr.findIndex(3);

	//实现双向链表以下api
	auto list1 = new TList<int>();
	auto node1 = list1->push(1);
	list1->push(2);
	list1->push(3);

	auto node3 = list1->insert(3, 6);
	auto ret = list1->find(6);
	list1->remove(3);
	list1->popAll();

	delete list1;

	return 0;
 }