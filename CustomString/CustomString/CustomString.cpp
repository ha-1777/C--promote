#include "CustomString.h"
#include <string.h>
#include <iostream>
#include <vector>

CustomString::CustomString(const char* str)
{
	//std::cout <<"constructor" << std::endl;
	if (!str)
	{
		return;
	}
	this->m_length = strlen(str);
	m_data = new char[m_length + 1];
	memcpy(m_data, str, m_length * sizeof(char));
	m_data[m_length] = '\0';
}

CustomString::CustomString(const CustomString& obj)
{	
	if (this == &obj)
	{
		return;
	}

	//std::cout << "copy constructor" << std::endl;
	m_length = obj.m_length;
	m_data = new char[m_length + 1];
	memcpy(m_data, obj.m_data, m_length * sizeof(char));
	m_data[m_length] = '\0';
}

CustomString::CustomString(CustomString&& obj) noexcept
{
	if (this == &obj)
	{
		return;
	}

	//exchange将obj.m_data值move到m_data，让后让obj.m_data指向nullptr
	m_data = std::exchange(obj.m_data, nullptr);
	m_length = obj.m_length;
}

CustomString& CustomString::operator=(const CustomString& obj)
{
	if (this == &obj)
	{
		return *this;
	}

	if (m_length < obj.m_length)
	{
		delete[] m_data;
		m_data = new char[obj.m_length + 1];
		m_length = obj.m_length;
		m_data[m_length] = '\0';
	}
	memcpy(m_data, obj.m_data, m_length * sizeof(char));
	return *this;
}

bool CustomString::operator==(const CustomString& obj)
{
	//可以先判断长度是否相等
	if (m_length != obj.m_length)
	{
		return false;
	}

	for (int i=0; i<m_length; i++)
	{
		if (m_data[i] != obj.m_data[i])
		{
			return false;
		}
	}
	return true;
}

CustomString::~CustomString()
{
	if (!m_data)
	{
		return;
	}
	//std::cout << "destructor" << std::endl;
	delete[] m_data;
}

int CustomString::len()
{
	if (!m_data)
	{
		return NULL;
	}

	return m_length; 
}

CustomString CustomString::sub(int start, int end)
{
	if (!m_data)
	{
		return CustomString();
	}

	if (start < 0 || start > std::max(m_length, end) || end > m_length - 1)
	{
		std::cout << "Index is not illegal!" << std::endl;
		return CustomString();
	}
	
	int subLen = end - start + 1;
	char* tempStr = new char[subLen + 1];
	//不对结尾进行赋值\0会导致char*长度出问题
	tempStr[subLen] = '\0';
	memcpy(tempStr, m_data + sizeof(char) * start, subLen);
	CustomString str(tempStr);

	delete[] tempStr;
	return str;	//return会走移动构造，没有移动构造则会走拷贝构造
}

void CustomString::append(const char* str)
{
	if (!str || "" == str)
	{
		return;
	}

	int newStrLen = m_length + strlen(str);
	char* newStr = new char[newStrLen + 1];
	
	memcpy(newStr, m_data, m_length * sizeof(char));
	memcpy(newStr + m_length * sizeof(char), str, strlen(str));
	newStr[newStrLen] = '\0';
	delete[] m_data;
	std::exchange(m_data, newStr);
	m_length = newStrLen;
}

int* makeNext(const char* str)
{
	int len = strlen(str);
	int* next = new int[len];
	next[0] = 0; //初始化next，next[0]不使用
	int i = 1; //str索引
	int j = 0; //最长公共前后缀

	while (i < len)
	{
		if (str[i] == str[j])
		{
			//如果相等，则最长公共前后缀+1
			j++;
			next[i] = j;
			i++;
		}
		else
		{
			if (j != 0)
			{
				j = next[j - 1];//通过上一个next求这个next
			}
			else
			{
				next[i] = 0;
				i++;
			}
		}
	}
	return next;
}

//使用pat去匹配txt
int KMP(const char* pat, const char* txt, int startIndex = 0)
{
	int M = strlen(pat);
	int N = strlen(txt);

	int i = startIndex, j = 0;
	int* next = makeNext(txt);

	while ((N - i) >= (M - j))
	{
		if (pat[j] == txt[i])
		{
			i++;
			j++;
		}

		if (j == M)
		{
			return i - j;
		}
		else if (i < N && pat[j] != txt[i])
		{
			if (j != 0)
			{
				j = next[j - 1];
			}
			else
			{
				i = i + 1;
			}

		}
	}
	return -1;
	delete[] next;
}



int CustomString::find(const char* str)
{
	return KMP(str, m_data);
}

CustomString* CustomString::split(const char* str)
{
	int str_length = strlen(str);

	if (str_length > m_length)
	{
		return nullptr;
	}

	int startIndex = 0;
	std::vector<CustomString> vec;

	for (int i=0; i< m_length;i++)
	{
		int index = KMP(str, m_data, startIndex);

		if (index == -1)
		{
			CustomString tempStr = sub(startIndex, m_length-1);
			vec.push_back(tempStr);
			break;
		}

		CustomString tempStr = sub(startIndex, index-1);
		vec.push_back(tempStr);
		startIndex = index + 1;
	}
	CustomString* result = new CustomString[vec.size()]();
	for (int i = 0; i < vec.size(); i++)
	{
		result[i] = vec[i];
	}

	return result;
}

