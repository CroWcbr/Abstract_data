#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "../utility/exception.hpp"
#include "../utility/xutility.hpp"
#include "../utility/algorithm.hpp"

namespace ft
{
/*
Template class for the nodes in the Fibonacci Heap.

This class defines the structure for the nodes used in the Fibonacci Heap.
Each node contains various attributes for maintaining the heap structure.
 
T - type of data stored in the nodes.
Allocator - type of allocator used for memory management.
*/

	template<class T, class Allocator> 
	class Fibo_nod
	{ // base class for Fibo_ptr to hold allocator Alloc_node
	protected:

		typedef		T	value_type;

		friend struct Node;
		struct Node
		{ // fibonacci_heap node
			Fibo_nod*	m_parent; 
			Fibo_nod*	m_left; 
			Fibo_nod*	m_right;
			Fibo_nod*	m_child; 
			value_type	m_value; 
			int			m_degree;
			bool		m_marked;
		};

		Fibo_nod(Allocator A)
		: Alloc_node(A)
		{}

		typename	Allocator::template rebind<Node>::other	Alloc_node;
	};


	template<class T, class Allocator>
	class Fibo_ptr : public Fibo_nod<T, Allocator>
	{ // base class for Fibo_val to hold allocator Alloc_ptr
	protected:
		typedef typename	Fibo_nod<T, Allocator>::Node						Node;
		typedef typename	Allocator::template rebind<Node>::other::pointer	Node_ptr;
		typename			Allocator::template rebind<Node_ptr>::other			Alloc_ptr;

		Fibo_ptr(Allocator A)
		: Fibo_nod<T, Allocator>(A)
		, Alloc_ptr(A)
		{}
	};

	template<class T, class Allocator>
	class Fibo_val : public Fibo_ptr<T, Allocator>
	{ // base class for fibonacci_heap to hold allocator m_alloc
	protected:
		typedef typename	Allocator::template rebind<T>::other	allocator_type;
		allocator_type		m_alloc;

		Fibo_val(Allocator A = Allocator())
		: Fibo_ptr<T, Allocator>(A)
		, m_alloc(A)
		{}
	};

/**
A Fibonacci Heap implementation.

This class provides an implementation of the Fibonacci Heap data structure.
It supports operations like
	insertion,
	merging, 
	removal of minimum element,
	decreasing key value,
	and finding elements.

Allows for duplicates

T - type of data stored in the heap.
Pr - type of comparison function for ordering elements.
Allocator - type of allocator used for memory management.
 */
	template<class T, class Pr = ft::less<T>, class Allocator = std::allocator<T> >
	class fibonacci_heap : public Fibo_val<T, Allocator>
	{
	protected:
		typedef				unsigned long int								_size_t;
		typedef				Fibo_val<T, Allocator>							Base;
		typedef				Pr												key_compare;
		typedef typename	Base::allocator_type							A;
		typedef typename	Fibo_nod<T, A>::Node							Node;
	public:
		typedef typename	A::template rebind<Node>::other::pointer		Node_ptr;
	protected:
		typedef typename	A::template rebind<Node_ptr>::other::reference	Node_pref;
		typedef typename	A::reference 									Val_ref;

		typedef				A					allocator_type;
		typedef typename	A::size_type		size_type;
		typedef typename	A::difference_type	difference_type;
		typedef typename	A::pointer			pointer;
		typedef typename	A::const_pointer	const_pointer;
		typedef typename	A::reference		reference;
		typedef typename	A::const_reference	const_reference;
		typedef typename	A::value_type		value_type;

	protected:
		typedef typename	allocator_type::template rebind<int>::other::reference				Int_ref;
		typedef typename	allocator_type::template rebind<bool>::other::reference				Bool_ref;

