#include <iostream>
#include <assert.h>

//Name: Parham Ebadi
//StudentId: 398833
//Grade: 100/100
//Comments: Great assignment! Nice comments and good organization with your code!.


int RecursiveMultiplication(int a, int b);
int NonRecursiveFibonacci(int n);
void PrintFibonacciLessThan15(int n);
void PrintRecursiveFactorialLessThan50(int n);
int DynamicProgrammingFunc(int n);
int DynamicFunction(int n);

int main(int argc, char* argv[])
{
	//Tests:	
	std::cout << RecursiveMultiplication(2, 5) << std::endl; // Expected result: 10

	std::cout << NonRecursiveFibonacci(5) << std::endl; //Expected result: 5

	PrintFibonacciLessThan15(7); //Expected result: 0 1 1 2 3 5 8 13

	std::cout << std::endl;

	PrintRecursiveFactorialLessThan50(10);//Expected result: 10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1

	std::cout << std::endl;
	
	//You can test the dynamic function here! The first one
	//is a recursive function, and the other one is the one
	//I wrote. You can compare them by passing in different
	//values to both functions here:
	std::cout << DynamicProgrammingFunc(4) << std::endl;
	std::cout << DynamicFunction(4) << std::endl;
	std::cout << DynamicProgrammingFunc(5) << std::endl;
	std::cout << DynamicFunction(5) << std::endl;
	std::cout << DynamicProgrammingFunc(6) << std::endl;
	std::cout << DynamicFunction(6) << std::endl;
	std::cout << DynamicProgrammingFunc(7) << std::endl;
	std::cout << DynamicFunction(7) << std::endl;

	std::cout << RecursiveMultiplication(-1, 10);

	return 0;
}

int RecursiveMultiplication(int a, int b)
{
	//TODO: Write a recursive function to multiply two positive integers
	//without using the operator *
	//You can use addition(+), subtraction(-) and bitShifting(<< or >>), but you
	//should minimize the number of those operations.

	assert(b > 0);

	if (b > 1)
	{
		return a + RecursiveMultiplication(a, b - 1);
	}
	else
	{
		return a;
	}
}

int NonRecursiveFibonacci(int n)
{
	//TODO: Convert the recursive fibonacci that we did in class
	//to a non recursive method, using a bottom-up approach.

	int iFibNumber = 0;
	int iPrePreviousNumber = 0;
	int iPreviousNumber = 1;

	for (int i = 0; i <= n; ++i)
	{
		if (i <= 1)
		{
			iFibNumber = n;
		}
		else
		{
			iFibNumber = iPrePreviousNumber + iPreviousNumber;
			iPrePreviousNumber = iPreviousNumber;
			iPreviousNumber = iFibNumber;
		}
	}

	return iFibNumber;
}

void PrintFibonacciLessThan15(int n)
{
	//TODO: Create a method that will print all the fibonacci sequence
	//less than 15. The way that you should print is:
	//PrintFibonacciLessThan15(7) -> "0 1 1 2 3 5 8 13". You just need to print what is between "".
	//Don't forget that is less than 15, so use assert if the method is being used outside the
	//boundaries of the function.

	//I wasn't sure which one it was you were looking for.
	assert(n < 8);
	//assert(n < 15);
	
	//I thought it would be a good practice to use and call a function I have already written,
	//instead of copying the code over and over again.
	for (int i = 0; i <= n; ++i)
	{
		std::cout << NonRecursiveFibonacci(i) << " ";
	}
}

void PrintRecursiveFactorialLessThan50(int n)
{
	//TODO: Create a method that will print recursive
	//the factorial multiplication format of a number that is less than 50.
	//ASSERT that this function will be used in a correct way.
	//As an example:
	//printRecursiveFactorialLessThan50(10) -> "10 * 9 * 8 * 7 * 6 * 5 * 4 * 3 * 2 * 1"
	//The function just prints what is between "".

	assert(n < 50);
	
	if (n >= 1)
	{
		if (n == 1)
		{
			std::cout << n;
		}

		else
		{
			std::cout << n << " * ";
		}

		PrintRecursiveFactorialLessThan50(n - 1);
	}
}

//TODO: Show with dynamic programming, the results and calls for DynamicProgrammingFunc(10)
//Identify repeated calls. This question you can do in a piece of paper drawing the calls
//and results and saving an image on your git repo.
int DynamicProgrammingFunc(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	return DynamicProgrammingFunc(n - 3) - (DynamicProgrammingFunc(n - 1) * DynamicProgrammingFunc(n - 2));
}

int DynamicFunction(int n)
{
	if (n < 5)
	{
		return n - 2;
	}

	int previousNminus1 = 2;
	int previousNminus2 = 1;
	int previousNminus3 = 0;

	int result3 = 0;
	int result2 = 0;
	int result1 = previousNminus3 - (previousNminus1 * previousNminus2);
	
	previousNminus1 = result1;
	++previousNminus3;
	++previousNminus2;

	for (int i = 0; i < n - 5; ++i)
	{
		result3 = result2;
		result2 = result1;
		result1 = previousNminus3 - (previousNminus1 * previousNminus2);

		previousNminus1 = result1;

		if (i >= 0)
		{
			previousNminus2 = result2;
		}
		else
		{
			++previousNminus2;
		}

		if (i >= 1)
		{
			previousNminus3 = result3;
		}
		else
		{
			++previousNminus3;
		}

	}

	return result1;

}