#pragma once

#include <memory>
#include "xutility.hpp"
#include "algorithm.hpp"
#include "exception.hpp"

namespace ft
{
	template<class T>
	class Tree_nod : public T
	{
	protected:
		typedef typename	T::allocator_type	allocator_type;
		typedef typename	T::key_compare		key_compare;
		typedef typename	T::value_type		value_type;
		
		friend struct Node;
		struct Node
		{
			Node		*_Left;
			Node		*_Right;
			Node		*_Parent;
			value_type	_Value;
			char		_Color;
			char		_Isnil;
		};

		Tree_nod(const key_compare& Parg, allocator_type A)
		: T(Parg)
		, Alloc_node(A)
		{}

		typename allocator_type::template rebind<Node>::other	Alloc_node;
	};

	template<class T>
	class Tree_ptr : public Tree_nod<T>
	{
	protected:
		typedef typename	Tree_nod<T>::Node		Node;
		typedef typename	T::allocator_type		allocator_type;
		typedef typename	T::key_compare			key_compare;

		typedef typename	allocator_type::template rebind<Node>::other::pointer	Node_ptr;
		typename			allocator_type::template rebind<Node_ptr>::other		Alloc_ptr;

		Tree_ptr(const key_compare& Parg, allocator_type A)
		: Tree_nod<T>(Parg, A)
		, Alloc_ptr(A)
		{}
	};

	template<class T>
	class Tree_val : public Tree_ptr<T>
	{
	protected:
		typedef typename	T::allocator_type	allocator_type;
		typedef typename	T::key_compare		key_compare;
		allocator_type		m_alloc;
	
		Tree_val(const key_compare Parg, allocator_type A)
		: Tree_ptr<T>(Parg, A)
		, m_alloc(A)
		{}
	};

	template<class T>
	class Tree : public Tree_val<T>
	{
	public:
		typedef				Tree_val<T>			Base;
		typedef typename	T::key_type			key_type;
		typedef typename	T::key_compare		key_compare;
		typedef typename	T::value_compare	value_compare;
		typedef typename	T::value_type		value_type;
		typedef typename	T::allocator_type	allocator_type;

	protected:
		typedef typename	T::Kfn				Kfn;
		typedef typename	Tree_nod<T>::Node	Node;

		enum Redbl
		{
			Red,
			Black
		};

		typedef typename	allocator_type::template rebind<Node>::other::pointer				Node_ptr;
		typedef typename	allocator_type::template rebind<Node_ptr>::other::reference			Node_pref;
		typedef typename	allocator_type::template rebind<key_type>::other::const_reference	Key_ref;
		typedef typename	allocator_type::template rebind<char>::other::reference				Char_ref;
		typedef typename	allocator_type::template rebind<value_type>::other::reference		Val_ref;

		static Char_ref		_Color(Node_ptr P) { return ((Char_ref)(*P)._Color); }
		static Char_ref		_Isnil(Node_ptr P) { return((Char_ref)(*P)._Isnil); }
		static Key_ref		_Key(Node_ptr P) { return (Kfn()(_Value(P))); }
		static Node_pref	_Left(Node_ptr P) { return((Node_pref)(*P)._Left); }
		static Node_pref	_Right(Node_ptr P) { return ((Node_pref)(*P)._Right); }
		static Node_pref	_Parent(Node_ptr P) { return ((Node_pref)(*P)._Parent); }
		static Val_ref		_Value(Node_ptr P) { return ((Val_ref)(*P)._Value); }

	public:
		typedef typename allocator_type::template rebind<value_type>::other::pointer			pointer;
		typedef typename allocator_type::template rebind<value_type>::other::const_pointer		const_pointer;
		typedef typename allocator_type::template rebind<value_type>::other::reference			reference;
		typedef typename allocator_type::template rebind<value_type>::other::const_reference	const_reference;