		static Node_pref	_Parent(Node_ptr P) { return ((Node_pref)(*P).m_parent); }
		static Node_pref	_Left(Node_ptr P) { return ((Node_pref)(*P).m_left); }
		static Node_pref	_Right(Node_ptr P) { return ((Node_pref)(*P).m_right); }
		static Node_pref	_Child(Node_ptr P) { return ((Node_pref)(*P).m_child); }
		static Val_ref		_Value(Node_ptr P) { return ((Val_ref)(*P).m_value); }
		static Int_ref		_Degree(Node_ptr P) { return ((Int_ref)(*P).m_degree); }
		static Bool_ref		_Marked(Node_ptr P) { return((Bool_ref)(*P).m_marked);}

	protected:
 // m_root node, always on top level
		Node_ptr		m_root;
// size if fibocci heap
		_size_t			m_size;
// comparison operator
		key_compare		m_comp;

	public:
// Constructors/Destructor
/*
INPUT:
	const key_compare& Parg - comparison functor
	const allocator_type& Al - allocator functor
BEHAVIOR:
	Generates an empty fibonacci heap.
*/
		fibonacci_heap()
		: Base()
		, m_root(0)
		, m_size(0)
		, m_comp(key_compare())
		{}

		fibonacci_heap(const key_compare& Parg)
		: Base()
		, m_root(0)
		, m_size(0)
		, m_comp(Parg)
		{}

		fibonacci_heap(const key_compare& Parg, const allocator_type& Al)
		: Base(Al)
		, m_root(0)
		, m_size(0)
		, m_comp(Parg)
		{}

/*
INPUT:
	InputIterator first - first input iterator
	InputIterator last - last input iterator
	const key_compare& Parg - comparison functor
	const allocator_type& Al - allocator functor
BEHAVIOR:
	Generates a fibonacci heap filled with the input elements.
*/
		template<class It>
		fibonacci_heap(It F, It L)
		: Base()
		, m_root(0)
		, m_size(0)
		, m_comp(key_compare())
		{
			insert(F, L);
		}

		template<class It>
		fibonacci_heap(It F, It L, const key_compare& Parg)
		: Base()
		, m_root(0)
		, m_size(0)
		, m_comp(Parg)
		{
			insert(F, L);
		}

