#pragma once

#include <memory>
#include "../utility/exception.hpp"
#include "../utility/xutility.hpp"
#include "../utility/algorithm.hpp"

namespace ft
{
	template<class T, class Allocator> 
	class List_nod
	{
	protected:

		friend struct Node;
		struct Node
		{
			Node*		m_next;
			Node*		m_prev;
			T			m_value;
		};

		List_nod(Allocator A)
		: Alloc_node(A)
		{}

		typename	Allocator::template rebind<Node>::other	Alloc_node;
	};

	template<class T, class Allocator>
	class List_ptr : public List_nod<T, Allocator>
	{
	protected:
		typedef typename	List_nod<T, Allocator>::Node						Node;
		typedef typename	Allocator::template rebind<Node>::other::pointer	Node_ptr;
		typename			Allocator::template rebind<Node_ptr>::other			Alloc_ptr;

		List_ptr(Allocator A)
		: List_nod<T, Allocator>(A)
		, Alloc_ptr(A)
		{}
	};

	template<class T, class Allocator>
	class List_val : public List_ptr<T, Allocator>
	{
	protected:
		typedef typename	Allocator::template rebind<T>::other	allocator_type;
		allocator_type		m_alloc;

		List_val(Allocator A = Allocator())
		: List_ptr<T, Allocator>(A),
		m_alloc(A)
		{}
	};

	template<class T, class Allocator = std::allocator<T> >
	class list : public List_val<T, Allocator>
	{
	protected:
		typedef				unsigned long int								_size_t;
		typedef				List_val<T, Allocator>							Base;
		typedef typename	Base::allocator_type							A;
		typedef typename	List_nod<T, A>::Node							Node;
		typedef typename	A::template rebind<Node>::other::pointer		Node_ptr;
		typedef typename	A::template rebind<Node_ptr>::other::reference	Node_pref;
		typedef typename	A::reference 									Val_ref;

		static Node_pref	_Next(Node_ptr P) { return ((Node_pref)(*P).m_next); }
		static Node_pref	_Prev(Node_ptr P) { return ((Node_pref)(*P).m_prev); }
		static Val_ref		_Value(Node_ptr P) { return ((Val_ref)(*P).m_value); }

	public:
		typedef				A					allocator_type;
		typedef typename	A::size_type		size_type;
		typedef typename	A::difference_type	difference_type;
		typedef				difference_type		Dift;
		typedef typename	A::pointer			pointer;
		typedef				pointer				Tptr;
		typedef typename	A::const_pointer	const_pointer;
		typedef				const_pointer		Ctptr;
		typedef typename	A::reference		reference;
		typedef				reference			Tref;
		typedef typename	A::const_reference	const_reference;
		typedef typename	A::value_type		value_type;

	protected:
		Node_ptr	m_head_ptr;
		size_type	m_size;

	public:
		friend class bidirectional_iterator;
		class bidirectional_iterator : public ft::iterator<bidirectional_iterator_tag, value_type, Dift, Tptr, Tref>
		{
		protected:
			Node_ptr Ptr;
		public:
			typedef typename bidirectional_iterator::iterator_category	iterator_category;
			typedef typename bidirectional_iterator::value_type			value_type;
			typedef typename bidirectional_iterator::difference_type	difference_type;
			typedef typename bidirectional_iterator::pointer			pointer;
			typedef typename bidirectional_iterator::reference			reference;

			bidirectional_iterator()
			: Ptr(0) 
			{}

			bidirectional_iterator(Node_ptr P)
			: Ptr(P)
			{}

			reference	operator*() const { return (_Value(Ptr) ); }
			Tptr		operator->() const { return (&**this); }

			bidirectional_iterator&	operator++()
			{
				Ptr = _Next(Ptr);
				return (*this);
			}

			bidirectional_iterator	operator++(int)
			{
				bidirectional_iterator	Tmp = *this;
				++*this;
				return (Tmp);
			}

			bidirectional_iterator&	operator--()
			{	
				Ptr = _Prev(Ptr);
				return (*this);
			}

			bidirectional_iterator	operator--(int)
			{
				bidirectional_iterator	Tmp = *this;
				--*this;
				return (Tmp);
			}

