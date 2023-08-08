#pragma once

#include <memory>
#include "../utility/rb_tree.hpp"
#include "../utility/xutility.hpp"

namespace ft
{
	template<class K, class T, class Pr, class Ax, bool Mfl>
	class Tmap_traits
	{
	protected:
		Pr	m_comp;

	public:
		typedef	K						key_type;
		typedef	ft::pair<const K, T>	value_type;
		typedef	Pr						key_compare;


		typedef	typename Ax::template rebind<value_type>::other	allocator_type;

		struct Kfn
		{
			const K& operator()(const value_type& X) const
			{
				return(X.first);
			}
		};

		enum {Multi = Mfl};

		Tmap_traits()
		: m_comp()
		{}

		Tmap_traits(Pr Parg)
		: m_comp(Parg)
		{}

		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
		public:
			bool operator()(const value_type& X, const value_type& Y) const
			{
				return (comp(X.first, Y.first));
			}
			value_compare (key_compare Pred)
			: comp(Pred)
			{}
		protected:
			key_compare comp;
		};

	};

	template<class K, class T, class Pr = ft::less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class map : public Tree<Tmap_traits<K, T, Pr, A, false> >
	{
	public:
		typedef				Tree<Tmap_traits<K, T, Pr, A, false> >	Base;
		typedef				K										key_type;
		typedef				T										mapped_type;
		typedef				T										referent_type;
		typedef				Pr										key_compare;
		typedef typename	Base::value_compare						value_compare;
		typedef typename	Base::allocator_type					allocator_type;
		typedef typename	Base::size_type							size_type;
		typedef typename	Base::difference_type					difference_type;
		typedef typename	Base::pointer							pointer;
		typedef typename	Base::const_pointer						const_pointer;
		typedef typename	Base::reference							reference;
		typedef typename	Base::const_reference					const_reference;
		typedef typename	Base::iterator							iterator;
		typedef typename	Base::const_iterator					const_iterator;
		typedef typename	Base::reverse_iterator					reverse_iterator;
		typedef typename	Base::const_reverse_iterator			const_reverse_iterator;
		typedef typename	Base::value_type						value_type;

		map()
		: Base(key_compare(), allocator_type())
		{}

		explicit map(const key_compare& Pred)
		: Base(Pred, allocator_type())
		{}

		map(const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{}

		template<class It>
		map(It F, It L)
		: Base(key_compare(), allocator_type())
		{
			for(;F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		map(It F, It L, const key_compare& Pred) : Base(Pred, allocator_type())
		{
			for(;F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		map(It F, It L, const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{
			for(;F != L; ++F)
				this->insert(*F);
		}

		mapped_type& operator[](const key_type& Kv)
		{
			iterator P = this->insert(value_type(Kv, mapped_type())).first;
			return((*P).second);
		}
	};

	template<class K, class T, class Compare, class Alloc>
	void swap(map<K, T, Compare, Alloc> &X, map<K, T, Compare, Alloc> &Y)
	{
		X.swap(Y);
	}

	template<class K, class T, class Pr = less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class multimap : public Tree<Tmap_traits<K, T, Pr, A, true> >
	{
	public:
		typedef				Tree<Tmap_traits<K, T, Pr, A, true> >	Base;
		typedef				K										key_type;
		typedef 			T										mapped_type;
		typedef				T										referent_type;
		typedef				Pr										key_compare;
		typedef typename	Base::value_compare						value_compare;
		typedef typename	Base::allocator_type					allocator_type;
		typedef typename	Base::size_type							size_type;
		typedef typename	Base::difference_type					difference_type;
		typedef typename	Base::pointer							pointer;
		typedef typename	Base::const_pointer					const_pointer;
		typedef typename	Base::reference						reference;
		typedef typename	Base::const_reference					const_reference;
		typedef typename	Base::iterator						iterator;
		typedef typename	Base::const_iterator					const_iterator;
		typedef typename	Base::reverse_iterator				reverse_iterator;
		typedef typename	Base::const_reverse_iterator			const_reverse_iterator;
		typedef typename	Base::value_type						value_type;
		
		multimap ()
		: Base(key_compare(), allocator_type())
		{}
		
		explicit multimap(const key_compare& Pred)
		: Base(Pred, allocator_type())
		{}
		
		multimap(const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{}
		
		template<class It>
		multimap (It F, It L)
		: Base(key_compare(), allocator_type())
		{
			for (; F != L; ++F) 
			{
				insert(*F);
			}
		}
		
		template<class It>
		multimap(It F, It L, const key_compare& Pred)
		: Base(Pred, allocator_type())
		{
			for (; F != L; ++F)
			{
				insert(*F);
			}
		}
		
		template<class It>
		multimap(It F, It L, const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{
			for (; F != L; ++F)
			{
				insert(* F);
			}
		}

		iterator insert(const value_type& X)
		{
			return (Base::insert(X).first);
		}
		
		iterator insert(iterator P, const value_type& X)
		{
			return (Base::insert(P, X));
		}
		
		template<class It>
		void insert(It F, It L)
		{
			for (; F != L; ++F)
			{
				insert(*F);
			}
		}
	};

	template<class K, class T, class Compare, class Alloc>
	void swap(multimap<K, T, Compare, Alloc> &X, multimap<K, T, Compare, Alloc> &Y)
	{
		X.swap(Y);
	}
}
