#pragma once

#include <memory>
#include "../utility/exception.hpp"
#include "../utility/xutility.hpp"
#include "../utility/algorithm.hpp"

namespace ft
{

	template<class T, class Allocator>
	class Deque_map
	{
	protected:
		typedef typename	Allocator::template rebind<T>::other::pointer	pointer;
		typename			Allocator::template rebind<pointer>::other		Alloc_map;

		Deque_map(Allocator A)
		: Alloc_map(A)
		{}
	};

	template<class T, class Allocator>
	class Deque_val : public Deque_map<T, Allocator>
	{
		protected:
			typedef typename	Allocator::template rebind<T>::other	allocator_type;
			allocator_type		m_alloc;

		Deque_val(Allocator A = Allocator())
		: Deque_map<T, Allocator>(A)
		, m_alloc(A)
		{}
	};

	template<class T, class Allocator = std::allocator<T> >
	class deque	: public Deque_val<T, Allocator>
	{
	public:
		enum { DEQUEMAPSIZ = 8};
		enum { DEQUESIZ = sizeof(T) <= 1 ? 16 \
				: sizeof(T) <= 2 ? 8 \
				: sizeof(T) <= 4 ? 4 \
				: sizeof(T) <= 8 ? 2 : 1 };

		typedef				Deque_val<T, Allocator>	Base;
		typedef typename	Base::allocator_type	A;
		typedef				A						allocator_type;
		typedef typename	A::size_type			size_type;
		typedef typename	A::difference_type		difference_type;
		typedef				difference_type			Dift;
		typedef typename	A::pointer				pointer;
		typedef				pointer					Tptr;
		typedef typename	A::const_pointer		const_pointer;
		typedef				const_pointer			Ctptr;
		typedef typename	A::reference			reference;
		typedef				reference				Tref;
		typedef typename	A::const_reference		const_reference;
		typedef typename	A::value_type			value_type;

		typedef typename	A::template rebind<pointer>::other::pointer	Map_ptr;

	protected:
		Map_ptr		m_map;
		size_type	m_mapsize;
		size_type	m_offset;
		size_type	m_size;

	public:
		friend class deque_iterator;
		class deque_iterator : public ft::iterator<random_access_iterator_tag, T, Dift, Tptr, Tref>
		{
		public:
			typedef typename	deque_iterator::iterator_category	iterator_category;
			typedef typename	deque_iterator::value_type			value_type;
			typedef typename	deque_iterator::difference_type		difference_type;
			typedef typename	deque_iterator::pointer				pointer;
			typedef typename	deque_iterator::reference			reference;

		protected:
			difference_type	Idx;
			const deque		*Deque;

		public:
			deque_iterator()
			: Idx(0)
			, Deque(0)
			{}

			deque_iterator(difference_type I, const deque *P)
			: Idx(I)
			, Deque(P)
			{}

			reference				operator*() const
			{
				size_type Block = Idx / DEQUESIZ;
				size_type Off = Idx - Block * DEQUESIZ;
				if (Deque->m_mapsize <= Block)
				{
					Block -= Deque->m_mapsize;
				}
				return ((Deque->m_map)[Block][Off]);
			}

			Tptr					operator->() const
			{
				return (&**this);
			}
			
			deque_iterator&			operator++()
			{
				++Idx;
				return (*this);
			}

			deque_iterator			operator++(int)
			{
				deque_iterator tmp = *this;
				++*this;
				return (tmp);
			}

			deque_iterator&			operator--()
			{
				--Idx;
				return (*this);
			}
			
			deque_iterator			operator--(int)
			{
				deque_iterator tmp = *this;
				--*this;
				return (tmp);
			}

			deque_iterator&			operator+=(difference_type N)
			{
				Idx += N;
				return (*this);
			}

			deque_iterator&			operator-=(difference_type N)
			{
				return (*this += -N);
			}

