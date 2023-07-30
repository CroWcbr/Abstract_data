#include <cassert>
#include <iostream>

#ifndef TEST_CONTAINER
	#if TYPE == 1
		#include <set>
		#define	TEST_CONTAINER	std::unorder_set
		#define	NAMESPACE		std
	#elif TYPE == 2
		#include "../src/containers/unorder_set.hpp"
		#define	TEST_CONTAINER	ft::unorder_set
		#define	NAMESPACE		ft
	#endif
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#ifdef TEST_CONTAINER
int main()
{
	typedef	std::allocator<char>	Myal;
	typedef	NAMESPACE::less<char>	Mypred;
	typedef	TEST_CONTAINER<char>	Mycont; 

	char	ch;
	Mycont::key_type			*p_key = (char *)0;
	Mycont::key_compare			*p_kcomp = (Mypred *)0;
	Mycont::value_type			*p_val = (char *)0;
	Mycont::value_compare		*p_vcomp = (Mypred *)0;
	Mycont::allocator_type		*p_alloc = (Myal *)0;
	Mycont::pointer				p_ptr = (char *)0;
	Mycont::const_pointer		p_cptr = (const char *)0;
	Mycont::reference			p_ref = ch;
	Mycont::const_reference		p_cref = (const char&)ch;
	Mycont::size_type*			p_size = (size_t *)0;
	Mycont::difference_type*	p_diff = (ptrdiff_t *)0;

	char carr[] = "abc";
	char carr2 [] = "def";


	Mycont	v0;
	Myal al = v0.get_allocator();
	Mypred  pred;
	Mycont	v0a(pred);
	Mycont v0b(pred, al);
	assert (v0.empty () && v0.size() == 0);
	assert(v0a.size() == 0 && v0a.get_allocator () == al);
	assert(v0b.size() == 0 && v0b.get_allocator() == al);
	Mycont vl(carr, carr + 3);
	assert(vl.size() == 3 && *vl.begin() == 'a');
	Mycont v2(carr, carr + 3, pred);
	assert(v2.size() == 3 && *v2.begin() == 'a');
	Mycont v3(carr, carr + 3, pred, al);
	assert(v3.size() == 3 && *v3.begin() == 'a');
	const Mycont v4(carr, carr + 3);
	v0 = v4;
	assert(v0.size() == 3 && *v0.begin() == 'a');

	Mycont::iterator p_it(vl.begin());
	Mycont::const_iterator p_cit (v4.begin());
	Mycont::reverse_iterator p_rit (vl.rbegin());
	Mycont::const_reverse_iterator p_crit(v4.rbegin());
	assert(*p_it == 'a' && *--(p_it = vl.end()) == 'c');
	assert(*p_cit == 'a' && *--(p_cit = v4.end()) == 'c');
	assert (*p_rit == 'c' && *--(p_rit = vl.rend()) == 'a');
	assert(*p_crit == 'c' && *--(p_crit = v4.rend()) == 'a');

	v0.clear();
	NAMESPACE::pair<Mycont::iterator, bool> pib = v0.insert('d');
	assert(*pib.first == 'd' && pib.second);
	assert (*--v0.end() == 'd');
	pib = v0.insert('d');
	assert(*pib.first == 'd' && !pib.second);
	assert(*v0.insert(v0.begin(), 'e') == 'e');
	v0.insert(carr, carr + 3);
	assert(v0.size() == 5 && *v0.begin() == 'a');
	v0.insert(carr2, carr2 + 3);
	assert(v0.size() == 6 && *--v0.end() == 'f');
	// assert(*v0.erase(v0.begin()) == 'b' && v0.size() == 5);	// ISO+IEC+14882-1998 - erase is void, but in stl return iterator
	v0.erase(v0.begin());										// the same previos
	assert(*v0.begin() == 'b' && v0.size() == 5);				// the same previos
	// assert(*v0.erase(v0.begin(), ++v0.begin()) == 'c' && v0.size() == 4) ;	// ISO+IEC+14882-1998 - erase is void, but in stl return iterator
	v0.erase(v0.begin(), ++v0.begin());											// the same previos
	assert(*v0.begin() == 'c' && v0.size() == 4);								// the same previos
	assert(v0.erase('x') == 0 && v0.erase('e') == 1);

	v0.clear();
	assert(v0.empty());
	v0.swap(vl);
	assert (!v0.empty() && vl.empty());
	NAMESPACE::swap(v0, vl);
	assert(v0.empty() && !vl.empty());
	assert(vl == vl && v0 < vl);
	assert(v0 != vl && vl > v0);
	assert(v0 <= vl && vl >= v0);

	assert(v0.key_comp()('a', 'c') && !v0.key_comp()('a', 'a'));
	assert(v0.value_comp()('a', 'c') && !v0.value_comp()('a', 'a'));
	assert(*v4.find('b') == 'b');
	assert(v4.count('x') == 0 && v4.count('b') == 1);
	assert(*v4.lower_bound('a') == 'a');
	assert(*v4.upper_bound('a') == 'b');
	NAMESPACE::pair<Mycont::const_iterator, Mycont::const_iterator> pcc = v4.equal_range('a');
	assert(*pcc.first == 'a' && *pcc.second == 'b');

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
