#include "DS_binary_Tree.h"
#include "DS_doubly_linked_list.h"
#include "DS_singly_linked_list.h"
#include "DS_stack.h"
#include "DS_array.h"
#include <cstdlib> // Для использования функций rand() и srand()
#include <ctime>   // Для использования функции time()
#include <iostream>


int main()
{
	std::srand(static_cast<unsigned int>(std::time(nullptr)));

	DArray<int> arr(2, 2, 2);

	arr.random();

	arr.print3D();

	int a = arr.indexOf(7);

	std::cout << "[Index 16] = " << a << std::endl;

	int b = arr.Size();

	std::cout << "[Size] = " << b << std::endl;

	int c = arr.findMin();

	std::cout << "[Min] = " << c << std::endl;

	int d = arr.findMax();

	std::cout << "[Max] = " << d << std::endl;

	int e = arr.findAvegage();

	std::cout << "[Avegage] = " << e << std::endl;

	int f = arr.findMedian();

	std::cout << "[Median] = " << f << std::endl;

	arr.insertItem(14, 4);

	arr.print();

	arr.print2D();

	return 0;
 }