		typedef typename	allocator_type::size_type		size_type;
		typedef typename	allocator_type::difference_type	difference_type;
		typedef				difference_type					Dift;
		typedef				pointer							Tptr;
		typedef				const_pointer					Ctptr;
		typedef				reference						Reft;

	protected:
		Node_ptr	m_head;
		size_type	m_size;

	public:
		friend class map_iterator;
		class map_iterator : public ft::iterator<bidirectional_iterator_tag, value_type, Dift, Tptr, Reft>
		{
		protected:
			Node_ptr	Ptr;
		public:
			typedef typename	map_iterator::iterator_category		iterator_category;
			typedef typename	map_iterator::difference_type		difference_type;
			typedef typename	map_iterator::pointer				pointer;
			typedef typename	map_iterator::reference				reference;

			map_iterator()
			: Ptr(0)
			{}

			map_iterator(Node_ptr P)
			: Ptr(P)
			{}

			reference		operator*() const { return (_Value(Ptr)); }
			Tptr			operator->() const { return (&**this); }

			map_iterator&	operator++()
			{
				_inc();
				return (*this);
			}

			map_iterator	operator++(int)
			{
				map_iterator Tmp = *this;
				++*this;
				return (Tmp);
			}

			map_iterator&	operator--()
			{
				_dec();
				return *this;
			}

			map_iterator	operator--(int)
			{
				map_iterator Tmp = *this;
				--*this;
				return (Tmp);
			}

			bool			operator==(const map_iterator& X) const { return (Ptr == X.Ptr); }
			bool			operator!=(const map_iterator& X) const { return (!(*this == X)); }
			Node_ptr		_mynode() const { return (Ptr); }

		private:
			void _dec()
			{
				if (_Isnil(Ptr))
					Ptr = _Right(Ptr);
				else if (!_Isnil(_Left(Ptr)))
					Ptr = _max(_Left(Ptr));
				else
				{
					Node_ptr P;
					while (!_Isnil(P = _Parent(Ptr)) && Ptr == _Left(P))
						Ptr = P;
					if (!_Isnil(P))
						Ptr = P;
				}
			}

			void _inc()
			{
				if (_Isnil(Ptr))
					;
				else if (!_Isnil(_Right(Ptr)))
					Ptr = _min(_Right(Ptr));
				else {
					Node_ptr P;
					while (!_Isnil(P = _Parent(Ptr)) && Ptr == _Right(P))
						Ptr = P;
					Ptr = P;
				}
			}
		};

		friend class const_map_iterator;
		class const_map_iterator : public ft::iterator<bidirectional_iterator_tag, value_type, Dift, Ctptr, const_reference>
		{
		protected:
			Node_ptr	Ptr;

		public:
			typedef typename	const_map_iterator::iterator_category	iterator_category;
			typedef typename	const_map_iterator::difference_type		difference_type;
			typedef typename	const_map_iterator::pointer				pointer;
			typedef typename	const_map_iterator::reference			reference;

			const_map_iterator()
			: Ptr(0)
			{}

			const_map_iterator(Node_ptr P)
			: Ptr(P)
			{}

			const_map_iterator(const typename Tree<T>::iterator& X)
			: Ptr(X._mynode())
			{}

			const_reference		operator*() const { return (_Value(Ptr)); }
			Ctptr				operator->() const { return (&**this); }

			const_map_iterator&	operator++()
			{
				_inc();
				return (*this);
			}

			const_map_iterator	operator++(int)
			{
				const_map_iterator Tmp = *this;
				++*this;
				return (Tmp);
			}

			const_map_iterator& operator--()
			{
				_dec();
				return *this;
			}

			const_map_iterator operator--(int)
			{
				const_map_iterator Tmp = *this;
				--*this;
				return (Tmp);
			}

			bool operator==(const const_map_iterator& X) const { return (Ptr == X.Ptr); }
			bool operator!=(const const_map_iterator& X) const { return (!(*this == X)); }
			Node_ptr _mynode() const { return (Ptr); }

