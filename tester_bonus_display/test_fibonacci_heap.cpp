#include <iostream>
#include "../src/containers/fibonacci_heap.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	int size = 10;
	int max_value = 100;
	typedef typename ft::fibonacci_heap<int> FT;
	FT test;
	FT test_tmp;
	for(int i = 1; i < size; ++i)
	{
		test.insert(rand() % max_value);
		test_tmp.insert(rand() % max_value);
	}
	ft::fibonacci_heap<int>::Node_ptr n = test.insert(rand() % max_value);
	test.display();
	test_tmp.display();

	test.merge(test_tmp);
	test.display();
	test_tmp.display();

	ft::fibonacci_heap<int>::Node_ptr	n_test = test.insert(max_value + 1);
	ft::fibonacci_heap<int>::Node_ptr	test_find = test.find(max_value + 1);
	if (test_find != n_test)
	{
		std::cout << "find FALSE" << std::endl;
		return 1;
	}

	std::cout << "Heap Minimum Extracted: " << test.remove_min() << std::endl;
	test.display();

	test.decreaseKey(n, 1);
	test.display();

	std::cout << "Heap Minimum Extracted: " << test.remove_min() << std::endl;
	test.display();
	for (int i = test.size(); i > 0; i--)
	{
		test.remove_min();
		test.display();
	}

	return 0;
}
