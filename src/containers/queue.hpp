#pragma once

#include <memory>
#include "vector.hpp"
#include "list.hpp"
#include "deque.hpp"
#include "../utility/exception.hpp"
#include "../utility/xutility.hpp"
#include "../utility/algorithm.hpp"
#include "../utility/heap.hpp"

namespace ft
{

	template<class T, class C = ft::deque<T> >	// may be list/deque
	class queue
	{
	public:
		typedef				C					container_type;
		typedef typename	C::value_type		value_type;
		typedef typename	C::size_type		size_type;
 		typedef typename	C::reference		reference;
		typedef typename	C::const_reference	const_reference;

	protected:
		C	c;

	public:
		queue()
		: c()
		{}

		explicit queue(const C& Cont)
		: c(Cont)
		{}
		
		bool				empty() const { return (c.empty()); }
		size_type			size() const { return (c.size()); }
		reference			front() { return (c.front()); }
		const_reference		front() const { return (c.front()); }
		reference			back() { return (c.back()); }
		const_reference		back() const { return (c.back()); }
		void				push(const value_type& X) { c.push_back(X); }
		void				pop() { c.pop_front(); }

		bool				_eq(const queue X) const { return (c == X.c); }
		bool				_lt(const queue X) const { return (c < X.c); }
	};

template<class T, class C>
inline bool	operator==(const queue<T, C>& X, const queue<T, C>& Y) { return (X._eq(Y)); }

template<class T, class C>
inline bool	operator!=(const queue<T, C>& X, const queue<T, C>& Y) { return (! (X == Y)); }

template<class T, class C>
inline bool	operator<(const queue<T, C>& X, const queue<T, C>& Y) { return (X._lt(Y)); }

template<class T, class C>
inline bool	operator>(const queue<T, C>& X, const queue<T, C>& Y) { return (Y < X); }

template<class T, class C>
inline bool	operator<=(const queue<T, C>& X, const queue<T, C>& Y) { return (!(Y < X)); }

template<class T, class C>
inline bool operator>=(const queue<T, C>& X, const queue<T, C>& Y) { return (!(X < Y)); }


template<class T, class C = ft::vector<T>, class Pr = ft::less<typename C::value_type> >	// may be vector/deque
	class priority_queue
	{
	public:
		typedef				C					container_type;
		typedef typename	C::value_type		value_type;
		typedef typename	C::size_type		size_type;
		typedef				Pr					value_compare;
		typedef typename	C::const_reference	const_reference;

	protected:
		C	c;
		Pr	comp;

	public:
		priority_queue()
		: c()
		, comp()
		{}

		explicit priority_queue(const Pr& X)
		: c()
		, comp(X)
		{}

		priority_queue(const Pr& X, const C& Cont)
		: c(Cont)
		, comp(X)
		{
			ft::make_heap(c.begin(), c.end(), comp);
		}

		template<class It>
		priority_queue(It F, It L)
		: c(F, L)
		, comp()
		{
			ft::make_heap(c.begin(), c.end(), comp); }

		template<class It>
		priority_queue(It F, It L, const Pr& X)
		: c(F, L)
		, comp(X)
		{
			ft::make_heap(c.begin(), c.end(), comp);
		}
		
		template<class It>
		priority_queue(It F, It L, const Pr& X, const C& Cont)
		: c(Cont)
		, comp(X)
		{
			c.insert(c.end(), F, L);
			ft::make_heap(c.begin(), c.end(), comp);
		}
		
		bool				empty() const { return (c.empty()); }
		size_type			size() const { return (c.size()); }
		const_reference		top() const { return (c.front()); }

		void				push(const value_type& X)
		{	
			c.push_back(X);
			ft::push_heap(c.begin(), c.end(), comp);
		}

		void				pop()
		{
			ft::pop_heap(c. begin(), c.end(), comp);
			c.pop_back();
		}

	};

}
