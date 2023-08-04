#pragma once

#include <memory>
#include "../utility/rb_tree.hpp"

namespace ft
{
	template<class K, class Pr, class Ax, bool Mfl>
	class Tset_traits
	{
	protected:
		Pr	m_comp;

	public:
		typedef	K			key_type;
		typedef	K			value_type;
		typedef	Pr			key_compare;
		typedef	key_compare	value_compare;

		typedef typename Ax::template rebind<value_type>::other	allocator_type;

		struct Kfn
		{
			const K& operator()(const value_type& X) const
			{
				return (X);
			};
		};

		enum {Multi = Mfl};

		Tset_traits()
		: m_comp()
		{}

		Tset_traits(Pr Parg)
		: m_comp(Parg)
		{}
	};

	template<class K, class Pr = ft::less<K>, class A = std::allocator<K> >
	class set : public ft::Tree<Tset_traits<K, Pr, A, false> >
	{
	public:
		typedef				ft::Tree<Tset_traits<K, Pr, A, false> >	Base;
		typedef				K										key_type;
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

		set()
		: Base(key_compare(), allocator_type())
		{}

		explicit set(const key_compare& Pred)
		: Base(Pred, allocator_type())
		{}

		set(const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{}

		template<class It>
		set(It F, It L)
		: Base(key_compare(), allocator_type())
		{
			for (; F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		set(It F, It L, const key_compare& Pred)
		: Base(Pred, allocator_type())
		{
			for (; F != L; ++F)
			{
				this->insert (*F);
			}
		}

		template<class It>
		set(It F, It L, const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{
			for (; F != L; ++F)
			{
				this->insert (*F);
			}
		}
	};

	template<class K, class Pr = less<K>, class A = std::allocator<K> >
	class multiset : public Tree<Tset_traits<K, Pr, A, true> >
	{
	public:
		typedef				Tree<Tset_traits<K, Pr, A, true> >	Base;
		typedef				K									key_type;
		typedef				Pr									key_compare;
		typedef typename	Base::value_compare					value_compare;
		typedef typename	Base::allocator_type				allocator_type;
		typedef typename	Base::size_type						size_type;
		typedef typename	Base::difference_type				difference_type;
		typedef typename	Base::pointer						pointer;
		typedef typename	Base::const_pointer					const_pointer;
		typedef typename	Base::reference						reference;
		typedef typename	Base::const_reference				const_reference;
		typedef typename	Base::iterator						iterator;
		typedef typename	Base::const_iterator				const_iterator;
		typedef typename	Base::reverse_iterator				reverse_iterator;
		typedef typename	Base::const_reverse_iterator		const_reverse_iterator;
		typedef typename	Base::value_type					value_type;
		
		multiset()
		: Base(key_compare(), allocator_type())
		{}

		explicit multiset(const key_compare& Pred)
		: Base(Pred, allocator_type())
		{}

		multiset(const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{}

		template<class It>
		multiset(It F, It L)
		: Base(key_compare(), allocator_type())
		{
			for (; F != L; ++F)
			{
				insert(*F);
			}
		}

		template<class It>
		multiset(It F, It L, const key_compare& Pred)
		: Base(Pred, allocator_type())
		{
			for (; F != L; ++F)
			{
				insert(*F);
			}
		}
		
		template<class It>
		multiset(It F, It L, const key_compare& Pred, const allocator_type& Al)
		: Base(Pred, Al)
		{
			for (; F != L; ++F)
			{
				insert(*F);
			}
		}

		iterator	insert(const value_type& X)
		{
			return (Base::insert(X).first);
		}

		iterator	insert(iterator P, const value_type& X)
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

}
