#pragma once

#include <memory>
#include "exception.hpp"

namespace ft
{

	template<class T, class Allocator>
	class vector_base
	{
	protected:
		typedef typename	Allocator::template rebind<T>::other	allocator_type;
		allocator_type		m_alloc;

		vector_base(Allocator A = Allocator())
		: m_alloc(A)
		{}
	};

	template<class T, class Allocator = std::allocator<T> >
	class vector: public vector_base<T, Allocator>
	{
	public:
		typedef				vector_base<T, Allocator>	Base;
		typedef typename	Base::allocator_type		allocator_type;
		typedef 			allocator_type				A;
		typedef typename	A::size_type				size_type;
		typedef typename	A::difference_type			difference_type;
		typedef typename	A::pointer					pointer;
		typedef typename	A::const_pointer			const_pointer;
		typedef typename	A::reference				reference;
		typedef typename	A::const_reference			const_reference;
		typedef typename	A::value_type				value_type;
typedef __gnu_cxx::__normal_iterator<pointer, vector>		iterator;
typedef __gnu_cxx::__normal_iterator<const_pointer, vector>	const_iterator;
        // typedef random_acsees_iterator<value_type, difference_type, pointer, reference, pointer, reference>        iterator;
        // typedef random_acsees_iterator<value_type, difference_type, const_pointer, const_reference, pointer, reference> const_iterator;
typedef std::reverse_iterator<iterator>						reverse_iterator;
typedef std::reverse_iterator<const_iterator>				const_reverse_iterator;

	private:
		pointer m_first;
		pointer m_last;
		pointer m_end;

//////////////////////////////////////////////////////////////////////////////////////////
// to algorithm
	private:
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

	template <class FwdIt, class T1>
	inline void fill(FwdIt F, FwdIt L, const T1& X)
	{
		for (; F != L ; ++F)
		{
			*F = X;
		}
	}
//////////////////////////////////////////////////////////////////////////////////////////
	private:
		bool	_buy(size_type N)
		{
			if (N == 0)
			{
				m_first = 0;
				m_last = 0;
				m_end = 0;
				return false;
			}
			else
			{
				m_first = this->m_alloc.allocate(N, (void*)0);
				m_last = m_first;
				m_end = m_first + N;
				return true;
			}
		}

		pointer	_ufill(pointer Q, size_type N, const T &X)
		{
			pointer Qs = Q;
			try
			{
				for(; 0 < N; --N, ++Q)
				{
					Base::m_alloc.construct(Q, X);
				}
			}
			catch(...)
			{
				_destroy(Qs, Q);
				throw;
			}
			return Q;
		}

		void	_destroy(pointer F, pointer L)
		{
			for(; F != L; ++F)
			{
				this->m_alloc.destroy(F);
			}
		}

		template<class It>
		pointer	_ucopy(It F, It L, pointer Q)
		{
			pointer Qs = Q;
			try
			{
				for(; F != L; ++Q, ++F)
				{
					this->m_alloc.construct(Q, *F);
				}
			}
			catch(...)
			{
				_destroy(Qs, Q);
				throw;
			}
			return Q;
		}

		template<class It>
void	_construct (It F, It L, std::__true_type) 
		{
			size_type N = (size_type)F;
			if(_buy(N))
			{
				m_last = _ufill(m_first, N, (T)L);
			}
		}

		template<class It>
void	_construct(It F, It L, std::__false_type)
		{
			_buy(0);
			insert(begin(), F, L);
		}

		void _clear()
		{
			if (m_first != 0)
			{
				_destroy(m_first, m_last);
				this->m_alloc.deallocate(m_first, m_end - m_first);
			}
			m_first = 0;
			m_last = 0;
			m_end = 0;
		}

		void _xlen() const
		{
			throw ft::exception("Out of length access");
		}

		void _xran() const
		{
			throw ft::exception("Out of range access");
		}

	public:
		vector()
		: Base()
		{
			_buy(0);
		}

		explicit vector(const A& Alloc)
		: Base(Alloc)
		{
			_buy(0);
		}

		explicit vector(size_type N)
		: Base()
		{
			if (_buy(N))
			{
				m_last = _ufill(m_first, N, T());
			}
		}

		vector(size_type N, const T& V)
		: Base()
		{
			if (_buy(N))
			{
				m_last = _ufill(m_first, N, V);
			}
		}

		vector(size_type N, const T& V, const A& Alloc)
		: Base(Alloc)
		{
			if (_buy(N))
			{
				m_last = _ufill(m_first, N, V);
			}
		}

		vector (const vector& X)
		: Base(X.m_alloc)
		{
			if (_buy(X.size()))
			{
				m_last = _ucopy(X.begin(), X.end(), m_first);
			}
		}

		template<class It>
		vector(It F, It L)
		: Base()
		{
typedef typename std::__is_integer<It>::__type _Integral;
			_construct(F, L, _Integral());
		}

		template<class It>
		vector(It F, It L, const A& Alloc)
		: Base(Alloc)
		{
typedef typename std::__is_integer<It>::__type _Integral;
			_construct(F, L, _Integral());
		}

