#include "TArray.h"
#include <malloc.h>
#include <math.h>

#define DEFAULTSIZE 1

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

TArray::~TArray()
{
	free(_array);
}
