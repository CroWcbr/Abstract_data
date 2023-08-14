#pragma once

#include <memory>
#include "../utility/hash_table.hpp"

namespace ft
{

	template<class K, class Hash, class Pr, class Ax, bool Mfl >
	class Hset_traits
	{
	protected:
		Hash	m_hash;
		Pr		comp;

	public:
		typedef	K			key_type;
		typedef	K			value_type;
		typedef	Hash		hasher;
		typedef	Pr			key_compare;
		typedef	key_compare	value_compare;

		typedef typename Ax::template rebind<value_type>::other	allocator_type;

		static const K& Kfn(const value_type& V)
		{
			return (V);
		}

		enum {Multi = Mfl};

		Hset_traits()
		: m_hash()
		, comp()
		{}

		Hset_traits(const Hash& H, const Pr& Parg)
		: m_hash(H)
		, comp(Parg)
		{}
	};

	template<class K, class Hash = ft::hash_compare<K>, class Pr = ft::less<K>,	class A = std::allocator<K> >
	class unordered_set : public ft::Hash_table<Hset_traits<K, Hash, Pr, A, false> >
	{
	public:
		typedef				ft::Hash_table<Hset_traits<K, Hash, Pr, A, false> >	Base;
		typedef				K										key_type;
		typedef				Hash									hasher;
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

		unordered_set()
		: Base(hasher(), key_compare(), allocator_type())
		{}

		explicit unordered_set(const hasher& H)
		: Base(H, key_compare(), allocator_type())
		{}

		explicit unordered_set(const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{}

		unordered_set(const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{}

		template<class It>
		unordered_set(It F, It L)
		: Base(hasher(), key_compare(), allocator_type())
		{
			for (; F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		unordered_set(It F, It L, const hasher& H)
		: Base(H, key_compare(), allocator_type())
		{
			for (; F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		unordered_set(It F, It L, const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{
			for (; F != L; ++F)
			{
				this->insert(*F);
			}
		}

		template<class It>
		unordered_set(It F, It L, const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{
			for (; F != L; ++F)
			{
				this->insert(*F);
			}
		}
	};

	template<class K, class Hash, class Pr, class A>
	void swap(unordered_set<K, Hash, Pr, A> &X, unordered_set<K, Hash, Pr, A> &Y)
	{
		X.swap(Y);
	}

	template<class K, class Hash = ft::hash_compare<K>, class Pr = ft::less<K>,	class A = std::allocator<K> >
	class unordered_multiset : public ft::Hash_table<Hset_traits<K, Hash, Pr, A, true> >
	{
	public:
		typedef				ft::Hash_table<Hset_traits<K, Hash, Pr, A, true> >	Base;
		typedef				K													key_type;
		typedef				Hash												hasher;
		typedef				Pr													key_compare;
		typedef typename	Base::value_compare									value_compare;
		typedef typename	Base::allocator_type								allocator_type;
		typedef typename	Base::size_type										size_type;
		typedef typename	Base::difference_type								difference_type;
		typedef typename	Base::pointer										pointer;
		typedef typename	Base::const_pointer									const_pointer;
		typedef typename	Base::reference										reference;
		typedef typename	Base::const_reference								const_reference;
		typedef typename	Base::iterator										iterator;
		typedef typename	Base::const_iterator								const_iterator;
		typedef typename	Base::reverse_iterator								reverse_iterator;
		typedef typename	Base::const_reverse_iterator						const_reverse_iterator;
		typedef typename	Base::value_type									value_type;

		unordered_multiset()
		: Base(hasher(), key_compare(), allocator_type())
		{}

		explicit unordered_multiset(const hasher& H)
		: Base(H, key_compare(), allocator_type())
		{}

		explicit unordered_multiset(const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{}

		unordered_multiset(const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{}

		template<class It>
		unordered_multiset(It F, It L)
		: Base(hasher(), key_compare(), allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		template<class It>
		unordered_multiset(It F, It L, const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		template<class It>
		unordered_multiset(It F, It L, const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		iterator insert(const value_type& V)
		{
			return (Base::insert(V).first);
		}

		iterator insert(iterator P, const value_type& V)
		{
		return (Base::insert(P, V));
		}

		template<class It>
		void insert(It F, It L)
		{
			for (; F != L; ++F)
				insert(*F);
		}
	};

	template<class K, class Hash, class Pr, class A>
	void swap(unordered_multiset<K, Hash, Pr, A> &X, unordered_multiset<K, Hash, Pr, A> &Y)
	{
		X.swap(Y);
	}
}