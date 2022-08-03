#pragma once
class TArray
{
public:
	TArray();
	void reserve(int capacity);
	void push(int value);
	void insert(int index, int value);
	void remove(int index);
	int pop();
	void clear();
	int findIndex(int value);
	~TArray();
private:
	int* _array;
	int _size;
	int _capacity;
};