		template<class It>
		fibonacci_heap(It F, It L, const key_compare& Parg, const allocator_type& Al)
		: Base(Al)
		, m_root(0)
		, m_size(0)
		, m_comp(Parg)
		{
			insert(F, L);
		}

/*
INPUT:
	fibonacci_heap - deep copy of other fibonacci heap
BEHAVIOR:
	Generates a fibonacci heap filled with data of another fibonacci heap.
*/
		fibonacci_heap(const fibonacci_heap& X)
		: Base(X.m_alloc)
		, m_root(0)
		, m_size(0)
		, m_comp(X.m_comp)
		{
			*this = X;
		}

/*
BEHAVIOR:
	Clear fibonacci heap.
*/
		~fibonacci_heap()
		{
			_clear_all();
		}

/*
INPUT:
	fibonacci_heap - deep copy of other fibonacci heap
BEHAVIOR:
	Generates a fibonacci heap filled with data of another fibonacci heap.
RETURN:
	*this
*/
		fibonacci_heap& operator=(const fibonacci_heap& other)
		{
			if(this == &other)
				return *this;
			_clear_all();
			if (other.empty())
				return *this;

			m_size = other.size();
			m_comp = other.m_comp;

			m_root = _deep_copy(other.root(), other.root(), 0, 0, 0, 0);
			return *this;
		}

/*
RETURN:
	Whether empty
*/
		bool			empty() const { return m_root == 0; }
/*
RETURN:
	size of fibonacci heap
*/
		size_type		size() const { return m_size; }
/*
RETURN:
	pointer to root node
*/
		Node_ptr		root() const { return m_root; }
/*
PRECONDITION:
	!empty()
RETURN:
	value of root node
*/
		value_type&		top() const { return _Value(m_root); }
/*
RETURN:
	allocator type
*/
		allocator_type	get_allocator() const { return (this->m_alloc); }
/*
RETURN:
	max size of fibonacci heap
*/
		size_type		max_size() const { return (this->Alloc_node.max_size()); }
/*
RETURN:
	comparison functor
*/
		key_compare		key_comp() const { return (this->m_comp); }

/*
INPUT:
	Vallue to insert
RETURN:
	pointer to inserted node
*/
		Node_ptr	insert(const value_type& V)
		{
			Node_ptr tmp = _create_node(V);
			m_root = _merge(m_root, tmp);
			m_size++;
			return tmp;
		}
/*
INPUT:
	InputIterator first - first input iterator
	InputIterator last - last input iterator
BEHAVIOR:
	Added to fibonacci heap data from InputIterator.
*/
		template<class It>
		void		insert(It F, It L)
		{
			for (; F != L; ++F)
				insert(*F);
		}

/*
INPUT:
	another fibonacci heap
BEHAVIOR:
	Merge two fibonacci heap
*/
		void		merge(fibonacci_heap& X)
		{
			if (this == &X)
				return;
			m_root = _merge(m_root, X.root());
			m_size += X.size();
			X.m_root = NULL;
			X.m_size = 0;
		}

/*
BEHAVIOR:
	Delete root element and update root
RETURN:
	Value of deleting element
*/
		value_type	remove_min()
		{
			if (empty())
				_empty_error();
			Node_ptr old_root = m_root;
			m_root = _remove_min(m_root);
			value_type tmp = _Value(old_root);
			this->Alloc_node.deallocate(old_root, 1);
			m_size--;
			return tmp;
		}

/*
INPUT:
	pointer to node which will be changed
	new value of this node
BEHAVIOR:
	Change value of node and reconstruct fibonacci heap
*/
		void		decreaseKey(const Node_ptr node, const value_type& V)
		{
			m_root = _decreaseKey(m_root, node, V);
		}

/*
INPUT:
	Value to find
RETURN:
	pointer to finding value
*/
		Node_ptr	find(const value_type& V)
		{
			return _find(m_root, V);
		}

/*
INPUT:
	fibonacci heap
RETURN:
	change pointer of fibonacci heap
*/
		void		swap(fibonacci_heap& X)
		{
			if (this->m_alloc == X.m_alloc)
			{
				ft::swap(m_root, X.m_root);
				ft::swap(m_size, X.m_size);
				ft::swap(m_comp, X.m_comp);
			}
			else 
			{
				fibonacci_heap Ts = *this;
				*this = X;
				X = Ts;
			}
		}

/*
BEHAVIOR:
	draw the fibonacci heap
*/
		void		display() const
		{
			if (empty())
			{
				std::cout << "The Heap is Empty" << std::endl;
				return;
			}
			std::cout << "fibonacci_heap size " << size() << " and root " << top() << std::endl;
			_display(m_root, "");
			std::cout << std::endl;
		}