			void _dec()
			{
				if (_Isnil(Ptr))
					Ptr = _Right(Ptr);
				else if (!_Isnil(_Left(Ptr)))
					Ptr = _max(_Left(Ptr));
				else {
					Node_ptr P;
					while (!_Isnil(P = _Parent(Ptr)) && Ptr == _Left(P))
						Ptr = P;
					if (!_Isnil(P))
						Ptr = P;
				}
			}

			void _inc()
			{
				if (_Isnil(Ptr))
					;
				else if (!_Isnil(_Right(Ptr)))
					Ptr = _min(_Right(Ptr));
				else {
					Node_ptr P;
					while (!_Isnil(P = _Parent(Ptr)) && Ptr == _Right(P))
						Ptr = P;
					Ptr = P;
				}
			}
		};

	public:
		typedef	map_iterator								iterator;
		typedef	const_map_iterator							const_iterator;
		typedef	ft::reverse_iterator<const_iterator>		const_reverse_iterator;
		typedef	ft::reverse_iterator<iterator>				reverse_iterator;
		typedef ft::pair<iterator, bool>					Pairib;
		typedef ft::pair<iterator, iterator>				Pairii;
		typedef ft::pair<const_iterator, const_iterator>	Paircc;

		explicit Tree(const key_compare& Parg, const allocator_type& A)
		: Base(Parg, A)
		{
				_init();
		}

		Tree(const value_type *F, const value_type *L, const key_compare& Parg, const allocator_type& A)
		: Base(Parg, A)
		{
			_init();
			insert(F, L);
		}

		Tree(const Tree& X)
		: Base(X.key_comp(), X.get_allocator())
		{
			_init();
			_copy(X);
		}

		~Tree(){
			erase(begin(), end());
			_freenode(m_head);
			m_head = 0, m_size = 0;
		}

		Tree&	operator=(const Tree& X)
		{
			if (this != &X)
			{
				erase(begin(), end());
				this->m_comp = X.m_comp;
				_copy(X);
			}
			return (*this);
		}

		iterator				begin() { return(iterator(_lmost())); }
		const_iterator			begin() const { return(const_iterator(_lmost())); }
		iterator				end() { return (iterator(m_head)); }
		const_iterator			end() const { return (const_iterator(m_head)); }
		reverse_iterator		rbegin() { return (reverse_iterator(end())); }
		const_reverse_iterator	rbegin() const { return (const_reverse_iterator(end())); }
		reverse_iterator		rend() { return (reverse_iterator(begin())); }
		const_reverse_iterator	rend() const { return (const_reverse_iterator(begin())); }
		size_type				size() const { return(m_size); }
		size_type				max_size() const { return (this->Alloc_node.max_size()); }
		bool					empty() const { return(size() == 0); }
		allocator_type			get_allocator() const { return(this->Alloc_node); }
		key_compare				key_comp() const { return (this->m_comp); }
		value_compare			value_comp() const { return (value_compare(key_comp())); }

		Pairib	insert(const value_type& V)
		{
			Node_ptr X = _root();
			Node_ptr Y = m_head;
			bool Addleft = true;
			while(!_Isnil(X))
			{
				Y = X;
				Addleft = this->m_comp(Kfn()(V), _Key(X));
				X = Addleft ? _Left(X) : _Right(X);
			}
			if (T::Multi)
			{
				return (Pairib(_insert(Addleft, Y, V), true));
			}
			else
			{
				iterator P = iterator(Y);
				if(!Addleft)
					;
				else if(P == begin())
					return (Pairib(_insert(true, Y, V), true));
				else
					--P;
				if (this->m_comp(_Key(P._mynode()), Kfn()(V)))
					return(Pairib(_insert(Addleft, Y, V), true));
				else
					return(Pairib(P,false));
			}
		}


