#pragma once

#include "xutility.hpp"
#include <iostream>

namespace ft
{
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

	template<typename T1, typename T2>
	std::ostream& operator<<(std::ostream& os, const ft::pair<T1, T2>& p)
	{
		os << "(" << p.first << ", " << p.second << ")";
		return os;
	}

	template <class InIt, class OutIt>
	inline OutIt	copy(InIt F, InIt L, OutIt X)
	{
		for (; F != L; ++X, ++F)
		{
			*X = *F;
		}
		return (X);
	}

	template <class BidIt1, class BidIt2>
	inline BidIt2	copy_backward(BidIt1 F, BidIt1 L, BidIt2 X)
	{
		while (F != L)
		{
			*--X = *--L;
		}
		return (X);
	}

	template <class FwdIt, class T>
	inline void fill(FwdIt F, FwdIt L, const T& X)
	{
		for (; F != L ; ++F)
		{
			*F = X;
		}
	}

	template<class Inltl, class Inlt2> 
	inline bool	lexicographical_compare(Inltl F1, Inltl L1, Inlt2 F2, Inlt2 L2)
	{
		for (; F1 != L1 && F2 != L2; ++F1, ++F2)
		{
			if (* F1 < *F2)
			{
				return (true);
			}
			else if (*F2 < *F1)
			{
				return (false);
			}
		}
		return (F1 == L1 && F2 != L2);
	}

	template<class Inltl, class Inlt2, class Pr>
	inline bool	lexicographical_compare(Inltl F1, Inltl L1, Inlt2 F2, Inlt2 L2, Pr P)
	{
		for (; F1 != L1 && F2 != L2; ++F1, ++F2)
		{
			if (P(*F1, *F2))
			{
				return (true);
			}
			else if (P(*F2, *F1))
			{
				return (false);
			}
		}
		return (F1 == L1 && F2 != L2);
	}

	template<class InIt1, class InIt2> inline
	pair<InIt1, InIt2> mismatch(InIt1 F, InIt1 L, InIt2 X)
	{
		for (; F != L && *F == *X; ++F, ++X)
			;
		return (pair<InIt1, InIt2>(F, X));
	}

	template<class InIt1, class InIt2, class Pr> inline
	pair<InIt1, InIt2> mismatch(InIt1 F, InIt1 L, InIt2 X, Pr P)
	{
		for (; F != L && P(*F, *X) ; ++F, ++X)
			;
		return (pair<InIt1, InIt2>(F, X));
	}

	template<class Inltl, class Inlt2> 
	inline bool equal(Inltl F, Inltl L, Inlt2 X)
	{
		return (ft::mismatch(F, L, X). first == L);
	}
	template<class Inltl, class Inlt2, class Pr>
	inline bool equal(Inltl F, Inltl L, Inlt2 X, Pr P)
	{
		return (ft::mismatch(F, L, X, P).first == L);
	}

	template<class T>
	inline void	swap(T& X, T& Y)
	{
		T	Tmp = X;
		X = Y;
		Y = Tmp;
	}

	template<class Al, class A2, class R>
	struct binary_function
	{
		typedef	Al	first_argument_type;
		typedef	A2	second_argument_type;
		typedef	R	result_type;
	};

	template<class T>
	struct less : binary_function<T, T, bool>
	{
		bool operator()(const T& X, const T& Y) const
		{
			return (X < Y);
		}
	};

	template<class T>
	struct greater : binary_function<T, T, bool>
	{
		bool operator()(const T& X, const T& Y) const
		{
			return (X > Y);
		}
	};

	template<class T>
	struct equal_to : binary_function<T, T, bool> 
	{
		bool operator()(const T& X, const T& Y) const
		{
			return (X == Y);
		}
	};

	struct false_type {};
	struct true_type {};

	template<class T> struct is_primitive_type : public false_type {};
	template <> struct is_primitive_type<bool> : public true_type {};
	template <> struct is_primitive_type<char> : public true_type {};
	template <> struct is_primitive_type<wchar_t> : public true_type {};
	template <> struct is_primitive_type<signed char> : public true_type {};
	template <> struct is_primitive_type<short int> : public true_type {};
	template <> struct is_primitive_type<int> : public true_type {};
	template <> struct is_primitive_type<long int> : public true_type {};
	template <> struct is_primitive_type<unsigned char> : public true_type {};
	template <> struct is_primitive_type<unsigned short int> : public true_type {};
	template <> struct is_primitive_type<unsigned int> : public true_type {};
	template <> struct is_primitive_type<unsigned long int> : public true_type {};

}