		~vector()
		{
			_clear();
		}

		vector&	operator=(const vector& X)
		{
			if (this == &X) 
			{
				;
			}
			else if (X.size() == 0)
			{
				_clear();
			}
			else if (X.size() <= size())
			{
				pointer Q = copy(X.begin(), X.end(), m_first);
				_destroy(Q, m_last);
				m_last = m_first + X.size();
			}
			else if (X.size() <= capacity())
			{
				const_iterator S = X.begin() + size();
				copy(X.begin(), S, m_first);
				m_last = _ucopy(S, X.end(), m_last);
			}
			else
			{
				_destroy(m_first, m_last);
				this->m_alloc.deallocate(m_first, m_end - m_first);
				if (_buy(X.size()))
				{
					m_last = _ucopy(X.begin(), X.end(), m_first);
				}
			}
			return *this;
		}

		void	reserve(size_type N)
		{
			if (max_size() < N)
			{
				_xlen();
			}
			else if(capacity() < N)
			{
				pointer Q = this->m_alloc.allocate(N, (void*)0);
				try 
				{
					_ucopy(begin(), end(), Q);
				}
				catch (...) 
				{
					this->m_alloc.deallocate(Q, N);
					throw;
				}
				if (m_first != 0)
				{
					_destroy(m_first, m_last);
					this->m_alloc.deallocate(m_first, m_end - m_first);
				}
				m_end = Q + N;
				m_last = Q + size();
				m_first = Q;
			}
		}

		size_type				capacity() const{ return (m_first == 0 ? 0 : m_end - m_first); }
		iterator				begin() { return (iterator(m_first)); }
		const_iterator			begin() const { return (const_iterator(m_first)); }
		iterator				end() { return (iterator(m_last)); }
		const_iterator			end() const { return (const_iterator(m_last)); }
		reverse_iterator		rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator		rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
		
		void		resize(size_type N) { resize(N, T()); }
		void		resize(size_type N, T X)
		{
			if (size() < N)
			{
				insert (end(), N - size(), X);
			}
			else if (N < size())
			{
				erase (begin() + N, end());
			}
		}
	
		size_type	size() const { return (m_first == 0 ? 0 : m_last - m_first); }
		size_type	max_size() const { return (this->m_alloc.max_size()); }
		bool		empty() const { return (size() == 0); }
		A			get_allocator() const { return (this->m_alloc); }

		reference		at(size_type P)
		{
			if(size() <=P)
			{
				_xran();
			}
			return (*(begin() + P));
		}

		const_reference	at(size_type P) const
		{
			if (size() <= P)
			{
				_xran();
			}
			return (*(begin() + P));
		}

		const_reference		operator[](size_type P) const { return (*(begin() + P)); }
		reference			operator[](size_type P) { return (*(begin() + P)); }
		reference			front() { return (*begin()); }
		const_reference		front() const { return (*begin()); }
		reference			back() { return (*(end() - 1)); }
		const_reference		back() const { return (*(end() - 1)); }
		void				push_back(const T& X) { insert(end(), X); }
		void				pop_back() { erase(end() - 1); }

		template<class It>
		void	assign(It F, It L)
		{
typedef typename std::__is_integer<It>::__type _Integral;
			Assign(F, L, _Integral());
		}

		template<class It>
		void	Assign(It F, It L, std::__true_type)
		{
			assign((size_type)F, (T)L);
		}

		template<class It>
		void	Assign(It F, It L, std::__false_type)
		{
			erase (begin(), end());
			insert (begin(), F, L);
		}

		void	assign(size_type N, const T& X)
		{
			T	Tx = X;
			erase(begin(), end());
			insert(begin(), N, Tx);
		}

		iterator insert(iterator P, const T& X)
		{
			size_type	Off = size() == 0 ? 0 : P - begin();
			insert(P, (size_type)1, X);
			return (begin() + Off);
		}

		void insert(iterator P, size_type M, const T& X)
		{
			T			Tx = X;
			size_type	N = capacity();
			if (M == 0)
			{
				;
			}
			else if (max_size() - size() < M)
			{
				_xlen();
			}
			else if (N < size() + M)
			{

				// N = max_size() - N / 2 < N ? 0 : N + N / 2; 
				N = max_size() - N < N ? 0 : N * 2;
				if (N < size() + M)
					N = size() + M;
				// N = max_size() - N / 2 < N ? 0 : N + N / 2;
				// if (N * 1,5 < size() + M)
				// {
				// 	N = size() + M;
				// }
				// else
				// {
				// 	N = max_size() - N < N ? 0 : N * 2;
				// }
				pointer S = this->m_alloc.allocate(N, (void *)0);
				pointer Q;
				try
				{
					Q = _ucopy(begin(), P, S);
					Q = _ufill(Q, M, Tx);
					_ucopy(P, end(), Q);
				}
				catch (...)
				{
					_destroy(S, Q);
					this->m_alloc.deallocate(S, N);
					throw;
				}
				if (m_first != 0)
				{
					_destroy(m_first, m_last);
					this->m_alloc.deallocate(m_first, m_end - m_first);
				}
				m_end = S + N;
				m_last = S + size() + M;
				m_first = S;
			}
			else if ((size_type)(end() - P) < M)
			{
				_ucopy(P, end(), P.base() + M);
				try
				{
					_ufill(m_last, M - (end() - P), Tx);
				}
				catch(...) {
					_destroy(P.base() + M, m_last + M);
					throw;
				}
				m_last += M;
				fill(P, end() - M, Tx);
			}
			else
			{
				iterator Oend = end();
				m_last = _ucopy(Oend - M, Oend, m_last);
				copy_backward(P, Oend - M, Oend);
				fill(P, P + M, Tx);
			}
		}

