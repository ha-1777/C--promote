#pragma once
class TArray
{
public:
	TArray();
	void reserve(int capacity);
	void push(int value);
	~TArray();
private:
	int* _array;
	int _size;
	int _capacity;
};

