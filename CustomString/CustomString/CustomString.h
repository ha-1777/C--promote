#pragma once
class CustomString
{
public:
	CustomString() = default;
	CustomString(const char* str);							//普通构造
	CustomString(const CustomString& obj);					//拷贝构造
	CustomString(CustomString&& obj) noexcept;				//移动构造
	CustomString& operator=(const CustomString& obj);
	bool operator==(const CustomString& obj);
	~CustomString();
	int len();
	CustomString sub(int start, int end);
	void append(const char * str);
	int find(const char * str);
private:
	char* m_data;
	int m_length;
};