			bool					operator==(const bidirectional_iterator& X) const { return (Ptr == X.Ptr); }
			bool					operator!=(const bidirectional_iterator& X) const { return (!(*this == X)); }
			Node_ptr				Mynode() const { return (Ptr); }
		};

		friend class const_bidirectional_iterator;
		class	const_bidirectional_iterator : public ft::iterator<bidirectional_iterator_tag, value_type, Dift, Ctptr, const_reference> 
		{
			protected:
				Node_ptr	Ptr;

			public:
			typedef typename	const_bidirectional_iterator::iterator_category	iterator_category;
			typedef typename	const_bidirectional_iterator::value_type		value_type;
			typedef typename	const_bidirectional_iterator::difference_type	difference_type;
			typedef typename	const_bidirectional_iterator::pointer			pointer;
			typedef typename	const_bidirectional_iterator::reference			reference;

			const_bidirectional_iterator()
			: Ptr(0)
			{}

			const_bidirectional_iterator (Node_ptr P)
			: Ptr(P)
			{}

			const_bidirectional_iterator(const typename list<T, Allocator>::iterator& X)
			: Ptr(X.Mynode())
			{}

			const_reference					operator*() const { return (_Value(Ptr)); }
			Ctptr							operator->() const {return (&**this); }

			const_bidirectional_iterator&	operator++()
			{
				Ptr = _Next(Ptr);
				return (*this);
			}

			const_bidirectional_iterator	operator++(int)
			{
				const_bidirectional_iterator	Tmp = *this;
				++*this;
				return (Tmp);
			}

			const_bidirectional_iterator&	operator--()
			{
				Ptr = _Prev(Ptr);
				return (*this);
			}

			const_bidirectional_iterator	operator--(int)
			{
				const_bidirectional_iterator	Tmp = *this;
				--*this;
				return (Tmp);
			}

			bool							operator==(const const_bidirectional_iterator& X) const { return (Ptr == X.Ptr); }
			bool							operator!=(const const_bidirectional_iterator& X) const { return (!(*this == X)); }
			Node_ptr						Mynode() const {return (Ptr); }
		};

		typedef bidirectional_iterator					iterator;
		typedef const_bidirectional_iterator			const_iterator;
		typedef ft::reverse_iterator<const_iterator>	const_reverse_iterator;
		typedef ft::reverse_iterator<iterator>			reverse_iterator;

	public:
		list()
		: Base()
		, m_head_ptr(_buynode())
		, m_size(0)
		{}

		explicit list (const A& Alloc)
		: Base(Alloc)
		, m_head_ptr(_buynode())
		, m_size(0)
		{}
		
		explicit list(size_type N)
		: Base()
		, m_head_ptr(_buynode())
		, m_size(0)
		{
			insert(begin(), N, T());
		}
		
		list(size_type N, const T& V)
		: Base()
		, m_head_ptr(_buynode())
		, m_size(0)
		{
			insert(begin(), N, V);
		}
		
		list(size_type N, const T& V, const A& Alloc)
		: Base(Alloc)
		, m_head_ptr(_buynode())
		, m_size(0)
		{
			insert(begin(), N, V);
		}
		
		list (const list& X)
		: Base(X.m_alloc)
		, m_head_ptr(_buynode())
		, m_size(0)
		{
			insert(begin(), X.begin(), X.end());
		}
		
		template<class It>
		list (It F, It L)
		: Base()
		, m_head_ptr(_buynode())
		, m_size(0)
		{
			_construct(F, L, ft::is_primitive_type<It>());
		}
		
		template<class It>
		list (It F, It L, const A& Alloc)
		: Base(Alloc)
		, m_head_ptr(_buynode())
		, m_size(0) 
		{
			_construct(F, L, ft::is_primitive_type<It>());
		}

		~list()
		{
			erase(begin(), end());
			_freenode(m_head_ptr);
			m_head_ptr = 0;
			m_size = 0;
		}

		list& operator=(const list& X)
		{
			if (this != &X)
			{
				assign(X.begin(), X.end());
			}
			return (*this);
		}

