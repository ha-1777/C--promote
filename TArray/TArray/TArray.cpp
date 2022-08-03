#include "TArray.h"
#include <malloc.h>
#include <math.h>

#define ERROR 0x7fffffff

TArray::TArray()
{
	_array = (int*)malloc(sizeof(int));
	_size = 0;
	_capacity = 1;
}

void TArray::reserve(int capacity)
{
	if (capacity <= _capacity)
	{
		return;
	}
	int newCapacity = pow(2, ceil(log(capacity) / log(2)));

	_array = (int*)realloc(_array, sizeof(int)*newCapacity);

	_capacity = newCapacity;
}

void TArray::push(int value)
{
	if (_size + 1 > _capacity)
	{
		reserve(_size + 1);
	}
	_array[_size] = value;
	_size++;
}

void TArray::insert(int index, int value)
{
	if (!value)
	{
		return;
	}

	if (index < 0 || index > _size)
	{
		return;
	}

	if (_size+1 > _capacity)
	{
		reserve(_size + 1);
	}

	for (int i = _size; i > index; i--)
	{
		_array[i] = _array[i - 1];
	}
	_array[index] = value;

	_size++;
}

void TArray::remove(int index)
{
	if (index<0 || index > _size-1)
	{
		return;
	}

	_array[_size] = NULL;
	for (int i=index; i<_size; i++)
	{
		_array[i] = _array[i + 1];
	}
	_size--;
}

int TArray::pop()
{
	if (!_size)
	{
		return ERROR;
	}

	int result = _array[_size - 1];
	_size--;
	
	return result;
}

void TArray::clear()
{
	_size = 0;
}

int TArray::findIndex(int value)
{
	if (!_size)
	{
		return -1;
	}

	for (int i=0; i<_size; i++)
	{
		if (value == _array[i])
		{
			return i;
		}
	}
	return -1;
}

TArray::~TArray()
{
	free(_array);
}
