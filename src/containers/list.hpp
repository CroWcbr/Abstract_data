// #pragma once

// #include <memory>
// #include "../utils/exception.hpp"
// #include "../iterators/xutility.hpp"
// // #include "../iterators/algorithm.hpp"

// namespace ft
// {

// 	template<class Т, class Allocator>
// 	class List_nod
// 	{
// 	protected:
// 		typedef typename Allocator::template rebind<void>::other::pointer Genptr;
		
// 		struct Node;
// 		friend struct Node;
// 		struct Node
// 		{
// 			Genptr	m_next;
// 			Genptr	m_prev;
// 			T		m_value;
// 		};

// 		List_nod(Allocator A)
// 		: Al_node(A)
// 		{}

// 		typename Allocator::template rebind<Node>::other Al_node;
// 	};

// 	template<class T, class Allocator>
// 	class List_ptr : public List_nod<Ty, Allocator>
// 	{
// 	protected:
// 		typedef typename List_nod<T, Allocator>::Node Node;
// 		typedef typename Allocator::template rebind<Node>::other::pointer Nodeptr;

// 		List_ptr(Allocator A)
// 		: List_nod<T, Allocator>(A)
// 		, Al_ptr(A)
// 		{}
		
// 		typename Allocator::template rebind<Nodeptr>::other Al_ptr; 
// 	};

// 	template<class T, class Allocator>
// 	class List_val : public List_ptr<T, Allocator>
// 	{
// 	protected:
// 		List_val(Allocator A = Allocator())
// 		: List_ptr<T, Allocator>(A)
// 		, m_alloc(A)
// 		{}
		
// 		typedef typename A::template rebind<Ty>::other Al_val;

// 		Al_val m_alloc;
// 	};

// 	template<class T, class Allocator = std::allocator<T> >
// 	class list : public List_val<T, Allocator>
// 	{
// 	public:
// 		typedef				List_val<T, Allocator>	Base;
// 		typedef typename	Base::Al_val				A;
	
// 	protected:
// 		typedef typename	List_nod<T, Allocator>::Genptr				Genptr;
// 		typedef typename	List_nod<T, Allocator>::Node				Node;
// 		typedef typename	A::template rebind::<Node>::other::pointer	Nodeptr;
		
// 		struct Ace;
// 		friend struct Ace;
// 		struct Ace
// 		{
// 			typedef typename	A::template rebind::<Nodeptr>::other::reference Nodepref;
// 			typedef typename	A::reference	Vref;

// 			static	Nodepref	Next(Nodeptr P) {return ((Nodepref)(*P).m_next); }
// 			static	Nodepref	Prev(Nodeptr P) { return ((Nodepref)(*P).m_prev); }
// 			static	Vref		Value(Nodeptr P) { return ((Vref)(*P).m_value); }
// 		};

	
// 	public:
// 		typedef				A					allocator_type;
// 		typedef typename	A::size_type		size_type;
// 		typedef typename	A::difference_type	difference_type;
// 		typedef typename	A::pointer			pointer; 
// 		typedef typename	A::const_pointer	const_pointer;
// 		typedef typename	A::reference		reference;
// 		typedef typename	A::const_reference	const_reference;
// 		typedef typename	A::value_type		value_type;



// 	};

// }
