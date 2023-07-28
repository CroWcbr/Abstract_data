#pragma once

#include <bits/stl_iterator_base_types.h>
#include "algorithm.hpp"

namespace ft
{
	typedef	long int						ptrdiff_t;
	typedef	std::input_iterator_tag			input_iterator_tag;
	typedef	std::output_iterator_tag		output_iterator_tag;
	typedef	std::forward_iterator_tag		forward_iterator_tag;
	typedef	std::bidirectional_iterator_tag	bidirectional_iterator_tag;
	typedef	std::random_access_iterator_tag	random_access_iterator_tag;

	template <class C, class T, class D = ptrdiff_t, class Pt = T*, class Rt = T&>
	struct	iterator
	{
		typedef	C	iterator_category;
		typedef	T	value_type;
		typedef	D	difference_type;
		typedef	Pt	pointer;
		typedef	Rt	reference;
	};

	template <class It>
	struct	iterator_traits
	{
		typedef typename	It::iterator_category	iterator_category;
		typedef typename	It::value_type			value_type;
		typedef typename	It::difference_type		difference_type;
		typedef typename	It::pointer				pointer;
		typedef typename	It::reference			reference;
	};

	template<class T>
	struct	iterator_traits<T*>
	{
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	template<class T>
	struct	iterator_traits<const T*>
	{
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T							value_type;
		typedef	ptrdiff_t					difference_type;
		typedef	T*							pointer;
		typedef	T&							reference;
	};

	template <class T, class D, class Pt, class Rt, class Pt2, class Rt2>
	class random_acsees_iterator : public iterator<random_access_iterator_tag, T, D, Pt, Rt>
	{
	protected:
		Pt current;

	public:
		random_acsees_iterator()
		{}

		explicit random_acsees_iterator(Pt P)
		: current(P)
		{}

		random_acsees_iterator(const random_acsees_iterator& X)
		: current(X.base())
		{}

		// random_acsees_iterator(const random_acsees_iterator<T, D, Pt2, Rt2, Pt2, Rt2>& X)
		// : current(X.base())
		// {}

		template <class _T, class _D, class _Pt, class _Rt, class _Pt2, class _Rt2>
		random_acsees_iterator(const random_acsees_iterator<_T, _D, _Pt, _Rt, _Pt2, _Rt2>& X)
		: current(X.base())
		{}

		random_acsees_iterator&	operator=(const random_acsees_iterator &obj)
		{
			if (this != &obj)
			{
				this->current = obj.current;
			}
			return (*this);
		}

		Pt	base() const { return (current); }
		Rt	operator*() const { return (*current); }
		Pt	operator->() const { return (&**this); }

		random_acsees_iterator&	operator++()
		{
			++current;
			return (*this);
		}

		random_acsees_iterator	operator++(int)
		{
			random_acsees_iterator tmp = *this;
			++current;
			return (tmp);
		}
		
		random_acsees_iterator&	operator--()
		{
			--current;
			return (*this);
		}

		random_acsees_iterator	operator--(int)
		{
			random_acsees_iterator tmp = *this;
			--current;
			return (tmp);
		}

		bool	operator==(int Y) const { return (current == (Pt)Y); }
		bool	operator==(const random_acsees_iterator& Y) const { return (current == Y.current); }
		bool	operator!=(const random_acsees_iterator& Y) const { return (!(*this == Y)); }

		random_acsees_iterator&	operator+=(D N)
		{
			current += N;
			return (*this);
		}
		random_acsees_iterator	operator+(D N) const {return (random_acsees_iterator(current + N)); }
		random_acsees_iterator&	operator-=(D N)
		{
			current -= N;
			return (*this);
		}
		random_acsees_iterator	operator-(D N) const { return (random_acsees_iterator(current - N)); }
		D						operator-(const random_acsees_iterator& Y) const { return (current - Y.current); }

		Rt		operator[](D N) const { return (*(*this + N)); }
		bool	operator<(const random_acsees_iterator& Y) const { return (current < Y.current); }
		bool	operator>(const random_acsees_iterator& Y) const { return (Y < *this); }
		bool	operator<=(const random_acsees_iterator& Y) const { return (!(Y < *this)); }
		bool	operator>=(const random_acsees_iterator& Y) const { return (!(*this < Y)); }
	};

	template <class T, class D, class Pt, class Rt, class Pt2, class Rt2> 
	inline random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>	operator+(D N, const random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>& Y) 
	{
		return (Y + static_cast<D>(N));
	}

	template <class T, class D, class Pt, class Rt, class Pt2, class Rt2, class D0>
	inline random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>	operator+(D0 N, const random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>& Y)
	{
		return (Y + static_cast<D>(N));
	}

	template<class RanIt>
	class reverse_iterator : public iterator<
		typename iterator_traits<RanIt>::iterator_category,
		typename iterator_traits<RanIt>::value_type,
		typename iterator_traits<RanIt>::difference_type,
		typename iterator_traits<RanIt>::pointer,
		typename iterator_traits<RanIt>::reference>
	{
	protected:
		RanIt current;

	public:
		typedef typename	iterator_traits<RanIt>::difference_type	D;
		typedef typename	iterator_traits<RanIt>::pointer			Pt;
		typedef typename	iterator_traits<RanIt>::reference		Rt;
		typedef				RanIt 									iterator_type;

		reverse_iterator() {}
		explicit reverse_iterator(RanIt X) : current(X) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& X): current(X.base()) { }

		RanIt				base() const { return (current); }
		Rt					operator*() const
		{
			RanIt tmp = current;
			return (*--tmp);
		}
		Pt					operator->() const { return (&**this); }