		iterator	insert(iterator P, const value_type &V)
		{
			if (size() == 0)
				return (_insert(true, m_head, V));
			else if (P == begin())
			{
				if (this->m_comp(Kfn()(V), _Key(P._mynode())))
					return (_insert(true, P._mynode(), V));
			}
			else if (P == end())
			{
				if (this->m_comp(_Key(_rmost()), Kfn()(V)))
					return(_insert(false, _rmost(), V));
			}
			else {
				iterator Pb = P;
				if (this->m_comp(_Key((--Pb)._mynode()), Kfn()(V)) && this->m_comp(Kfn()(V), _Key(P._mynode())))
				{
					if (_Isnil(_Right(Pb._mynode())))
						return(_insert(false, Pb._mynode(), V));
					else
						return(_insert(true, P._mynode(), V));
				}
			}
			return(insert(V).first);
		}

		template<class It>
		void insert(It F, It L)
		{
			for (; F != L; ++F)
				insert(*F);
		}

		// iterator erase(iterator P)	// iterator erase( - https://en.cppreference.com/w/cpp/container/set/erase
		void erase(iterator P)			// - ISO/IEC 14882
		{
			if (_Isnil(P._mynode()))
				_except_iterator();
			Node_ptr X;
			Node_ptr Xpar;
			Node_ptr Y = (P++)._mynode();
			Node_ptr Z = Y;
			if (_Isnil(_Left(Y)))
				X = _Right(Y);
			else if (_Isnil(_Right(Y)))
				X = _Left(Y);
			else
			{
				Y = _min(_Right(Y));
				X = _Right(Y);
			}
			if (Y == Z)
			{
				Xpar = _Parent(Z);
				if (!_Isnil(X))
					_Parent(X) = Xpar;
				if (_root() == Z)
					_root() = X;
				else if(_Left(Xpar) == Z)
					_Left(Xpar) = X;
				else
					_Right(Xpar) = X;
				if (_lmost() != Z)
					;
				else if (_Isnil(_Right(Z)))
					_lmost() = Xpar;
				else
					_lmost() = _min(X);
				if(_rmost() != Z)
					;
				else if (_Isnil(_Left(Z)))
					_rmost() = Xpar;
				else
					_rmost() = _max(X);
			}
			else
			{
				_Parent(_Left(Z)) = Y;
				_Left(Y) = _Left(Z);
				if(Y == _Right(Z))
					Xpar = Y;
				else{
					Xpar = _Parent(Y);
					if (!_Isnil(X))
						_Parent(X) = Xpar;
					_Left(Xpar) = X;
					_Right(Y) = _Right(Z);
					_Parent(_Right(Z)) = Y;
				}
				if (_root() == Z)
					_root() = Y;
				else if(_Left(_Parent(Z)) == Z)
					_Left(_Parent(Z)) = Y;
				else
					_Right(_Parent(Z)) = Y;
				_Parent(Y) = _Parent(Z);
				ft::swap(_Color(Y), _Color(Z));
			}
			if (_Color(Z) == Black)
			{
				for (;X != _root() && _Color(X) == Black; Xpar = _Parent(X))
					if (X == _Left(Xpar)){
						Node_ptr W = _Right(Xpar);
						if(_Color(W) == Red)
						{
							_Color(W) = Black;
							_Color(Xpar) = Red;
							_lrotate(Xpar);
							W = _Right(Xpar);
						}
						if (_Isnil(W))
							X = Xpar;
						else if (_Color(_Left(W)) == Black && _Color(_Right(W)) == Black)
						{
							_Color(W) = Red;
							X = Xpar;
						}
						else {
							if (_Color(_Right(W)) == Black)
							{
								_Color(_Left(W)) = Black;
								_Color(W) = Red;
								_rrotate(W);
								W = _Right(Xpar);
							}
							_Color(W) = _Color(Xpar);
							_Color(Xpar) = Black;
							_Color(_Right(W)) = Black;
							_lrotate(Xpar);
							break;
						}
					}
					else {
						Node_ptr W = _Left(Xpar);
						if(_Color(W) == Red)
						{
							_Color(W) = Black;
							_Color(Xpar) = Red;
							_rrotate(Xpar);
							W = _Left(Xpar);
						}
						if (_Isnil(W))
							X = Xpar;
						else if(_Color(_Right(W)) == Black && _Color(_Left(W)) == Black)
						{
							_Color(W) = Red;
							X = Xpar;
						}
						else
						{
							if(_Color(_Left(W)) == Black)
							{
								_Color(_Right(W)) = Black;
								_Color(W) = Red;
								_lrotate(W);
								W = _Left(Xpar);
							}
							_Color(W) = _Color(Xpar);
							_Color(Xpar) = Black;
							_Color(_Left(W)) = Black;
							_rrotate(Xpar);
							break;
						}
					}
				_Color(X) = Black;
			}
			_destval(&_Value(Z));
			_freenode(Z);
			if(0 < m_size)
				--m_size;
			// return (P);	// - ISO/IEC 14882
		}

