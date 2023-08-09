#pragma once

#include <memory>
#include "../utility/hash_table.hpp"

namespace ft
{

	template<class K, class T, class Hash, class Pr, class Ax, bool Mfl>
	class Hmap_traits
	{
	protected:
		Hash	m_hash;
		Pr		comp;

	public:
		typedef				K						key_type;
		typedef				ft::pair<const K, T>	value_type;
		typedef				Hash					hasher;
		typedef				Pr						key_compare;

		typedef typename	Ax::template rebind<value_type>::other	allocator_type;

		enum {Multi = Mfl};

		Hmap_traits()
		: m_hash()
		, comp()
		{}

		Hmap_traits(const Hash& H, const Pr& Parg)
		: m_hash(H)
		, comp(Parg)
		{}

		class value_compare : public ft::binary_function<value_type, value_type, bool>
		{
			friend class Hmap_traits<K, T, Hash, Pr, Ax, Mfl>;

			protected:
				key_compare comp;

			public:
				bool operator()(const value_type& L, const value_type& R) const
				{
					return (comp(L.first, R.first));
				}

				value_compare(const key_compare& Parg)
				: comp(Parg)
				{}
			};

			static const K& Kfn(const value_type& V)
			{
				return (V.first);
			}

		};


	template<class K, class T, class Hash = ft::hash_compare<K>, class Pr = ft::less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class unordered_map : public Hash_table<Hmap_traits<K, T, Hash, Pr, A, false> >
	{
	public:
		typedef				ft::Hash_table<Hmap_traits<K, T, Hash, Pr, A, false> >	Base;
		typedef				K													key_type;
		typedef				T													mapped_type;
		typedef				T													referent_type;
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

		unordered_map()
		: Base(hasher(), key_compare(), allocator_type())
		{}

		explicit unordered_map(const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{}

		unordered_map(const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{}

		template<class It>
		unordered_map(It F, It L)
		: Base(hasher(), key_compare(), allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		template<class It>
		unordered_map(It F, It L, const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

	template<class It>
		unordered_map(It F, It L, const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		mapped_type& operator[](const key_type& Keyval)
		{
			iterator P = insert(value_type(Keyval, mapped_type())).first;
			return ((*P).second);
		}
	};

	template<class K, class T, class Hash, class Pr, class A>
	void swap(unordered_map<K, T, Hash, Pr, A> &X, unordered_map<K, T, Hash, Pr, A> &Y)
	{
		X.swap(Y);
	}

	template<class K, class T, class Hash = ft::hash_compare<K>, class Pr = ft::less<K>, class A = std::allocator<ft::pair<const K, T> > >
	class unordered_multimap : public Hash_table<Hmap_traits<K, T, Hash, Pr, A, true> >
	{

	public:
		typedef				Hash_table<Hmap_traits<K, T, Hash, Pr, A, true> >	Base;
		typedef				K											key_type;
		typedef				T											mapped_type;
		typedef				T											referent_type;
		typedef				Hash										hasher;
		typedef				Pr											key_compare;
		typedef typename	Base::value_compare							value_compare;
		typedef typename	Base::allocator_type						allocator_type;
		typedef typename	Base::size_type								size_type;
		typedef typename	Base::difference_type						difference_type;
		typedef typename	Base::pointer								pointer;
		typedef typename	Base::const_pointer							const_pointer;
		typedef typename	Base::reference								reference;
		typedef typename	Base::const_reference						const_reference;
		typedef typename	Base::iterator								iterator;
		typedef typename	Base::const_iterator						const_iterator;
		typedef typename	Base::reverse_iterator						reverse_iterator;
		typedef typename	Base::const_reverse_iterator				const_reverse_iterator;
		typedef typename	Base::value_type							value_type;

		unordered_multimap()
		: Base(hasher(), key_compare(), allocator_type())
		{}

		explicit unordered_multimap(const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{}

		unordered_multimap(const hasher& H, const key_compare& Pred, const allocator_type& Al)
		: Base(H, Pred, Al)
		{}

		template<class It>
		unordered_multimap(It F, It L)
		: Base(hasher(), key_compare(), allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		template<class It>
		unordered_multimap(It F, It L, const hasher& H, const key_compare& Pred)
		: Base(H, Pred, allocator_type())
		{
			for (; F != L; ++F)
				this->insert(*F);
		}

		template<class It>
		unordered_multimap(It F, It L, const hasher& H, const key_compare& Pred, const allocator_type& Al)
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

	template<class K, class T, class Hash, class Pr, class A>
	void swap(unordered_multimap<K, T, Hash, Pr, A> &X, unordered_multimap<K, T, Hash, Pr, A> &Y)
	{
		X.swap(Y);
	}

}