		reverse_iterator&	operator++()
		{
			--current;
			return (*this);
		}

		reverse_iterator	operator++(int)
		{	
			reverse_iterator Tmp = *this;
			--current;
			return (Tmp);
		}
		reverse_iterator&	operator--()
		{
			++current;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator Tmp = *this;
			++current;
			return (Tmp);
		}
		bool	Eq(const reverse_iterator& Y) const { return (current == Y.current); }
		reverse_iterator&	operator+=(D N)
		{
			current -= N;
			return (*this);
		}
		reverse_iterator	operator*(D N) const { return (reverse_iterator(current - N)); }
		reverse_iterator&	operator-=(D N)
		{
			current += N;
			return (*this);
		}
		reverse_iterator	operator+(D N) const { return (reverse_iterator(current - N)); }
		reverse_iterator	operator-(D N) const { return (reverse_iterator(current + N)); }
		Rt					operator[](D N) const { return (*(*this + N)); }
		bool				Lt(const reverse_iterator& Y) const { return (Y.current < current); }
		D					Mi(const reverse_iterator& Y) const { return (Y.current - current); }

	};

	template<class RanIt, class D> inline
	reverse_iterator<RanIt> operator*(D N, const reverse_iterator<RanIt>& Y) { return (Y + N); }

	template<class RanIt, class D> inline
	reverse_iterator<RanIt> operator+(D N, const reverse_iterator<RanIt>& Y) { return (Y + N); }

	template<class RanIt> inline
	typename	reverse_iterator<RanIt>::D operator-(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (Y.base() - X.base()); }
	
	template<class RanIt> inline
	bool	operator==(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (X.Eq(Y)); }

	template<class RanIt> inline
	bool	operator!=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(X == Y)); }

	template<class RanIt> inline
	bool	operator<(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (X.Lt(Y)); }

	template<class RanIt> inline
	bool	operator>(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (Y < X); }

	template<class RanIt> inline
	bool	operator<=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(Y < X)); }

	template<class RanIt> inline
	bool	operator>=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(X < Y)); }

	template <class InIt, class D> inline
	void	_distance(InIt F, InIt L, D& N, input_iterator_tag)
	{
		for (; F != L; ++F)
		{
			++N;
		}
	}

	template <class InIt, class D> inline
	void	_distance(InIt F, InIt L, D& N, forward_iterator_tag)
	{
		for (; F != L; ++F)
		{
			++N;
		}
	}

	template <class InIt, class D> inline
	void	_distance(InIt F, InIt L, D& N, bidirectional_iterator_tag)
	{
		for (; F != L; ++F)
		{
			++N;
		}
	}

	template <class InIt, class D> inline
	void	_distance(InIt F, InIt L, D& N, random_access_iterator_tag)
	{
		N += L - F;
		// N = 0;
		// InIt it = F;
		// while (it != L)
		// {
		// 	++it;
		// 	++N;
		// }
	}

	template <class InIt, class D> inline
	void	distance(InIt F, InIt L, D& N)
	{
		typedef typename iterator_traits<InIt>::iterator_category category;
		_distance(F, L, N, category());
	}

	template <class InIt> inline
	typename iterator_traits<InIt>::difference_type distance(InIt F, InIt L)
	{
		typename iterator_traits<InIt>::difference_type N = 0;
		typedef typename iterator_traits<InIt>::iterator_category category;
		_distance(F, L, N, category());
		return (N);
	}

	template <class InIt, class D> 
	inline void	_advance(InIt &I, D N, input_iterator_tag)
	{
	for (; 0 < N; --N)
		++I;
	}

	template <class FwdIt, class D>
	inline void	_advance(FwdIt &I, D N, forward_iterator_tag)
	{
		for (; 0 < N; --N)
			++I;
	}

	template <class BidIt, class D>
	inline void	_advance (BidIt &I, D N, bidirectional_iterator_tag)
	{
		for (; 0 < N; --N)
			++I;
		for (; N < 0; ++N)
			--I;
	}

	template <class RanIt, class D>
	inline void	_advance (RanIt &I, D N, random_access_iterator_tag)
	{
		// I += N;
		if (N >= 0)
		{
			while (N > 0)
			{
				++I;
				--N;
			}
		}
	}

	template <class InIt, class D>
	inline void	advance (InIt& I, D N)
	{
		typedef typename iterator_traits<InIt>::iterator_category category;
		_advance(I, N, category());
	}

	template<class T1, class T2>
	struct pair
	{
		typedef	T1	first_type;
		typedef	T2	second_type;

		T1	first;
		T2	second;

		pair()
		: first(T1())
		, second(T2()) 
		{}

		pair(const T1 &V1, const T2 &V2)
		: first(V1)
		, second(V2)
		{}

		template<class U1, class U2>
		pair(const pair<U1, U2> &X)
		: first(X.first)
		, second(X.second)
		{}
	};

	template<class T1, class T2> 
	inline pair<T1, T2>	make_pair(const T1 &X, const T2 &Y) { return (pair<T1, T2>(X, Y)); }

	template<class T1, class T2>
	inline bool			operator==(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (X.first == Y.first && X.second == Y.second); }

	template<class T1, class T2>
	inline bool			operator!=(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (!(X == Y)); }

	template<class T1, class T2>
	inline bool			operator<(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (X.first < Y.first || (!(Y.first < X.first) && X.second < Y.second)); }

	template<class T1, class T2>
	inline bool			operator>(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (Y < X); }

	template<class T1, class T2>
	inline bool			operator<=(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (!(Y < X)); }

	template<class T1, class T2>
	inline bool			operator>=(const pair<T1,T2> &X, const pair<T1, T2> &Y) { return (!(X < Y)); }

}