		template<class It>
		void	insert(iterator P, It F, It L)
		{
			typedef typename std::__is_integer<It>::__type _Integral;
			Insert(P, F, L, _Integral());
		}

		template<class It>
		void	Insert(iterator P, It F, It L, std::__true_type)
		{
			insert(P, (size_type)F, (T)L);
		}

		template<class It>
		void	Insert(iterator P, It F, It L, std::__false_type)
		{
			Insert2(P, F, L, std::__iterator_category(F));
		}

		template<class It>
		void	Insert2(iterator P, It F, It L, std::input_iterator_tag)
		{
			for (; F != L; ++F, ++P)
				P = insert (P, *F);
		}
		template<class It>
		void	Insert2(iterator P, It F, It L, std::forward_iterator_tag)
		{
			size_type	M = std::distance(F, L);
			size_type	N = capacity();
			if (M == 0)
			{
				;
			}
			else if (max_size() - size() < M)
			{
				_xlen();
			}
			else if(N < size() + M)
			{
				// N = max_size() - N / 2 < N ? 0 : N + N / 2;
				N = max_size() - N < N ? 0 : N * 2;
				if (N < size() + M)
					N = size() + M;
				pointer S = this->m_alloc.allocate(N, (void *)0);
				pointer Q;
				try
				{
					Q = _ucopy(begin(), P, S);
					Q = _ucopy(F, L, Q);
					_ucopy(P, end(), Q);
				}
				catch (...)
				{
					_destroy(S, Q);
					this->m_alloc.deallocate(S, N);
					throw;
				}
				if (m_first != 0)
				{
					_destroy(m_first, m_last);
					this->m_alloc.deallocate(m_first, m_end - m_first);
				}
				m_end = S + N;
				m_last = S + size() + M;
				m_first = S;
			}
			else if ((size_type)(end() - P) < M)
			{
				_ucopy(P, end(), P.base() + M);
				It Mid = F;
				std::advance(Mid, end() - P);
				try
				{
					_ucopy(Mid, L, m_last);
				}
				catch (...)
				{
					_destroy (P.base() + M, m_last + M);
					throw;
				}
				m_last += M;
				copy(F, Mid, P);
			}
			else if (0 < M)
			{
				iterator Oend = end();
				m_last = _ucopy(Oend - M, Oend, m_last);
				copy_backward(P, Oend - M, Oend);
				copy(F, L, P);
			}
		}

		iterator	erase(iterator P)
		{
			copy(P + 1, end(), P);
			_destroy(m_last - 1, m_last);
			--m_last;
			return P;
		}

		iterator	erase(iterator F, iterator L)
		{
			if (F != L)
			{
				pointer S = copy(L, end(), F.base());
				_destroy(S, m_last);
				m_last = S;
			}
			return F;
		}

		void	clear()
		{
			erase(begin(), end());
		}

bool	Eq(const vector& X) const {
	return (size() == X.size() && std::equal(begin(), end(), X.begin()));
}

bool	Lt(const vector& X) const {
	return (std::lexicographical_compare(begin(), end(), X.begin(), X.end()));
}

		void	swap(vector& X)
		{
			if (this->m_alloc == X.m_alloc)
			{
				std::swap(m_first, X.m_first);
				std::swap(m_last, X.m_last);
				std::swap(m_end, X.m_end);
			}
			else 
			{
				vector Ts = *this;
				*this = X;
				X = Ts;
			}
		}

	};

	template<class T, class A> inline
	bool	operator==(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (X.Eq(Y));
	}

	template<class T, class A> inline
	bool	operator!=(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (!(X == Y));
	}

	template<class T, class A> inline
	bool	operator<(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (X.Lt(Y));
	}
	
	template<class T, class A> inline
	bool	operator>(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (Y < X);
	}

	template<class T, class A> inline
	bool	operator<=(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (!(Y < X));
	}
	
	template<class T, class A> inline
	bool	operator>=(const vector<T, A>& X, const vector<T, A>& Y)
	{
		return (!(X < Y));
	}
	
	template<class T, class A> inline
	void	swap(vector<T, A>& X, vector<T, A>& Y)
	{
		X.swap(Y);
	}

}