		// iterator	erase(iterator F, iterator L) // - https://en.cppreference.com/w/cpp/container/set/erase
		void	erase(iterator F, iterator L)	// - ISO/IEC 14882
			{
			if (size() == 0 || F != begin() || L != end())
			{
				while (F != L)
					erase(F++);
				// return (F);	// - ISO/IEC 14882
			}
			else
			{
				_erase(_root());
				_root() = m_head;
				m_size = 0;
				_lmost() = m_head;
				_rmost() = m_head;
				// return (begin());	// - ISO/IEC 14882
			}
		}

		size_type	erase(const key_type& X)
		{
			Pairii P = equal_range(X);
			size_type N = 0;
			N = ft::distance(P.first, P.second);
			erase(P.first, P.second);
			return (N);
		}

		void erase(const key_type *F, const key_type *L)
		{
			while (F != L)
				erase(*F++);
		}

		void clear() { erase(begin(), end()); }

		iterator find(const key_type& Kv)
		{
			iterator P = lower_bound(Kv);
			return (P == end() || this->m_comp(Kv, _Key(P._mynode())) ? end() : P);
		}

		const_iterator find(const key_type& Kv) const
		{
			const_iterator P = lower_bound(Kv);
			return (P == end() || this->m_comp(Kv, _Key(P._mynode())) ? end() : P);
		}

		size_type count(const key_type& Kv) const
		{
			Paircc Ans = equal_range(Kv);
			size_type N = 0;
			N = ft::distance(Ans.first, Ans.second);
			return (N);
		}

		iterator		lower_bound(const key_type&Kv) { return (iterator(_lbound(Kv))); }
		const_iterator	lower_bound(const key_type& Kv) const { return(const_iterator(_lbound(Kv))); }
		iterator		upper_bound(const key_type& Kv) { return (iterator(_ubound(Kv))); }
		const_iterator	upper_bound(const key_type&Kv) const { return (const_iterator(_ubound(Kv))); }
		Pairii			equal_range(const key_type& Kv) { return (Pairii(lower_bound(Kv), upper_bound(Kv))); }
		Paircc			equal_range(const key_type& Kv) const { return (Paircc(lower_bound(Kv), upper_bound(Kv))); }

		void swap(Tree& X)
		{
			if(get_allocator() == X.get_allocator())
			{
				ft::swap(this->m_comp, X.m_comp);
				ft::swap(m_head, X.m_head);
				ft::swap(m_size, X.m_size);
			}
			else
			{
				Tree Ts = *this;
				*this = X;
				X = Ts;
			}
		}

	protected:
		void	_except_iterator() const
		{
			throw ft::exception("map/set<T> iterator");
		}

		void	_except_long() const
		{
			throw ft::exception("tree mao/set too long");
		}

		void	_copy(const Tree& X)
		{
			_root() = _copy(X._root(), m_head);
			m_size = X.size();
			if (!_Isnil(_root()))
			{
				_lmost() = _min(_root());
				_rmost() = _max(_root());
			}
			else
			{
				_lmost() = m_head;
				_rmost() = m_head;
			}
		}