		iterator				begin() { return (iterator(m_head_ptr == 0 ? 0 : _Next(m_head_ptr))); }
		const_iterator			begin() const { return (const_iterator(m_head_ptr == 0 ? 0 : _Next(m_head_ptr))); }
		iterator				end() { return (iterator(m_head_ptr)); }
		const_iterator			end() const { return (const_iterator(m_head_ptr)); }
		reverse_iterator		rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator		rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
		
		void	resize(size_type N) { resize(N, T()); }
		void	resize(size_type N, T X)
		{
			if (size() < N)
			{
				insert(end(), N - size(), X);
			}
			else
			{
				while (N < size())
				{
					pop_back();
				}
			}
		}

		size_type				size() const { return (m_size); }
		size_type				max_size() const { return (this->m_alloc.max_size()); }
		bool					empty() const { return (size() == 0); }
		allocator_type			get_allocator() const { return (this->m_alloc); }
		reference				front() { return (*begin()); }
		const_reference			front() const { return (*begin()); }
		reference				back() { return (*(--end())); }
		const_reference			back() const { return (*(--end())); }
		void					push_front(const T& X) { _insert(begin(), X); } 
		void					pop_front() { erase(begin()); }
		void					push_back(const T& X) { _insert(end(), X); }
		void					pop_back() { erase(--end()); }

		template<class It>
		void assign(It F, It L)
		{
			_assign(F, L, ft::is_primitive_type<It>());
		}
		
		void assign(size_type N, const T& X)
		{	
			T	Tx = X;
			erase(begin(), end());
			insert(begin(), N, Tx);
		}

		iterator insert(iterator P, const T& X)
		{
			_insert(P, X);
			return (--P);
		}

		void insert(iterator P, size_type M, const T& X)
		{
			size_type N = M;
			try
			{
				for(; 0 < M; --M)
				_insert (P, X);
			}
			catch(...)
			{
				for(; M < N; ++M)
				{
					iterator Pm = P;
					erase(--Pm);
				}
				throw;
			}
		}

		template<class It>
		void	insert (iterator P, It F, It L)
		{
			_insert(P, F, L, ft::is_primitive_type<It>());
		}
		
		iterator	erase(iterator P)
		{
			Node_ptr S = (P++).Mynode();
			_Next(_Prev(S)) = _Next(S);
			_Prev(_Next(S)) = _Prev(S);
			this->m_alloc.destroy(&_Value(S));
			_freenode(S);
			--m_size;
			return (P);
		}

		iterator	erase(iterator F, iterator L)
		{
			while (F != L)
			{
				erase(F++);
			}
			return (F);
		}
		
		void	clear() { erase(begin(), end()); }

		void	swap(list& X)
		{
			if (this->m_alloc == X.m_alloc)
			{
				ft::swap(m_head_ptr, X.m_head_ptr);
				ft::swap(m_size, X.m_size);
			}
			else
			{
				iterator P = begin();
				splice(P, X);
				X.splice(X.begin(), *this, P, end());
			}
		}

		void	splice(iterator P, list& X)
		{
			if (this != &X && !X.empty())
			{
				_splice(P, X, X.begin(), X.end(), X.m_size); 
			}
		}
		
		void	splice(iterator P, list& X, iterator F)
		{
			iterator	L = F;
			if (F != X.end() && P != F && P != ++L)
			{
				_splice(P, X, F, L, 1);
			}
		}

		void	splice(iterator P, list& X, iterator F, iterator L)
		{
			if (F != L && P != L)
			{
				size_type	N = 0;
				for(iterator Fs = F; Fs != L; ++Fs, ++N)
				{
					if (Fs == P)
					{
						return;
					}
				}
				_splice(P, X, F, L, N);
			}
		}
				
		void	remove(const T& V)
		{
			iterator L = end();
			for(iterator F = begin(); F != L;)
			{
				if (*F == V)
				{
					erase(F++);
				}
				else
				{
					++F;
				}
			}
		}

		template<class Pr1>
		void	remove_if(Pr1 Pr)
		{
			iterator L = end();
			for(iterator F = begin(); F != L;)
			{
				if (Pr(*F))
				{
					erase(F++);
				}
				else
				{
					++F;
				}
			}
		}

