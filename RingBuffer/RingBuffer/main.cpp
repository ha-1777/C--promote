#include <iostream>
#include "RingBuffer.h"


int main()
{

	int initSize = 4;
	const char* data = "123456789";
	auto buffer = new RingBuffer(initSize);
	char out[128];

	for (int i = 0; i < initSize + 1; i++)
	{
		buffer->push(data);
	}

	for (int j = 0; j < initSize + 1; j++)
	{
		int len = buffer->pop(&out[0], sizeof(out));
		std::cout << j << "   ";
		for (int i = 0; i < len; i++)
		{
			std::cout << out[i];
		}
		std::cout << "\n"; 
	}

	delete buffer;

	return 0;
}
