#include <cassert>
#include <iostream>

#ifndef TEST_CONTAINER
	#if TYPE == 1
		#include <queue>
		#include <vector>
		#include <deque>
		#define	TEST_CONTAINER	std::priority_queue
		#define	NAMESPACE		std
	#elif TYPE == 2
		#include "../src/containers/queue.hpp"
		#include "../src/containers/vector.hpp"
		#include "../src/containers/deque.hpp"
		#define	TEST_CONTAINER	ft::priority_queue
		#define	NAMESPACE		ft
	#endif
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef TEST_CONTAINER
int main()
{
	typedef		std::allocator<char>	Myal;
	typedef		NAMESPACE::less<char>	Mypred;
	typedef		NAMESPACE::deque<char, Myal>		Myimpl;
	typedef		TEST_CONTAINER<char, Myimpl>		Mycont;
	typedef		NAMESPACE::vector<char, Myal>		Myimpl2;
	typedef		TEST_CONTAINER<char, Myimpl2>		Mycont2;
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

	Mypred pr;
	char carr[] = "acb";
	Mycont	v0; v0.push('x'); v0.push('x'); v0.push('x'); 
	Mycont	v0a(pr);
	Mycont	v0b;
	Mycont2	vl;
	const Mycont v2(carr, carr + 3);
	const Mycont v2a(carr, carr + 3, pr);
	const Mycont v2b(carr, carr + 3, pr, Myimpl(3, 'x'));

	assert(v0.size() == 3 && v0.top() == 'x');
	assert(v0a.empty());
	v0 = v0a;

	assert(v2.size() == 3 && v2.top() == 'c');
	assert(v2a.size() == 3 && v2a.top() == 'c');
	assert(v2b.size() == 6 && v2b.top() == 'x');
	v0.push('a');
	assert(v0.size() == 1 && v0.top() == 'a');
	v0.push('c');
	assert(v0.size() == 2 && v0.top() == 'c');
	v0.push('b');
	assert(v0.size() == 3 && v0.top() == 'c');

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
