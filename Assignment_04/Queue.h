#pragma once

//TODO: 5 - Implement a Queue class from scratch
//Remember that your queue should follow the FIFO standard (First In First Out)

template<typename T>
class Queue 
{
public:
	Queue() {}
	Queue(int capacity) : mCapacity(capacity)
	{
		mData = new T[capacity];
	}
	~Queue()
	{
		delete[] mData;
		mData = nullptr;
	}
	//Inserts the data in the queue.
	void Enqueue(T data)
	{
		if (mCurrentSize != mCapacity)
		{
			mData[rear] = data;

			rear++;
			rear %= mCapacity;
			mCurrentSize++;
		}
	}
	
	//Removes an element from the queue and returns this element in the output parameter
	//Also it returns true if the object was removed and false if the Queue is empty
	bool Daqueue(T& output)
	{
		if (mCurrentSize > 0)
		{
			output = mData[front];
			front++;
			front %= mCapacity;
			mCurrentSize--;
			return true;
		}
		else
		{
			return false;
		}
	}
	
	//Returns true if queue is empty, false otherwise
	bool isEmpty()
	{
		return mCurrentSize == 0;
	}

	//Display all the elements in the queue:
	//Example, lets suppose you inserted 1, 2, 3, 4, 5
	//Display should print: "front->1, 2, 3, 4, 5<-rear"
	void DisplayQueue()
	{

	}

private:
	int front = 0;
	int rear = 0;
	int mCurrentSize = 0;
	int mCapacity = 10;
	T* mData = nullptr;
};