		void	unique()
		{
			iterator F = begin(), L = end();
			if (F != L)
			{
				for(iterator M = F; ++M != L; M = F)
				{
					if (*F == *M)
					{
						erase(M);
					}
					else
					{
						F = M;
					}
				}
			}
		}

		template<class Pr2>
		void	unique(Pr2 Pr)
		{
			iterator F = begin(), L = end();
			if (F != L)
			{
				for(iterator M = F; ++M != L; M = F)
				{
					if (Pr(*F, *M))
					{
						erase(M);
					}
					else
					{
						F = M;
					}
				}
			}
		}

		void	merge(list& X)
		{
			if (&X != this)
			{
				iterator F1 = begin(), L1 = end();
				iterator F2 = X.begin(), L2 = X.end();
				while (F1 != L1 && F2 != L2)
				{
					if (*F2 < *F1)
					{
						iterator Mid2 = F2;
						_splice(F1, X, F2, ++Mid2, 1);
						F2 = Mid2;
					}
					else
					{
						++F1;
					}
				}
				if (F2 != L2)
				{
					_splice(L1, X, F2, L2, X.m_size);
				}
			}
		}
		
		
		template<class Pr3>
		void	merge(list& X, Pr3 Pr)
		{
			if (&X != this)
			{
				iterator F1 = begin(), L1 = end();
				iterator F2 = X.begin(), L2 = X.end();
				while (F1 != L1 && F2 != L2)
				{
					if (Pr (*F2, *F1))
					{
						iterator Mid2 = F2;
						_splice(F1, X, F2, ++Mid2, 1);
						F2 = Mid2;
					}
					else
					{
						++F1;
					}
				}
				if (F2 != L2)
				{
					_splice(L1, X, F2, L2, X.m_size);
				}
			}
		}

		void sort()
		{
			if (2 <= size())
			{
				const _size_t	MAXN = 25;
				list			X(this->m_alloc);
				list			Arr[MAXN + 1];
				_size_t			N = 0;
				while (!empty())
				{
					X.splice(X.begin(), *this, begin());
					_size_t I;
					for(I = 0; I < N && !Arr[I].empty(); ++I)
					{
						Arr[I].merge(X);
						Arr[I].swap(X);
					}
					if (I == MAXN)
					{
						Arr[I - 1].merge(X);
					}
					else
					{
						Arr[I].swap(X);
						if (I == N)
						{
							++N;
						}
					}
				}
				for(_size_t I = 1; I < N; ++I)
				{
					Arr[I].merge(Arr[I - 1]);
				}
				swap(Arr[N - 1]);
			}
		}
		
		template<class Pr3>
		void	sort(Pr3 Pr)
		{
			if (2 <= size())
			{
				const _size_t MAXN = 25;
				list X(this->m_alloc), Arr[MAXN + 1];
				_size_t N = 0;
				while (!empty())
				{
					X.splice (X.begin(), *this, begin());
					_size_t I;
					for(I = 0; I < N && !Arr[I].empty(); ++I)
					{
						Arr[I].merge(X, Pr);
						Arr[I].swap(X);
					}
					if (I == MAXN)
					{
						Arr[I - 1].merge(X, Pr);
					}
					else
					{
						Arr[I].swap(X);
						if (I == N)
						{
							++N;
						}
					}
				}
				for(_size_t I = 1; I < N; ++I)
				{
					Arr[I].merge(Arr[I - 1], Pr);
				}
				swap(Arr[N - 1]); 
			}
		}

		void reverse()
		{
			if (2 <= size())
			{
				iterator L = end();
				for(iterator F = ++begin(); F != L;)
				{
					iterator M = F;
					_splice(begin(), *this, M, ++F, 1);
				}
			}
		}

	protected:
		Node_ptr	_buynode(Node_ptr Narg = 0, Node_ptr Parg = 0)
		{
			Node_ptr	S = this->Alloc_node.allocate(1, (void *)0);
			this->Alloc_ptr.construct(&_Next(S), Narg != 0 ? Narg : S);
			this->Alloc_ptr.construct(&_Prev(S), Parg != 0 ? Parg : S);
			return (S);
		}

