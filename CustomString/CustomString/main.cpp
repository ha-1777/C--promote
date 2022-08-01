#include <iostream>
#include "CustomString.h"

int main()
{
	//实现string以下api，内部不能使用string，只能用数组存字符
	auto str1 = CustomString("test1");
	auto str2 = CustomString("test2, test3");
	str1 = str2;
	int m_length = str1.len();
	CustomString sub1 = str1.sub(1, 2);
	//str1.append("append");
	bool equal = str1 == str2;
	int index = str1.find("es");
	//CustomString* ret = str2.split(",");
}
