#include "CustomString.h"
#include <string.h>
#include <iostream>

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

	delete[] m_data;
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

int CustomString::find(const char* str)
{
	return 0;
}