			deque_iterator			operator+(difference_type N) const
			{
				deque_iterator tmp = *this;
				return (tmp += N);
			}

			friend deque_iterator	operator+(difference_type N, const deque_iterator& Y)
			{
				deque_iterator tmp = Y;
				return tmp += N;
			}

			deque_iterator			operator-(difference_type N) const
			{
				deque_iterator tmp = *this;
				return (tmp -= N);
			}

			difference_type			operator-(const deque_iterator& X) const
			{
				return (Idx - X.Idx);
			}
			
			reference				operator[](difference_type N) const
			{
				return (*(*this + N));
			}

			difference_type			getIdx() const { return Idx; }
			const deque				*getDeque() const { return Deque; };

			bool					operator==(const deque_iterator& X) const { return (Deque == X.Deque && Idx == X.Idx); }
			bool					operator!=(const deque_iterator& X) const { return (!(*this == X)); }
			bool					operator<(const deque_iterator& X) const { return (Idx < X.Idx); }
			bool					operator<=(const deque_iterator& X) const { return (!(X < *this)); }
			bool					operator>(const deque_iterator& X) const { return (X < *this); }
			bool					operator>=(const deque_iterator& X) { return (!(*this < X)); }
		};

		friend class const_deque_iterator;
		class const_deque_iterator : public ft::iterator<random_access_iterator_tag, T, Dift, Ctptr, const_reference>
		{
		public:
			typedef typename	const_deque_iterator::iterator_category	iterator_category;
			typedef typename	const_deque_iterator::value_type		value_type;
			typedef typename	const_deque_iterator::difference_type	difference_type;
			typedef typename	const_deque_iterator::pointer			pointer;
			typedef typename	const_deque_iterator::reference			reference;

		protected:
			difference_type Idx;
			const deque *Deque;

		public:
			const_deque_iterator()
			: Idx(0)
			, Deque(0)
			{}

			const_deque_iterator(difference_type I, const deque *P)
			: Idx(I)
			, Deque(P)
			{}

			const_deque_iterator(const deque_iterator& X)
			: Idx(X.getIdx())
			, Deque(X.getDeque())
			{}

			const_reference				operator*() const
			{
				size_type Block = Idx / DEQUESIZ;
				size_type Off = Idx - Block * DEQUESIZ;
				if (Deque->m_mapsize <= Block)
				{
					Block -= Deque->m_mapsize;
				}
				return ((Deque->m_map)[Block][Off]);
			}

			Ctptr						operator->() const
			{
				return (&**this);
			}
			
			const_deque_iterator&		operator++()
			{
				++Idx;
				return (*this);
			}

			const_deque_iterator		operator++(int)
			{
				const_deque_iterator tmp = *this;
				++*this;
				return (tmp);
			}

			const_deque_iterator&		operator--()
			{
				--Idx;
				return (*this);
			}
			
			const_deque_iterator		operator--(int)
			{
				const_deque_iterator tmp = *this;
				--*this;
				return (tmp);
			}

			const_deque_iterator&		operator+=(difference_type N)
			{
				Idx += N;
				return (*this);
			}

			const_deque_iterator&		operator-=(difference_type N)
			{
				return (*this += -N);
			}

			const_deque_iterator		operator+(difference_type N) const
			{
				const_deque_iterator tmp = *this;
				return (tmp += N);
			}

			friend const_deque_iterator	operator+(difference_type N, const const_deque_iterator& Y)
			{
				const_deque_iterator tmp = Y;
				return tmp += N;
			}

			const_deque_iterator		operator-(difference_type N) const
			{
				const_deque_iterator tmp = *this;
				return (tmp -= N);
			}

			difference_type				operator-(const const_deque_iterator& X) const
			{
				return (Idx - X.Idx);
			}
			
			reference					operator[](difference_type N) const
			{
				return (*(*this + N));
			}
			
