#include "CustomString.h"
#include <string.h>
#include <iostream>

CustomString::CustomString(const char* str)
{
	std::cout <<"constructor" << std::endl;
	if (!str)
	{
		return;
	}
	m_length = strlen(str);
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

	std::cout << "copy constructor" << std::endl;
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

CustomString::~CustomString()
{
	if (!m_data)
	{
		return;
	}
	std::cout << "destructor" << std::endl;
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
	char* tempStr = new char[subLen];
	//memset(tempStr, '\0', subLen*sizeof(char));
	//memcpy(tempStr, m_data + sizeof(char) * start, subLen);
	//CustomString str(tempStr);

	delete[] tempStr;

	return str;
}
