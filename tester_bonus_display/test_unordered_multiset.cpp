#include <iostream>
#include "../src/containers/unordered_set.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	int size = 20;
	int max_value = 50;
	srand(time(NULL));
	typedef typename ft::unordered_multiset<int> FT;
	FT test;
	for(int i = 0; i < size; ++i)
	{
		test.insert(rand() % max_value);
	}
	test.display();

	int t = 10;
	std::cout << "TEST insert/delete\t" << t << std::endl; 
	test.insert(t);
	test.display();
	test.erase(t);
	test.display();

	std::cout << "TEST delete end" << std::endl; 
	for(int i = test.size(); i > 8; --i)
	{
		test.erase(--test.end());
	}
	test.display();
	std::cout << "TEST begin end" << std::endl; 
	for(int i = test.size(); i > 2; --i)
	{
		test.erase(test.begin());
	}
	test.display();
	return 0;
}
