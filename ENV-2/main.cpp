#include <iostream>
#include "complex.h"
#include "sort.h"
int main()
{
	const int size = 6;
	Complex array[size] = 
{
	Complex(3,5),
	Complex(1,4),
	Complex(2,8),
	Complex(3,6),
	Complex(1,9),
	Complex(4,5)
};
	for(int i = 0; i < size; ++i)
	{
	array[i].print();
	}
	bubbleSort(array, size);

	for(int i = 0; i < size; ++i)
	{
	array[i].print();
	}
return 0;
}
