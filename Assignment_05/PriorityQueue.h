#pragma once

//Assignment 5: Implement a templatized priority queue, using a Max Heap for operations 
//like Enqueue and Daqueue

template<typename T>
class PriorityQueue
{
public:

	struct Data
	{
		int priority;
		T data;
	};

	PriorityQueue(Data emptyValue) : mEmptyValue(emptyValue), mCapacity(10), mSize(0) 
	{
		//TODO_1: Implement the constructor of this priority queue
		//Look to do this, look at the member variables that you have.
		//You can default initiliaze your capacity with 10 elements.
		mDataArray = new Data[mCapacity];
	}

	~PriorityQueue() 
	{
		//TODO_2: Implement the destructor of this priority queue
		//Remember that whatever you "new" you have to "delete"
		delete[] mDataArray;
		mDataArray = nullptr;
	}

	void Enqueue(Data data) 
	{
		//TODO_3: Implement an Enqueue method for this priority queue.
		//This enqueue should follow the same insertion method that
		//a max heap has.
		//
		//Remember:
		//Heaps Insertion: Place the element at the end of the array,
		//In a loop, check yourself against you parent.priority. 
		//If yours is bigger, swap;
		mDataArray[mSize] = data;
		mSize++;

		for (int i = mSize - 1; i > 0; i = GetParent(i))
		{
			if (mDataArray[i].priority > mDataArray[GetParent(i)].priority)
			{
				swap(&mDataArray[i], &mDataArray[GetParent(i)]);
			}
		}
	}

	Data Dequeue() 
	{
		//TODO_4: Implement a Dequeue method for this priority queue.
		//This Dequeue should follow the same RemoveMax method that
		//a max heap has.
		//
		//Remember:
		//Heaps RemoveMax: Make the first element to receive the last
		//element from your array. After this, Heapfy.
		//If the queue is empty, return mEmptyValue
		
		if (mSize > 0)
		{
			Data temp = mDataArray[0];

			mDataArray[0] = mDataArray[mSize - 1];
			mSize--;

			Heapify(0);
			return temp;
		}
		else
		{
			return mEmptyValue;
		}
	}

	int GetSize() const 
	{
		return mSize;
	}

private:
	int GetParent(int index) const
	{
		return (index - 1) / 2;
	}

	int GetLeft(int index) const
	{
		return (index * 2) + 1;
	}

	int GetRight(int index) const 
	{
		return (index * 2) + 2;
	}

	void swap(Data* a, Data* b) 
	{
		Data temp = *a;
		*a = *b;
		*b = temp;
	}

	void Heapify(int index) 
	{
		//TODO_5: Implement Heapfy
		//
		//Remember:
		//Heapfy: In a loop, checks which one is bigger in priority between left and right. and select.
		//Then compares with it's priority. If parent priority is smaller, Swap.
		int savedIndex = 0;
		
		for (int i = index; i < mSize - 1; i = savedIndex)
		{
			int leftIndex = GetLeft(i);
			int rightIndex = GetRight(i);

			if (leftIndex > mSize && rightIndex > mSize)
			{
				break;
			}

			if (rightIndex > mSize || mDataArray[leftIndex].priority > mDataArray[rightIndex].priority)
			{
				savedIndex = leftIndex;

				if (mDataArray[leftIndex].priority > mDataArray[i].priority)
				{
					swap(&mDataArray[leftIndex], &mDataArray[i]);
				}
			}
			else
			{
				savedIndex = rightIndex;

				if (mDataArray[rightIndex].priority > mDataArray[i].priority)
				{
					swap(&mDataArray[rightIndex], &mDataArray[i]);
				}
			}			
		}
	}

	Data* mDataArray;
	int mCapacity;
	int mSize;
	Data mEmptyValue;
};
