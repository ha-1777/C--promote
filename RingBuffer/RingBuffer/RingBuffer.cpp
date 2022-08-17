#include "RingBuffer.h"
#include <String>
#include <iostream>

RingBuffer::RingBuffer(int _capacity) :
	head(0),
	rear(0),
	size(0),
	capacity(_capacity)
{
	data = new char* [capacity + 1];
}

void RingBuffer::push(const char* value)
{
	int valueSize = strlen(value);
	if (size == capacity)
	{
		reserve(capacity * 2);
	}
	data[rear] = new char[valueSize + 1];
	data[rear][valueSize] = '\0';
	memcpy(data[rear], value, valueSize);
	rear = (rear + 1) % (capacity + 1);
	size++;
}

int RingBuffer::pop(char* out, int len)
{
	int outLen = strlen(data[head]);
	if (!size)
	{
		return -1;
	}
	else if (len < outLen)
	{
		return -1;
	}
	memcpy(out, data[head], outLen);
	delete[] data[head];
	head = (head + 1) % (capacity + 1);
	size--;

	if (size <= capacity / 2)
	{
		reserve(capacity / 2);
	}

	return outLen;
}

RingBuffer::~RingBuffer()
{
	delete[] data;
}

void RingBuffer::reserve(int newCapacity)
{
	if (newCapacity <= 2)
	{
		return;
	}

	char** newData = new char* [newCapacity + 1];
	for (int i = 0; i < size; i++)
	{
		newData[i] = data[head];
		head = (head + 1) % (capacity + 1);
	}
	head = 0;
	rear = size;
	capacity = newCapacity;
	delete[] data;
	data = newData;
}