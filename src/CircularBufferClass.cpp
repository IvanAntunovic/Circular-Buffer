// CircularBufferClass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

#define BUFFER_SIZE 8
#define BUFFER_MASK (BUFFER_SIZE - 1)


class CircularQueue
{
	private:
		int first;
		int last;
		int validItems;
		int rx_buffer[BUFFER_SIZE];
		int tempRXBufferSize;

	public:
		CircularQueue()
		{
			validItems = 0;
			first = 0;
			last = 0;

			for (int i = 0; i < BUFFER_SIZE; i++)
			{
				rx_buffer[i] = NULL;
			}
		}

		int getFirst()
		{
			return first;
		}

		int getLast()
		{
			return last;
		}

		int getValidItems()
		{
			return validItems;
		}

		int* getRxBuffer()
		{
			return rx_buffer;
		}

		int isEmpty()
		{
			if (validItems == 0)
				return 1;
			else
				return 0;
		}

		int getFreeElemNum()
		{
			return (BUFFER_SIZE - ((BUFFER_SIZE - first + last) & BUFFER_MASK));
		}

		bool availabile()
		{
			if (getFreeElemNum())
			{
				return true;
			}
			return false;
		}

		int getOccupiedElemNum()
		{
			return ((BUFFER_SIZE - first + last) & BUFFER_MASK);
		}


		int enqueue(int itemValue)
		{
			if (validItems >= BUFFER_SIZE)
			{
				std::cout << "The queue is full\n";
				std::cout << "You cannot add items\n";
				return -1;
			}

			else
			{
				validItems++;
				rx_buffer[last] = itemValue;
				last = (last + 1) & BUFFER_MASK;
				return 0;
			}
		}

		int dequeue(int* itemValue)
		{
			if (isEmpty())
			{
				printf("is empty\n");
				return 1;
			}
			else
			{
				*itemValue = rx_buffer[first];
				first = (first + 1) & BUFFER_MASK;
				validItems--;
				return 0;
			}
		}
		
		int* receive()
		{
			int* tempElement = (int*)malloc(sizeof(int));
			const int TEMP_BUFFER_SIZE = tempRXBufferSize = validItems;
			//*sizeOfRXBuffer = TEMP_BUFFER_SIZE;
			int* tempBuffer = (int*)malloc(TEMP_BUFFER_SIZE * sizeof(int));

			int i = 0;
			do {
				if (dequeue(tempElement))
					break;
				tempBuffer[i++] = *tempElement;
			} while (true);

			delete(tempElement);

			return tempBuffer;
		}

		void print(int* buffer)
		{
			for (int i = 0; i < tempRXBufferSize; ++i)
				printf("Buffer[%d]: %d\n", i, *buffer++);
		}
		
		void printElements()
		{
			int aux = first, auxOne = validItems;

			while (auxOne > 0)
			{
				printf("Element #%d = %d\n", aux, rx_buffer[aux]);
				aux = (aux + 1) & BUFFER_MASK;
				auxOne--;
			}
			return;
		}

};


int main()
{
	CircularQueue circularQueue;
	int* buffer = (int*)malloc(sizeof(int));
	int* sizeOfRXBuffer = (int*)malloc(sizeof(int));
	//int buffer[BUFFER_SIZE];

	if (circularQueue.isEmpty())
		std::cout << "Queue is empty" << endl;

	circularQueue.enqueue(1);
	circularQueue.enqueue(2);
	circularQueue.enqueue(3);
	circularQueue.enqueue(4);
	circularQueue.enqueue(5);
	circularQueue.enqueue(6);
	circularQueue.enqueue(7);
	circularQueue.enqueue(8);
	circularQueue.enqueue(9);

	circularQueue.printElements();

	if (circularQueue.isEmpty() == -1)
		std::cout << "Queue is empty" << endl;

	circularQueue.dequeue(buffer);
	circularQueue.dequeue(buffer);
	
	std::cout << "After dequeue" << endl;
	circularQueue.printElements();

	//buffer = receive(circularQueue, sizeOfRXBuffer);
	buffer = circularQueue.receive();

	std::cout << "After calling print function" << endl;
	//print(buffer, sizeOfRXBuffer);
	circularQueue.print(buffer);

	circularQueue.enqueue(12);

	delete(sizeOfRXBuffer);

	return 0;
}