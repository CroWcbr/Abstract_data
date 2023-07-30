#pragma once

//delete this!!!!!! for heap
#include <algorithm>
#include <queue>

namespace ft
{

	template<class It, class Comp>
	void make_heap(It F, It L, Comp C)
	{
		std::make_heap(F, L, C);
	}
	template<class It, class Comp>
	void push_heap(It F, It L, Comp C)
	{
		std::push_heap(F, L, C);
	}
	template<class It, class Comp>
	void pop_heap(It F, It L, Comp C)
	{
		std::pop_heap(F, L, C);
	}

}