		template<class It>
		void	_construct(It F, It L, ft::true_type)
		{
			insert(begin(), (size_type)F, (T) L);
		}
		
		template<class It>
		void	_construct (It F, It L, ft::false_type)
		{
			insert(begin(), F, L);
		}

		void	_freenode(Node_ptr S)
		{
			this->Alloc_ptr.destroy(&_Next(S));
			this->Alloc_ptr.destroy(&_Prev(S));
			this->Alloc_node.deallocate(S, 1);
		}

		template<class It>
		void	_assign(It F, It L, ft::true_type)
		{
			assign ((size_type) F, (T) L);
		}
		
		template<class It>
		void	_assign(It F, It L, ft::false_type)
		{
			erase(begin(), end()); 
			insert(begin(), F, L);
		}

		void	_insert(iterator P, const T& X)
		{
			Node_ptr S = P.Mynode();
			Node_ptr Snew = _buynode(S, _Prev(S));
			_incsize(1);
			try
			{
				this->m_alloc.construct(&_Value(Snew), X);
			}
			catch(...)
			{
				--m_size;
				_freenode(Snew);
				throw;
			}
			_Prev(S) = Snew;
			_Next(_Prev(Snew)) = Snew;
		}

		template<class It>
		void	_insert(iterator P, It F, It L, ft::true_type)
		{
			insert(P, (size_type) F, (T)L);
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
			size_type	N = 0;
			try
			{
				for(; F != L; ++F, ++N)
				{
					_insert(P, *F);
				}
			}
			catch(...)
			{
				for(; 0 < N; --N)
				{
					iterator Pm = P;
					erase(--Pm);
				}
				throw;
			}
		}

		template<class It>
		void	_insert_iter_type(iterator P, It F, It L, forward_iterator_tag)
		{
			It	Fs = F;
			try
			{
				for(; F != L; ++F)
				{
					_insert(P, *F);
				}
			}
			catch(...)
			{
				for(; Fs != F; ++Fs)
				{
					iterator Pm = P;
					erase(--Pm);
				}
				throw;
			}
		}

		void	_splice(iterator P, list& X, iterator F, iterator L, size_type N)
		{
			if (this->m_alloc == X.m_alloc)
			{
				if (this != &X)
				{
					_incsize(N);
					X.m_size -= N;
				}
				_Next(_Prev(F.Mynode())) = L.Mynode();
				_Next(_Prev(L.Mynode())) = P.Mynode();
				_Next(_Prev(P.Mynode())) = F.Mynode();
				Node_ptr S = _Prev(P.Mynode());
				_Prev(P.Mynode()) = _Prev(L.Mynode());
				_Prev(L.Mynode()) =	_Prev(F.Mynode());
				_Prev(F.Mynode()) = S;
			}
			else
			{
				insert (P, F, L);
				X.erase(F, L);
			}
		}

		void	_incsize(size_type N)
		{
			if (max_size() - size() < N)
			{
				throw ft::exception("list<T> too long");
			}
			m_size += N;
		}
	};

template<class T, class A> inline
void	swap(list<T, A>& X, list<T, A>& Y) { X.swap(Y); }

template<class T, class A> inline
bool operator==(const list<T, A>& X, const list<T, A>& Y) { return (X.size() == Y.size() && equal (X.begin(), X.end(), Y. begin())); }

template<class T, class A> inline
bool operator!=(const list<T, A>& X, const list<T, A>& Y) {	return (!(X == Y)); }

template<class T, class A> inline
bool operator<(const list<T, A>& X, const list<T, A>& Y) { return (ft::lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end())); }

template<class T, class A> inline
bool operator>(const list<T, A>& X, const list<T, A>& Y) { return (Y < X); }

template<class T, class A> inline
bool operator<=(const list<T, A>& X, const list<T, A>& Y) { return (!(Y < X)); }

template<class T, class A> inline
bool operator>=(const list<T, A>& X, const list<T, A>& Y) { return (!(X < Y)); }

}
