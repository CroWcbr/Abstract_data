#pragma once

namespace ft
{
	template<class It, class Diff, class T, class Pr>
	inline void	_push_heap(It F, Diff H, Diff J, T V, Pr P)
	{
		for (Diff I = (H - 1) / 2; J < H && P(*(F + I), V); I = (H - 1) / 2)
		{
			*(F + H) = *(F + I);
			H = I;
		}
		*(F + H) = V;
	}

	template<class It, class Diff, class T, class Pr> 
	inline void	_adjust_heap(It F, Diff H, Diff N, T V, Pr P)
	{
		Diff J = H;
		Diff K = 2 * H + 2;

		for (; K < N; K = 2 * K + 2)
		{
			if (P(*(F + K), *(F + (K - 1))))
				--K;
			*(F + H) = *(F + K);
			H = K;
		}

		if (K == N)
		{
			*(F + H) = *(F + (K - 1));
			H = K - 1;
		}
		_push_heap(F, H, J, V, P);
	}

	template<class It, class Pr>
	void make_heap(It F, It L, Pr P)
	{
		if (2 <= L - F)
		{
			typedef typename	It::difference_type		Diff;
			typedef typename	It::value_type			Val;
			
			Diff N = L - F;
			for (Diff H = N / 2; 0 < H; )
			{
				--H;
				_adjust_heap(F, H, N, Val(*(F + H)), P);
			}
		}
	}

	template<class It, class Pr>
	void push_heap(It F, It L, Pr P)
	{
		typedef typename	It::difference_type		Diff;
		typedef typename	It::value_type			Val;

		_push_heap(F, Diff(L - F - 1), Diff(0), Val(*(L - 1)), P);
	}

	template<class It, class Pr>
	void pop_heap(It F, It L, Pr P)
	{
		typedef typename	It::difference_type		Diff;
		typedef typename	It::value_type			Val;

		if (1 < L - F)
			_adjust_heap(F, Diff(0), Diff(L - F - 1), Val(*(L - 1)), P);
	}
}
