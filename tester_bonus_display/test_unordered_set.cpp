#include <iostream>
#include "../src/containers/unordered_set.hpp"
#include <cstdlib>
#include <ctime>

int main()
{
	int size = 20;
	int max_value = 100;
	srand(time(NULL));
	typedef typename ft::unordered_set<int> FT;
	FT test;
	for(int i = 0; i < size; ++i)
	{
		test.insert(rand() % max_value);
		test.display();
	}
	for(int i = test.size(); i > 0; --i)
	{
		test.erase(test.begin());
		test.display();
	}
	return 0;
}
