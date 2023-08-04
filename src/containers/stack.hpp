#pragma once

#include "vector.hpp"
#include "list.hpp"
#include "deque.hpp"

namespace ft
{

	template<class T, class C = ft::vector<T> >	// may be vector/list/deque
	class stack
	{
	public:
		typedef				C					container_type;
		typedef typename	C::value_type		value_type;
		typedef typename	C::size_type		size_type;
	 	typedef typename	C::reference		reference;
		typedef typename	C::const_reference	const_reference;

	protected:
		C	c;	// not as usual 'm_c' - error im tester 42
	
	public:
		explicit stack(const C& Cont)
		: c(Cont)
		{}
	
		stack()
		: c()
		{}
	
		bool				empty() const { return (c.empty()); }
		size_type			size() const { return (c.size()); }
		reference			top() { return (c.back()); }
		const_reference		top() const { return (c.back()); }
		void				push(const value_type& X) { c.push_back(X); }
		void				pop() { c.pop_back(); }

		bool				_eq(const stack& X) const { return (c == X.c); }
		bool				_lt(const stack& X) const { return (c < X.c); }
	};

	template<class T, class C>
	inline bool operator==(const stack<T, C>& X, const stack<T, C>& Y) { return (X._eq(Y)); }

	template<class T, class C>
	inline bool operator!=(const stack<T, C>& X, const stack<T, C>& Y) { return (!(X == Y)); }

	template<class T, class C>
	inline bool operator<(const stack<T, C>& X, const stack<T, C>& Y) { return (X._lt(Y)); }

	template<class T, class C>
	inline bool operator>(const stack<T, C>& X, const stack<T, C>& Y) { return (Y < X); }

	template<class T, class C>
	inline bool operator<=(const stack<T, C>& X, const stack<T, C>& Y) { return (!(Y < X)); }

	template<class T, class C>
	inline bool operator>=(const stack<T, C>& X, const stack<T, C>& Y) {return (!(X < Y)); }
}
