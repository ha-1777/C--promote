#pragma once

#define ERROR 0x7fffffff

template<typename T>
class TArray
{
public:
	TArray()
	{
		_array = (T*)malloc(sizeof(T));
		_size = 0;
		_capacity = 1;
	}

	void reserve(int capacity)
	{
		if (capacity <= _capacity)
		{
			return;
		}
		int newCapacity = pow(2, ceil(log(capacity) / log(2)));

		_array = (T*)realloc(_array, sizeof(T) * newCapacity);

		_capacity = newCapacity;
	}


	void push(T value)
	{
		if (_size + 1 > _capacity)
		{
			reserve(_size + 1);
		}
		_array[_size] = value;
		_size++;
	}

	void insert(int index, T value)
	{
		if (!value)
		{
			return;
		}

		if (index < 0 || index > _size)
		{
			return;
		}

		if (_size + 1 > _capacity)
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

	void remove(int index)
	{
		if (index<0 || index > _size - 1)
		{
			return;
		}

		_array[_size] = NULL;
		for (int i = index; i < _size; i++)
		{
			_array[i] = _array[i + 1];
		}
		_size--;
	}

	int pop()
	{
		if (!_size)
		{
			return ERROR;
		}

		int result = _array[_size - 1];
		_size--;

		return result;
	}

	void clear()
	{
		_size = 0;
	}

	int findIndex(int value)
	{
		if (!_size)
		{
			return -1;
		}

		for (int i = 0; i < _size; i++)
		{
			if (value == _array[i])
			{
				return i;
			}
		}
		return -1;
	}

	~TArray()
	{
		free(_array);
	}

private:
	int* _array;
	int _size;
	int _capacity;
};

