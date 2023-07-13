#pragma once

#include "xutility.hpp"

namespace ft
{
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

// // TEMPLATE FUNCTION mismatch (шаблонная функция mismatch) template<class Inltl, class Inlt2> inline
// pair<lnltl, Inlt2> mismatch(Inltl F, Inltl L, Inlt2 X)
// {
// 	for (; F 1= L && *F == *X; ++F, ++X)
// 		;
// 	return (pair<lnltl, InIt2>(F, X));
// }
// // TEMPLATE FUNCTION mismatch WITH PRED // шаблонная функция mismatch c Pred) template<class Inltl, class Inlt2, class Pr> inline
// pair<lnltl, Inlt2> mismatch(Inltl F, Inltl L, Inlt2 X, Pr P)
// {
// 	for (; F != L && P (*F, *X) ; + + F, ++X)
// 		;
// 	return (pair<lnltl, InIt2>(F, X));
// }

	template<class Inltl, class Inlt2> 
	inline bool equal (Inltl F, Inltl L, Inlt2 X)
	{
		for (; F != L && *F == *X; ++F, ++X)
			;
		return (F == L);
		// return (mismatch(F, L, X). first == L);
	}
	template<class Inltl, class Inlt2, class Pr>
	inline bool equal(Inltl F, Inltl L, Inlt2 X, Pr P)
	{
		for (; F != L && P (*F, *X) ; ++F, ++X)
			;
		return (F == L);
		// {return (mismatch(F, L, X, P).first == L);
	}

	template<class T>
	inline void	swap(T& X, T& Y)
	{
		T	Tmp = X;
		X = Y;
		Y = Tmp;
	}

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