	private:
// throw exception
		void		_empty_error() const
		{
			throw ft::exception("Fibonacci heap_empty");
		}

// create node with value
		Node_ptr	_create_node(const value_type& V)
		{
			Node_ptr S = this->Alloc_node.allocate(1, (void *)0);
			this->Alloc_ptr.construct(&_Parent(S), Node_ptr());
			this->Alloc_ptr.construct(&_Left(S), S);
			this->Alloc_ptr.construct(&_Right(S), S);
			this->Alloc_ptr.construct(&_Child(S), Node_ptr());
			this->m_alloc.construct(&_Value(S), V);
			_Degree(S) = 0;
			_Marked(S) = false;

			return S;
		}

// clear fibonacci heap
		void		_clear_all()
		{
			_clear(m_root, m_root);
			m_root = 0;
			m_size = 0;
		}

// recursive clear memory
		void		_clear(const Node_ptr current, const Node_ptr base)
		{
			if (current == NULL)
				return;
			
			if (_Child(current) != NULL)
				_clear(_Child(current), _Child(current));
			if (_Right(current) != base)
				_clear(_Right(current), base);

			this->Alloc_node.deallocate(current, 1);
		}

// debug - print adress and value
		void		_display_debug(Node_ptr R, std::string pre) const
		{
			std::string	pc = "│  ";
			Node_ptr	tmp = R;
			do 
			{
				if (_Right(tmp) != R)
				{
					std::cout << pre << "├─";
				}
				else
				{
					std::cout << pre << "└─";
					pc = "   ";
				}
				if (_Child(tmp) == NULL)
				{
					std::cout << "─" << tmp << "\t" << _Value(tmp) << std::endl;
				}
				else
				{
					std::cout << "┐" << tmp << "\t" << _Value(tmp) << std::endl;
					_display(_Child(tmp), pre + pc);
				}
				tmp = _Right(tmp);
			} while (tmp != R);
		}

// for demonstration - print value
		void		_display(Node_ptr R, std::string pre) const
		{
			std::string	pc = "│  ";
			Node_ptr	tmp = R;
			do 
			{
				if (_Right(tmp) != R)
				{
					std::cout << pre << "├─";
				}
				else
				{
					std::cout << pre << "└─";
					pc = "   ";
				}
				if (_Child(tmp) == NULL)
				{
					std::cout << "─" << _Value(tmp) << std::endl;
				}
				else
				{
					std::cout << "┐" << _Value(tmp) << std::endl;
					_display(_Child(tmp), pre + pc);
				}
				tmp = _Right(tmp);
			} while (tmp != R);
		}

// merge two fibonacci heap
		Node_ptr	_merge(Node_ptr first, Node_ptr second)
		{
			if (first == 0)
				return second;
			if (second == 0)
				return first;

			if (m_comp(_Value(second), _Value(first)))
			{
				Node_ptr tmp = first;
				first = second;
				second = tmp;
			}

			Node_ptr first_right = _Right(first);
			Node_ptr second_left = _Left(second);
			_Right(first) = second;
			_Left(second) = first;
			_Left(first_right) = second_left;
			_Right(second_left) =first_right;
			return first;
		}

// remove element
		Node_ptr	_remove_min(Node_ptr node)
		{
			Node_ptr	tmp = _Child(node);
			if(tmp != 0)
			{
				do{
					_Marked(tmp) = false;
					_Parent(tmp) = 0;
					tmp = _Right(tmp);
				}while(tmp != _Child(node));
			}

			if(_Right(node) == node)
			{
				node = _Child(node);
			}
			else
			{
				Node_ptr R = _Right(node);
				Node_ptr L = _Left(node);
				_Left(R) = L;
				_Right(L) = R;
				node = _merge(_Right(node), _Child(node));
			}

			if(node == 0)
				return node;

			_size_t		_max_degree = 0;
			tmp = node;
			do{
				if (_Degree(tmp) > _max_degree)
					_max_degree = _Degree(tmp);
				tmp = _Right(tmp);
			}while(tmp != node);

			return _consolidate(node, _max_degree);
		}

// reconstruct fibonacci heap after deleting element
		Node_ptr	_consolidate(Node_ptr node, _size_t _max_degree)
		{
			Node_ptr	trees[64] = {NULL};
			while(true)
			{
				if(trees[_Degree(node)] != 0)
				{
					Node_ptr tmp = trees[_Degree(node)];
					if(tmp == node)
						break;
					trees[_Degree(node)] = 0;
					Node_ptr tmp_left = _Left(tmp);
					Node_ptr tmp_right = _Right(tmp);
					_Right(tmp_left) = tmp_right;
					_Left(tmp_right) = tmp_left;
					if(m_comp(_Value(node), _Value(tmp)))
					{
						_add_child(node, tmp);
					}
					else
					{
						if(_Right(node) == node)
						{
							_Right(tmp) = tmp;
							_Left(tmp) = tmp;
						}
						else
						{
							Node_ptr node_left = _Left(node);
							Node_ptr node_right = _Right(node);
							_Right(node_left) = tmp;
							_Left(node_right) = tmp;
							_Right(tmp) = node_right;
							_Left(tmp) = node_left;
						}
						_add_child(tmp, node);
						node = tmp;
					}
					continue;
				}
				else
				{
					trees[_Degree(node)] = node;
				}
				node = _Right(node);
			}
			Node_ptr	new_root = node;
			Node_ptr	tmp = node;
			do {
				if(m_comp(_Value(node), _Value(new_root)))
					new_root = node;
				node = _Right(node);
			} while(node != tmp);
			return new_root;
		}

// add child
		void		_add_child(Node_ptr parent, Node_ptr child)
		{
			_Left(child) = child;
			_Right(child) = child;
			_Parent(child) = parent;
			++(_Degree(parent));
			_Child(parent) = _merge(_Child(parent), child);
		}

// cut node
		Node_ptr	_cut(Node_ptr root, Node_ptr node)
		{
			if(_Right(node) == node)
			{
				_Child(_Parent(node)) = 0;
			}
			else
			{
				Node_ptr tmp_right = _Right(node);
				Node_ptr tmp_left = _Left(node);
				_Left(tmp_right) = tmp_left;
				_Right(tmp_left) = tmp_right;
				_Child(_Parent(node)) = tmp_right;
			}
			_Right(node) = node;
			_Left(node) = node;
			_Marked(node) = false;
			--(_Degree(_Parent(node)));
			return _merge(root, node);
		}

// change value and reconstructed fibonacci heap
		Node_ptr	_decreaseKey(Node_ptr root, Node_ptr node, const value_type& V)
		{
			if (m_comp(_Value(node), V))
				return root;
			_Value(node) = V;
			Node_ptr parent = _Parent(node);
			if(parent != 0 && m_comp(_Value(node), _Value(parent)))
			{
				root = _cut(root, node);
				_Parent(node) = 0;
				while(parent != 0 && _Marked(parent))
				{
					root = _cut(root, parent);
					node = parent;
					parent = _Parent(node);
					_Parent(node) = 0;
				}
				if(parent != 0 && _Parent(parent) != 0)
					_Marked(parent) = true;
				if (m_comp(_Value(node), _Value(root)))
					root = node;
			}
			return root;
		}

// find element
		Node_ptr	_find(const Node_ptr node, const value_type& V)
		{
			Node_ptr tmp = node;
			if(tmp == 0)
				return 0;
			do{
				if(_Value(tmp) == V)
					return tmp;
				Node_ptr ret = _find(_Child(tmp), V);
				if (ret)
					return ret;
				tmp = _Right(tmp);
			}while(tmp != node);
			return NULL;
		}

// make a deep copy of another fibonacci heap
		Node_ptr _deep_copy(const Node_ptr current, const Node_ptr base, Node_ptr newParent, Node_ptr newLeft, Node_ptr newRight, Node_ptr newBase)
		{
			if (current == NULL)
				return Node_ptr();

			Node_ptr newNode  = this->Alloc_node.allocate(1, (void *)0);
			this->Alloc_ptr.construct(&_Parent(newNode), newParent);
			this->Alloc_ptr.construct(&_Left(newNode), newLeft ? newLeft : newNode);
			this->Alloc_ptr.construct(&_Right(newNode), newNode);
			this->Alloc_ptr.construct(&_Child(newNode), Node_ptr());
			this->m_alloc.construct(&_Value(newNode), _Value(current));
			_Degree(newNode) = _Degree(current);
			_Marked(newNode) = _Marked(current);

			if (!newBase)
			{
				newBase = newNode;
			}

			if (_Child(current) != NULL)
			{
				_Child(newNode) = _deep_copy(_Child(current), _Child(current), newNode, 0, 0, 0);
			}

			if (_Right(current) != base)
			{
				_Right(newNode) = _deep_copy(_Right(current), base, 0, newNode, newNode, newBase);
			}
			else
			{
				_Right(newNode) = newBase;
				_Left(newBase) = newNode;
			}
			return (newNode);
		}
	};

// swap two fibonacci heap
template<class T, class Pr, class A> inline
void	swap(fibonacci_heap<T, Pr, A>& X, fibonacci_heap<T, Pr, A>& Y) { X.swap(Y); }

}
