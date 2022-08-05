#include <iostream>
#include "TArray.h"
#include "TList.h"

int main()
{
	TArray arr = TArray();
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
	//auto node2 = list1.push(2);
	//auto node3 = list1.insert(node2, 3);
	//auto ret = list1.find(2);
	//list1.remove(node2);
	//list1.popAll();

	return 0;
 }