		Node_ptr	_copy(Node_ptr X, Node_ptr P)
		{
			Node_ptr R = m_head;
			if (!_Isnil(X))
			{
				Node_ptr Y = _buynode(P, _Color(X));
				try
				{
					_consval(&_Value(Y), _Value(X));
				}
				catch (...)
				{
					_freenode(Y);
					_erase(R);
					throw;
				}
				_Left(Y) = m_head;
				_Right(Y) = m_head;
				if (_Isnil(R))
				{
					R = Y;
				}
				try
				{
					_Left(Y) = _copy(_Left(X), Y);
					_Right(Y) = _copy(_Right(X), Y);
				}
				catch (...)
				{
					_erase(R);
					throw;
				}
			}
			return (R);
		}

		void	_erase(Node_ptr X)
		{
			for(Node_ptr Y = X; !_Isnil(Y); X = Y)
			{
				_erase(_Right(Y));
				Y = _Left(Y);
				_destval(&_Value(X));
				_freenode(X);
			}
		}

		void	_init()
		{
			m_head = _buynode(0, Black);
			_Isnil(m_head) = true;
			_root() = m_head;
			_lmost() = m_head;
			_rmost() = m_head;
			m_size = 0;
		}

		iterator	_insert(bool Addleft, Node_ptr Y, const value_type& V)
		{
			if (max_size() - 1 <= m_size)
				_except_long();
			Node_ptr Z = _buynode(Y, Red);
			_Left(Z) = m_head;
			_Right(Z) = m_head;
			try
			{
				_consval(&_Value(Z), V);
			}
			catch(...)
			{
				_freenode(Z);
				throw;
			}
			++m_size;
			if (Y == m_head)
			{
				_root() = Z;
				_lmost() = Z;
				_rmost() = Z;
			}
			else if (Addleft)
			{
				_Left(Y) = Z;
				if (Y == _lmost())
					_lmost() = Z;
			}
			else
			{
				_Right(Y) = Z;
				if (Y == _rmost())
					_rmost () = Z;
			}
			for (Node_ptr X = Z; _Color(_Parent(X)) == Red;)
			{
				if (_Parent(X) == _Left(_Parent(_Parent(X))))
				{
					Y = _Right(_Parent(_Parent(X)));
					if (_Color(Y) == Red)
					{
						_Color(_Parent(X)) = Black;
						_Color(Y) = Black;
						_Color(_Parent(_Parent(X))) = Red;
						X= _Parent(_Parent(X));
					}
					else
					{
						if ( X == _Right(_Parent(X)))
						{
							X = _Parent(X);
							_lrotate(X);
						}
						_Color(_Parent(X)) = Black;
						_Color(_Parent(_Parent(X))) = Red;
						_rrotate(_Parent(_Parent(X)));
					}
				}
				else
				{
					Y = _Left(_Parent(_Parent(X)));
					if (_Color(Y) == Red)
					{
						_Color(_Parent(X)) = Black;
						_Color(Y) = Black;
						_Color(_Parent(_Parent(X))) = Red;
						X = _Parent(_Parent(X));
					}
					else {
						if (X == _Left(_Parent(X)))
						{
							X = _Parent(X);
							_rrotate(X);
						}
						_Color(_Parent(X)) = Black;
						_Color(_Parent(_Parent(X))) = Red;
						_lrotate(_Parent(_Parent(X)));
					}
				}
			}
			_Color(_root()) = Black;
			return (iterator(Z));
		}

		Node_ptr	_lbound(const key_type& Kv) const
		{
			Node_ptr X = _root();
			Node_ptr Y = m_head;
			while (!(_Isnil(X)))
			{
				if (this->m_comp(_Key(X), Kv))
					X =_Right(X);
				else
				{
					Y = X;
					X = _Left(X);
				}
			}
			return(Y);
		}

		Node_ptr&	_lmost() { return (_Left(m_head)); }
		Node_ptr&	_lmost() const { return (_Left(m_head)); }

