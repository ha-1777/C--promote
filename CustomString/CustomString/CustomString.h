#pragma once
class CustomString
{
public:
	CustomString() = default;
	CustomString(const char* str);							//��ͨ����
	CustomString(const CustomString& obj);					//��������
	CustomString(CustomString&& obj) noexcept;				//�ƶ�����
	CustomString& operator=(const CustomString& obj);
	char& operator[](int index) { return m_data[index]; };
	~CustomString();

public:
	int len();
	CustomString sub(int start, int end);
	void append(const char * str);
private:
	char* m_data;
	int m_length;
};

