#include <cassert>
#include <iostream>

#ifndef TEST_CONTAINER
	#if TYPE == 1
		#include <stack>
		#define	TEST_CONTAINER	std::stack
	#elif TYPE == 2
		#include "../src/containers/stack.hpp"
		#include "../src/containers/vector.hpp"
		#include "../src/containers/list.hpp"
		#include "../src/containers/deque.hpp"
		#define	TEST_CONTAINER	ft::stack
	#endif
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef TEST_CONTAINER
int main()
{
	typedef		std::allocator<char>	Myal;
	typedef		ft::deque<char, Myal>		Myimpl;
	typedef		ft::stack<char, Myimpl>		Mycont;
	typedef		ft::list<char, Myal>		Myimpl2;
	typedef		ft::stack<char, Myimpl2>	Mycont2;
	typedef		ft::vector<char, Myal>		Myimpl3;
	typedef		ft::stack<char, Myimpl3>	Mycont3;
	{
		Mycont::container_type	*p_cont = (Myimpl *)0;
		Mycont::value_type		*p_val = (char *)0;
		Mycont::size_type		*p_size = (size_t *)0;
	}
	{
		Mycont2::container_type	*p_cont = (Myimpl2 *)0;
		Mycont2::value_type		*p_val = (char *)0;
		Mycont2::size_type		*p_size = (size_t *)0;
	}
	{
		Mycont3::container_type	*p_cont = (Myimpl3 *)0;
		Mycont3::value_type		*p_val = (char *)0;
		Mycont3::size_type		*p_size = (size_t *)0;
	}

	Mycont	v0(Myimpl(3, 'x'));
	Mycont	v0a;
	Mycont2	vl;
	Mycont3	v2;

	assert(v0.size() == 3 && v0.top() == 'x');
	assert(v0a.empty());

	v0 = v0a;
	v0.push('a');

	assert(v0.size() == 1 && v0.top() == 'a');
	v0.push('b');
	assert(v0.size() == 2 && v0.top() == 'b');
	v0.push('c');
	assert(v0.size() == 3 && v0.top() == 'c');
	assert(v0 == v0 && v0a < v0);
	assert(v0 != v0a && v0 > v0a);
	assert(v0a <= v0 && v0 >= v0a);
	v0.pop();
	assert(v0.top() == 'b');
	v0.pop();
	assert(v0.top() == 'a');
	v0.pop();
	assert(v0.empty());

	std::cout << "SUCCESS testing " << TOSTRING(TEST_CONTAINER) << std::endl;
	return (0);
}
#else
int main()
{
	std::cout << "USAGE: g++ test -D TYPE=1/2" << std::endl;
	std::cout << "1 - std" << std::endl;
	std::cout << "2 - ft" << std::endl;
	return 1;
}
#endif
