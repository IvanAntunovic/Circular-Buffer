// CircularBufferV2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
using namespace std;

#define BUFFER_SIZE 8 
#define BUFFER_MASK (BUFFER_SIZE - 1)

class CircularBuffer
{
	public:
		int head;
		int tail;
		int buffer[BUFFER_SIZE];
		int availableItems;
		int dequeuedElement;
	
		CircularBuffer()
		{
			head = 0;
			tail = 0;
			dequeuedElement = 0;
			availableItems = 0;
			for (int i = 0; i < BUFFER_SIZE; ++i)
			{
				buffer[i] = 0;
			}
		}

		bool isAvailable()
		{
			
			if (availableItems)
			{
				return true;
			}
			return false;
		}
};


bool isEmpty(CircularBuffer& queue)
{
	if (queue.availableItems)
	{
		return false;
	}
	return true;
}

bool isFull(CircularBuffer& queue)
{

	if (queue.availableItems >= BUFFER_SIZE)
	{
		return true;
	}
	return false;
}

bool enqueue(CircularBuffer& queue, int element)
{
	if (isFull(queue))
	{
		return false;
	}
	queue.buffer[queue.tail] = element;
	queue.tail = (queue.tail + 1) & BUFFER_MASK;
	queue.availableItems++;
	return true;
}

bool dequeue(CircularBuffer& queue)
{
	if (isEmpty(queue))
	{
		return false;
	}
	queue.dequeuedElement = queue.buffer[queue.head];
	queue.head = (queue.head + 1) & BUFFER_MASK;
	queue.availableItems--;
	return true;
}

int main()
{
	CircularBuffer queue;
	int buffer[BUFFER_SIZE] = { 0 }, i = 0;

	enqueue(queue, 1);
	enqueue(queue, 2);
	enqueue(queue, 3);
	enqueue(queue, 4);
	enqueue(queue, 5);
	enqueue(queue, 6);
	enqueue(queue, 7);
	enqueue(queue, 8);
	enqueue(queue, 9);
	
	if (queue.isAvailable())
	{
		std::cout << "There are elements available in the buffer" << std::endl;
	}

	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;
	dequeue(queue);
	buffer[i++] = queue.dequeuedElement;

    return 0;
}