			bool						operator==(const const_deque_iterator& X) const { return (Deque == X.Deque && Idx == X.Idx); }
			bool						operator!=(const const_deque_iterator& X) const { return (!(*this == X)); }
			bool						operator<(const const_deque_iterator& X) const { return (Idx < X.Idx); }
			bool						operator<=(const const_deque_iterator& X) const { return (!(X < *this)); }
			bool						operator>(const const_deque_iterator& X) const { return (X < *this); }
			bool						operator>=(const const_deque_iterator& X) { return (!(*this < X)); }
		};

		typedef	deque_iterator							iterator;
		typedef	const_deque_iterator					const_iterator;
		typedef	ft::reverse_iterator<iterator>			reverse_iterator;
		typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;

		deque()
		: Base()
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{}

		explicit deque(const Allocator& A)
		: Base(A)
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{}

		explicit deque(size_type N)
		: Base()
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			insert(begin(), N, T());
		}

		deque(size_type N, const T& V)
		: Base()
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			insert(begin(), N, V);
		}

		deque(size_type N, const T& V, const Allocator& A)
		: Base(A)
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			insert(begin(), N, V);
		}

		deque(const deque& X)
		: Base(X.m_alloc)
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			insert(begin(), X.begin(), X.end());
		}

		template<class It>
		deque (It F, It L)
		: Base()
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			_construct(F, L, ft::is_primitive_type<It>());
		}

		template<class It>
		deque(It F, It L, const Allocator& A)
		: Base(A)
		, m_map(0)
		, m_mapsize(0)
		, m_offset(0)
		, m_size(0)
		{
			_construct(F, L, ft::is_primitive_type<It>());
		}

		~deque()
		{
			clear();
		}

		deque&	operator=(const deque& X)
		{
			if (this == &X)
			{
				;
			}
			else if (X.size() == 0)
			{
				clear();
			}
			else if (X.size() <= size())
			{
				iterator S = ft::copy(X.begin(), X.end(), begin());
				erase(S, end());
			}
			else
			{
				const_iterator Sx = X.begin() + size();
				ft::copy(X.begin(), Sx, begin());
				insert(end(), Sx, X.end());
			}
			return (*this);
		}

		iterator				begin() { return (iterator(m_offset, this)); }
		const_iterator			begin() const {return (const_iterator(m_offset, this)); }
		iterator				end() { return (iterator(m_offset + m_size, this)); }
		const_iterator			end() const { return (const_iterator(m_offset + m_size, this)); };
		reverse_iterator		rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator		rend() { return (reverse_iterator (begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
		
		void					resize(size_type N) { resize (N, T()); }
		void					resize(size_type N, T X)
		{
			if (size() < N)
			{
				insert(end(), N - size(), X);
			}
			else if (N < size())
			{
				erase(begin() + N, end());
			}
		}
		
		size_type				size() const { return (m_size); }
		size_type				max_size() const { return (this->m_alloc.max_size()); }
		bool					empty() const { return (size() == 0); }
		allocator_type			get_allocator() const { return (this->m_alloc); }

		const_reference			at(size_type P) const
		{
			if (size() <= P)
			{
				_xran();
			}
			return (*(begin() + P));
		}

		reference				at(size_type P)
		{
			if (size() <= P)
			{
				_xran();
			}
			return (*(begin() + P));
		}

		reference				operator[](size_type P) { return (*(begin() + P)); }	
		const_reference			operator[](size_type P) const { return (*(begin() + P));  }
		reference				front() { return (*begin()); }
		const_reference			front() const { return (*begin()); }
		reference				back() { return (*(end() - 1)); }
		const_reference			back() const { return (*(end() - 1)); }

		void	push_front(const T& X)
		{
			if (m_offset % DEQUESIZ == 0 && m_mapsize <= (m_size + DEQUESIZ) / DEQUESIZ) 
			{
				_growmap(1);
			}
			size_type Newoff = m_offset != 0 ? m_offset : m_mapsize * DEQUESIZ;
			size_type Block = --Newoff / DEQUESIZ;
			if (m_map[Block] == 0)
			{
				m_map[Block] = this->m_alloc.allocate(DEQUESIZ, (void*)0);
			}
			try
			{
				m_offset = Newoff;
				++m_size;
				this->m_alloc.construct(m_map[Block] + Newoff % DEQUESIZ, X);
			}
			catch(...)
			{
				pop_front();
				throw;
			}
		}

		void	pop_front()
		{
			if (!empty())
			{
				size_type Block = m_offset / DEQUESIZ;
				this->m_alloc.destroy(m_map[Block] + m_offset % DEQUESIZ);
				if (m_mapsize * DEQUESIZ <= ++m_offset)
				{
					m_offset = 0;
				}
				if (--m_size == 0)
				{
					m_offset =0;
				}
			}
		}

		void	push_back(const T& X)
		{
			if ((m_offset + m_size) % DEQUESIZ == 0 && m_mapsize <= (m_size + DEQUESIZ) / DEQUESIZ)
			{
				_growmap(1);
			}
			size_type Newoff = m_offset + m_size;
			size_type Block = Newoff / DEQUESIZ;
			if (m_mapsize <= Block)
			{
				Block -= m_mapsize;
			}
			if (m_map[Block] == 0)
			{
				m_map[Block] = this->m_alloc.allocate(DEQUESIZ, (void *)0);
			}
			try
			{
				++m_size;
				this->m_alloc.construct(m_map[Block] + Newoff % DEQUESIZ, X);
			}
			catch(...)
			{
				pop_back();
				throw;
			}
		}

		void	pop_back()
		{
			if (!empty())
			{
				size_type Newoff = m_size + m_offset - 1;
				size_type Block = Newoff / DEQUESIZ;
				if (m_mapsize <= Block)
				{
					Block -= m_mapsize;
				}
				this->m_alloc.destroy(m_map[Block] + Newoff % DEQUESIZ);
				if (--m_size == 0)
				{
					m_offset = 0;
				}
			}
		}

		template<class It>
		void	assign(It F, It L)
		{
			_assign(F, L, ft::is_primitive_type<It>());
		}


		void	assign(size_type N, const T& X)
		{
			T Tx = X;
			erase(begin(), end());
			insert(begin(), N, Tx);
		}

		iterator	insert(iterator P, const T& X)
		{
			if (P == begin())
			{
				push_front(X);
				return (begin());
			}
			else if (P == end())
			{
				push_back(X);
				return (end() - 1);
			}
			else
			{
				iterator S;
				size_type Off = P - begin();
				T Tx = X;
				if (Off < size() / 2)
				{
					push_front(front());
					S = begin() + Off;
					ft::copy(begin() + 2, S + 1, begin() + 1);
				}
				else
				{
					push_back(back());
					S = begin() + Off;
					ft::copy_backward(S, end() - 2, end() - 1);
				}
				*S = Tx;
				return (S);
			}
		}

		void	insert(iterator P, size_type M, const T& X)
		{
			iterator S;
			size_type I;
			size_type Off = P - begin();
			size_type Rem = m_size - Off;
			if (Off < Rem)
			{
				if (Off < M)
				{
					for(I = M - Off; 0 < I; --I)
					{
						push_front(X);
					}
					for(I = Off; 0 < I; --I)
					{
						push_front(begin()[M - 1]);
					}
					S = begin() + M;
					ft::fill(S, S + Off, X);
				}
				else
				{
					for(I = M; 0 < I; --I)
					{
						push_front(begin()[M - 1]);
					}
					S = begin() + M;
					T Tx = X;
					ft::copy(S + M, S + Off, S);
					ft::fill(begin() + Off, S + Off, Tx);
				}
			}
			else
			{
				if (Rem < M)
				{
					for(I = M - Rem; 0 < I; --I)
					{
						push_back(X);
					}
					for(I = 0; I < Rem; ++I)
					{
						push_back(begin()[Off + I]);
					}
					S = begin() + Off;
					ft::fill(S, S + Rem, X);
				}
				else
				{
					for(I = 0; I < M; ++I)
					{
						push_back(begin()[Off + Rem - M + I]);
					}
					S = begin() + Off;
					T Tx = X;
					ft::copy_backward(S, S + Rem - M, S + Rem);
					ft::fill(S, S + M, Tx); 
				}
			}
		}
			
		template<class It>
		void	insert(iterator P, It F, It L)
		{
			_insert(P, F, L, ft::is_primitive_type<It>());
		}

		iterator erase(iterator P)
		{
			return (erase(P, P + 1));
		}

		iterator erase(iterator F, iterator L)
		{
			size_type N = L - F;
			size_type M = F - begin();
			if (M < (size_type)(end() - L))
			{
				ft::copy_backward(begin(), F, L);
				for(; 0 < N; --N)
				{
					pop_front();
				}
			}
			else
			{
				ft::copy(L, end(), F);
				for(; 0 < N; --N)
				{
					pop_back();
				}
			}
			return (M == 0 ? begin() : begin() + M);
		}

		void	clear()
		{
			while (!empty())
			{
				pop_back();
			}
			_freemap();
		}

		void	swap(deque& X)
		{
			if (this->m_alloc == X.m_alloc)
			{
				ft::swap(m_map, X.m_map);
				ft::swap(m_mapsize, X.m_mapsize);
				ft::swap(m_offset, X.m_offset);
				ft::swap(m_size, X.m_size);
			}
			else
			{
				deque Ts = *this;
				*this = X;
				X = Ts;
			}
		}

	private:

		template<class It>
		void	_construct(It F, It L, ft::true_type)
		{
			insert(begin(), (size_type)F, (T)L);
		}
		
		template<class It>
		void	_construct(It F, It L, ft::false_type)
		{
			insert(begin(), F, L);
		}

		template<class It>
		void	_assign(It F, It L, ft::true_type)
		{
			assign((size_type)F, (T)L);
		}

		template<class It>
		void	_assign(It F, It L, ft::false_type)
		{
			erase(begin(), end());
			insert (begin(), F, L);
		}

		template<class It>
		void	_insert(iterator P, It F, It L, ft::true_type)
		{
			insert(P, (size_type)F, (T)L);
		}

		template<class It>
		void	_insert(iterator P, It F, It L, ft::false_type)
		{
			typedef typename iterator_traits<It>::iterator_category category;
			_insert_iter_type(P, F, L, category());
		}

		template<class It>
		void	_insert_iter_type(iterator P, It F, It L, input_iterator_tag)
		{
			size_type Off = P - begin();
			for(; F != L; ++F, ++Off)
			{
				insert(begin() + Off, *F);
			}
		}

		template<class It>
		void	_insert_iter_type(iterator P, It F, It L, bidirectional_iterator_tag)
		{
			size_type M = 0;
			ft::distance(F, L, M);
			size_type I;
			size_type Off = P - begin();
			size_type Rem = m_size - Off; 
			if (Off < Rem)
			{
				if (Off < M)
				{
					It Qx = F;
					ft::advance(Qx, M - Off);
					for(It Q = Qx; F != Q;)
					{
						push_front(*--Q);
					}
					for(I = Off; 0 < I; --I)
					{
						push_front(begin()[M - 1]);
					}
					ft::copy(Qx, L, begin() + M);
				}
				else
				{
					for(I = M; 0 < I; --I)
					{
						push_front(begin()[M - 1]);
					}
					iterator S = begin() + M;
					ft::copy(S + M, S + Off, S);
					ft::copy(F, L, begin() + Off);
				}
			}
			else
			{
				if (Rem < M)
				{
					It Qx = F;
					ft::advance(Qx, Rem);
					for(It Q = Qx; Q != L; ++Q)
					{
						push_back(*Q);
					}
					for(I = 0; I < Rem; ++I)
					{
						push_back(begin()[Off + I]);
					}
					ft::copy(F, Qx, begin() + Off);
				}
				else
				{
					for(I = 0; I < M; ++I)
					{
						push_back(begin()[Off + Rem - M + I]);
					}
					iterator S = begin() + Off;
					ft::copy_backward(S, S + Rem - M, S + Rem);
					ft::copy(F, L, S); 
				}
			}
		}

		void	_xlen() const
		{
			throw ft::exception("deque<T> too long");
		}

		void	_xran() const
		{
			throw ft::exception("deque<T> subscript");
		}
		
		void	_freemap()
		{
			for(size_type M = m_mapsize; 0 < M; )
			{
				this->m_alloc.deallocate(*(m_map + --M), DEQUESIZ);
				this->Alloc_map.destroy(m_map + M);
			}
			this->Alloc_map.deallocate(m_map, m_mapsize);
			m_mapsize = 0;	
			m_map = 0;
		}

		void _growmap(size_type N)
		{
			if (max_size() / DEQUESIZ - m_mapsize < N)
			{
				_xlen();
			}
			size_type I = m_mapsize / 2;
			if (I < DEQUEMAPSIZ)
			{
				I = DEQUEMAPSIZ;
			}
			if (N < I && m_mapsize <= max_size() / DEQUESIZ - I)
			{
				N = I;
			}
			size_type Ib = m_offset / DEQUESIZ;
			Map_ptr M = this->Alloc_map.allocate(m_mapsize + N, (void *)0);
			Map_ptr Mn = M + Ib;
			for(I = Ib; I < m_mapsize; ++I, ++Mn)
			{
				this->Alloc_map.construct(Mn, m_map[I]);
				this->Alloc_map.destroy(m_map + I);
			}
			if (Ib <= N)
			{
				for(I = 0; I < Ib; ++I, ++Mn)
				{
					this->Alloc_map.construct(Mn, m_map[I]);
					this->Alloc_map.destroy(m_map + I);
					this->Alloc_map.construct(M + I, pointer());
				}
				for(; I < N; ++I, ++Mn)
				{
					this->Alloc_map.construct(Mn, pointer());
				}
			}
			else
			{
				for(I = 0; I < N; ++I, ++Mn)
				{
					this->Alloc_map.construct(Mn, m_map[I]);
					this->Alloc_map.destroy(m_map + I);
				}
				for(Mn = M; I < Ib; ++I, ++Mn)
				{
					this->Alloc_map.construct(Mn, m_map[I]);
					this->Alloc_map.destroy(m_map + I);
				}
				for(I = 0; I < N; ++I, ++Mn)
				{
					this->Alloc_map.construct(Mn, pointer());
				}
			}

			this->Alloc_map.deallocate(m_map, m_mapsize);
			m_map = M;
			m_mapsize += N;
		}

	};

template<class T, class A>
inline void	swap(deque<T, A>& X, deque<T, A>& Y) { X.swap(Y); }

template<class T, class A>
inline bool	operator==(const deque<T, A>& X, const deque<T, A>& Y) { return (X.size() == Y.size() && equal(X.begin(), X.end(), Y.begin())); }

template<class T, class A>
inline bool	operator!=(const deque<T, A>& X, const deque<T, A>& Y) { return (!(X == Y)); }

template<class T, class A>
inline bool	operator<(const deque<T, A>& X, const deque<T, A>& Y) { return (ft::lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end())); }

template<class T, class A>
inline bool operator<=(const deque<T, A>& X, const deque<T, A>& Y) { return (!(Y < X)); }

template<class T, class A>
inline bool operator>(const deque<T, A>& X, const deque<T, A>& Y) { return (Y < X); }

template<class T, class A>
inline bool operator>=(const deque<T, A>& X, const deque<T, A>& Y) { return (! (X < Y) ); }

}
