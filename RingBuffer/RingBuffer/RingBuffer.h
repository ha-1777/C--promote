#pragma once
#include <memory>

class RingBuffer
{
public:
	RingBuffer(int _capacity);
	void push(const char* value);
	int pop(char* out, int len);
	~RingBuffer();
private:
	void reserve(int newCapacity);

private:
	int head;
	int rear;
	int size;
	char** data;
	int capacity;
};

