#include <cassert>
#include <iostream>

#ifndef TEST_CONTAINER
	#if TYPE == 1
		#include <unordered_set>
		#define	TEST_CONTAINER	std::unordered_set
		#define	NAMESPACE		std
	#elif TYPE == 2
		#include "../src/containers/unordered_set.hpp"
		#define	TEST_CONTAINER	ft::unordered_set
		#define	NAMESPACE		ft
	#endif
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef TEST_CONTAINER
int main()
{
	typedef	std::allocator<char>	Myal;
	typedef	NAMESPACE::less<char>			Mypred;
#if TYPE == 1
	typedef	NAMESPACE::hash<char>			Myhash;
#elif TYPE == 2
	typedef	NAMESPACE::hash_compare<char>	Myhash;
#endif
	typedef	TEST_CONTAINER<char>	Mycont; 

	char	ch;
	Mycont::key_type			*p_key = (char *)0;
	// Mycont::key_compare			*p_kcomp = (Mypred *)0;
	Mycont::value_type			*p_val = (char *)0;
	// Mycont::value_compare		*p_vcomp = (Mypred *)0;
	Mycont::allocator_type		*p_alloc = (Myal *)0;
	Mycont::pointer				p_ptr = (char *)0;
	Mycont::const_pointer		p_cptr = (const char *)0;
	Mycont::reference			p_ref = ch;
	Mycont::const_reference		p_cref = (const char&)ch;
	Mycont::size_type*			p_size = (size_t *)0;
	Mycont::difference_type*	p_diff = (NAMESPACE::ptrdiff_t *)0;

	char carr[] = "abc";
	char carr2 [] = "def";

	Mycont	v0;
	Myal al = v0.get_allocator();
	Mypred pred;
	Myhash hash;
	Mycont v0a;
	Mycont v0b;
	assert(v0.empty () && v0.size() == 0);
	assert(v0a.size() == 0 && v0a.get_allocator () == al);
	assert(v0b.size() == 0 && v0b.get_allocator() == al);
	Mycont v1(carr, carr + 3);
	assert(v1.size() == 3);
	Mycont v2(carr, carr + 3);
	assert(v2.size() == 3);
	const Mycont v4(carr, carr + 3);
	v0 = v4;
	assert(v0.size() == 3);

	Mycont::iterator p_it(v1.begin());
	Mycont::const_iterator p_cit (v4.begin());

	v0.clear();
	assert(v0.empty () && v0.size() == 0);
	Mycont::iterator it_f = v1.find('q');
	assert(it_f == v1.end());
	it_f = v1.find('a');
	assert(*it_f == 'a');

	v1.erase(*it_f);
	assert(v1.size() == 2);
	v1.insert('q');
	assert(v1.size() == 3);

	v0.clear();
	assert(v0.empty());
	v0.swap(v1);
	assert (!v0.empty() && v1.empty());
	NAMESPACE::swap(v0, v1);
	assert(v0.empty() && !v1.empty());

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