		void	_lrotate(Node_ptr X)
		{
			Node_ptr Y = _Right(X);
			_Right(X) = _Left(Y);
			if (!_Isnil(_Left(Y)))
				_Parent(_Left(Y)) = X;
			_Parent(Y) = _Parent(X);
			if (X == _root())
				_root() = Y;
			else if (X == _Left(_Parent(X)))
				_Left(_Parent(X)) = Y;
			else
				_Right(_Parent(X)) = Y;
			_Left(Y) = X;
			_Parent(X) = Y;
		}

		static	Node_ptr _max(Node_ptr P)
		{
			while (!_Isnil(_Right(P)))
				P = _Right(P);
			return (P);
		}

		static Node_ptr	_min(Node_ptr P)
		{
			while (!_Isnil(_Left(P)))
				P = _Left(P);
			return (P);
		}

		Node_ptr&	_rmost() { return (_Right(m_head)); }
		Node_ptr&	_rmost() const { return (_Right(m_head)); }
		Node_ptr&	_root() { return (_Parent(m_head)); }
		Node_ptr&	_root() const { return (_Parent(m_head)); }

		void _rrotate(Node_ptr X)
		{
			Node_ptr Y = _Left(X);
			_Left(X) = _Right(Y);
			if (!_Isnil(_Right(Y)))
				_Parent(_Right(Y)) = X;
			_Parent(Y) = _Parent(X);
			if (X == _root())
				_root() = Y;
			else if (X == _Right(_Parent(X)))
				_Right(_Parent(X)) = Y;
			else
				_Left(_Parent(X)) = Y;
			_Right(Y) = X;
			_Parent(X) = Y;
		}

		Node_ptr	_ubound(const key_type& Kv) const
		{
			Node_ptr X = _root();
			Node_ptr Y = m_head;
			while(!_Isnil(X))
			{
				if (this->m_comp(Kv, _Key(X)))
				{
					Y= X;
					X = _Left(X);
				}
				else
					X = _Right(X);
			}
			return (Y);
		}

		Node_ptr	_buynode(Node_ptr Parg, char Carg)
		{
			Node_ptr S = this->Alloc_node.allocate(1, (void *)0);
			this->Alloc_ptr.construct(&_Left(S), Node_ptr());
			this->Alloc_ptr.construct(&_Right(S), Node_ptr());
			this->Alloc_ptr.construct(&_Parent(S), Parg);
			_Color(S) = Carg;
			_Isnil(S) = false;
			return (S);
		}

		void	_consval(Tptr P, const value_type& V) { this->m_alloc.construct(P, V); }
		void	_destval(Tptr P) { this->m_alloc.destroy(P); }

		void	_freenode(Node_ptr S)
		{
			this->Alloc_ptr.destroy(&_Parent(S));
			this->Alloc_ptr.destroy(&_Right(S));
			this->Alloc_ptr.destroy(&_Left(S));
			this->Alloc_node.deallocate(S, 1);
		}

	};

	template<class T>
	inline void	swap(Tree<T>& X, Tree<T>& Y) { X.swap(Y); }

	template<class T>
	inline bool	operator==(const Tree<T>& X, const Tree<T>& Y) { return (X.size() == Y.size() && ft::equal(X.begin(), X.end(), Y.begin())); }

	template<class T>
	inline bool	operator!=(const Tree<T>& X, const Tree<T>& Y) { return (!(X == Y)); }

	template<class T>
	inline bool	operator<(const Tree<T>& X, const Tree<T>& Y) { return (ft::lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end())); }

	template<class T>
	inline bool	operator>(const Tree<T>& X, const Tree<T>& Y) { return (Y < X); }

	template<class T>
	inline bool	operator<=(const Tree<T>& X, const Tree<T>& Y) { return (!(Y < X)); }

	template<class T>
	inline bool	operator>=(const Tree<T>& X, const Tree<T>& Y) { return (!(X < Y)); }

}
