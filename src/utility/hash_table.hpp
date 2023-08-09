#pragma once

#include <memory>
#include "xutility.hpp"
#include "algorithm.hpp"
#include "exception.hpp"
#include "../containers/vector.hpp"
#include "../containers/list.hpp"

namespace ft
{
	template<class K>
	class hash_compare
	{
	public:
		unsigned int operator()(const K& Kv) const
		{
			return ((unsigned int)Kv);
		}
	};

	template<class T>
	class Hash_table : public T
	{
	public:
		typedef typename	T::key_type			key_type;
		typedef typename	T::hasher			hasher;
		typedef typename	T::key_compare		key_compare;
		typedef typename	T::value_compare	value_compare;

		enum
		{
			bucket_size = 4,
			min_buckets = 8
		};

		typedef	ft::list<typename T::value_type, typename T::allocator_type> Base_List;

		typedef typename	Base_List::allocator_type			allocator_type;
		typedef typename	Base_List::size_type				size_type;
		typedef typename	Base_List::difference_type			difference_type;
		typedef typename	Base_List::pointer					pointer;
		typedef typename	Base_List::const_pointer			const_pointer;
		typedef typename	Base_List::reference				reference;
		typedef typename	Base_List::const_reference			const_reference;
		typedef typename	Base_List::iterator					iterator;
		typedef typename	Base_List::const_iterator			const_iterator;
		typedef typename	Base_List::reverse_iterator			reverse_iterator;
		typedef typename	Base_List::const_reverse_iterator	const_reverse_iterator;
		typedef typename	Base_List::value_type				value_type;

		typedef	ft::vector<iterator, typename allocator_type::template rebind<iterator>::other>	Base_Vec;
		typedef	pair<iterator, bool>					Pairib;
		typedef	pair<iterator, iterator>				Pairii;
		typedef	pair<const_iterator, const_iterator>	Paircc;

	protected:
	public:
		Base_List	m_list;
		Base_Vec	m_vec;
		size_type	m_mask;
		size_type	m_maxidx;

	public:
		explicit Hash_table(const hasher& H, const key_compare& Parg, const allocator_type& A)
		: T(H, Parg)
		, m_list(A)
		, m_vec(min_buckets + 1, end(), A)
		, m_mask(1)
		, m_maxidx(1)
		{}

		Hash_table(const value_type *F, const value_type *L, const hasher& H, const key_compare& Parg, const allocator_type& A)
		: T(H, Parg)
		, m_list(A)
		, m_vec(min_buckets + 1, end(), A)
		, m_mask(1)
		, m_maxidx(1)
		{
			insert(F, L);
		}

		Hash_table(const Hash_table& X)
		: T(X.m_hash,X.comp)
		, m_list(X.get_allocator())
		, m_vec(X.get_allocator())
		{
			_copy(X);
		}

		~Hash_table()
		{}

		Hash_table& operator=(const Hash_table& X)
		{
			if (this != &X)
			{
				_copy(X);
			}
			return (*this);
		}

		iterator				begin() { return (m_list.begin()); }
		const_iterator			begin() const { return (m_list.begin()); }
		iterator				end() { return (m_list.end()); }
		const_iterator			end() const { return (m_list.end()); }
		reverse_iterator		rbegin() { return (m_list.rbegin()); }
		const_reverse_iterator	rbegin() const { return (m_list.rbegin()); }
		reverse_iterator		rend() { return (m_list.rend()); }
		const_reverse_iterator	rend() const { return (m_list.rend()); }
		size_type				size() const { return (m_list.size()); }
		size_type				max_size() const { return (m_list.max_size()); }
		bool					empty() const { return (m_list.empty()); }
		allocator_type			get_allocator() const { return (m_list.get_allocator()); }
		key_compare				key_comp() const { return (this->comp); }

		Pairib	insert(const value_type& V)
		{
			iterator Plist;
			iterator Where;
			if (m_maxidx <= size() / bucket_size)
			{
				if (m_vec.size() - 1 <= m_maxidx)
				{
					m_mask = ((m_vec.size() - 1) << 1) - 1;
					m_vec.resize(m_mask + 2, end());
				}
				else if (m_mask < m_maxidx)
				{
					m_mask = (m_mask << 1) + 1;
				}

				size_type Bucket = m_maxidx - (m_mask >> 1) - 1;
				for (Plist = m_vec[Bucket]; Plist != m_vec[Bucket + 1]; )
				{
					if ((this->m_hash(this->Kfn(*Plist)) & m_mask) == Bucket)
					{
						++Plist;
					}
					else
					{
						iterator Pnext = Plist;
						size_type Idx;
						for (Idx = m_maxidx; Bucket < Idx; --Idx)
						{
							if (m_vec[Idx] != end())
								break;
							m_vec[Idx] = Plist;
						}
						if (++Pnext == end())
							break;
						else
						{
							for (Idx = Bucket; Plist == m_vec[Idx]; --Idx)
							{
								++m_vec[Idx];
								if (Idx == 0)
									break;
							}
							m_list.splice(end(), m_list, Plist);
							Plist = Pnext;
							m_vec[m_maxidx + 1] = end();
						}
					}
				}
				++m_maxidx;
			}


			size_type Bucket = _hashval(this->Kfn(V));
	// std::cout << m_vec.size() << "\t" << Bucket<< std::endl;
			for (Plist = m_vec[Bucket + 1]; Plist != m_vec[Bucket]; )
			{
	// std::cout << "Plist\t" << *Plist << std::endl;
				if (this->comp(this->Kfn(V), this->Kfn(*--Plist)))
					;
				else if (this->comp(this->Kfn(*Plist), this->Kfn(V)))
				{
					++Plist;
					break;
				}
				else if (T::Multi)
				{	
							break;
				}
				else
				{
					return (Pairib(Plist, false));
				}
			}
	// std::cout << "INSERT!!!!" << std::endl;
			Where = m_list.insert(Plist, V);
			for (; Plist == m_vec[Bucket]; --Bucket)
			{
				m_vec[Bucket] = Where;
				if (Bucket == 0)
					break;
			}
			return (Pairib(Where, true));
		}

		iterator insert(iterator, const value_type& V)
		{
			return (insert(V).first);
		}

		template<class _Iter>
		void insert(_Iter F, _Iter L)
		{
			for (; F != L; ++F)
				insert(*F);
		}

		iterator erase(iterator Where)
		{
			size_type Bucket = _hashval(this->Kfn(*Where));
			for (; Where == m_vec[Bucket]; --Bucket)
			{
				++m_vec[Bucket];
				if (Bucket == 0)
					break;
			}
			return (m_list.erase(Where));
		}

		iterator erase(iterator F, iterator L)
		{
			if (F == begin() && L == end())
			{
				clear();
				return (begin());
			}
			else
			{
				while (F != L)
					erase(F++);
				return (F);
			}
		}

		size_type erase(const key_type& X)
		{
			Pairii Where = equal_range(X);
			size_type N = 0;
			ft::distance(Where.first, Where.second, N);
			erase(Where.first, Where.second);
			return (N);
		}

		void erase(const key_type *F, const key_type *L)
		{
			for (; F != L; ++F)
				erase(*F);
		}

		void clear()
		{
			m_list.clear();
			m_vec.assign(min_buckets + 1, end());
			m_mask = 1;
			m_maxidx = 1;
		}

		iterator find(const key_type& Kv)
		{
			return (lower_bound(Kv));
		}

		const_iterator find(const key_type& Kv) const
		{
			return (lower_bound(Kv));
		}

		size_type count(const key_type& Kv) const
		{
			Paircc _Ans = equal_range(Kv);
			size_type N = 0;
			ft::distance(_Ans.first, _Ans.second, N);
			return (N);
		}

		iterator lower_bound(const key_type& Kv)
		{
			size_type Bucket = _hashval(Kv);
			iterator Where;
			for (Where = m_vec[Bucket]; Where != m_vec[Bucket + 1]; ++Where)
			{
				if (!this->comp(this->Kfn(*Where), Kv))
					return (this->comp(Kv, this->Kfn(*Where)) ? end() : Where);
			}
			return (end());
		}

		const_iterator lower_bound(const key_type& Kv) const
		{
			size_type Bucket = _hashval(Kv);
			const_iterator Where;
			for (Where = m_vec[Bucket]; Where != m_vec[Bucket + 1]; ++Where)
			{
				if (!this->comp(this->Kfn(*Where), Kv))
					return (this->comp(Kv, this->Kfn(*Where)) ? end() : Where);
			}
			return (end());
		}

		iterator upper_bound(const key_type& Kv)
		{
			size_type Bucket = _hashval(Kv);
			iterator Where;
			for (Where = m_vec[Bucket + 1]; Where != m_vec[Bucket]; )
			{
				if (!this->comp(Kv, this->Kfn(*--Where)))
					return (this->comp(this->Kfn(*Where), Kv) ? end() : ++Where);
			}
			return (end());
		}

		const_iterator upper_bound(const key_type& Kv) const
		{
			size_type Bucket = _hashval(Kv);
			const_iterator Where;
			for (Where = m_vec[Bucket + 1]; Where != m_vec[Bucket];)
			{
				if (!this->comp(Kv, this->Kfn(*--Where)))
					return (this->comp(this->Kfn(*Where), Kv) ? end() : ++Where);
			}
			return (end());
		}

		Pairii equal_range(const key_type& Kv)
		{
			size_type Bucket = _hashval(Kv);
			iterator First, Where;
			for (Where = m_vec[Bucket]; Where != m_vec[Bucket + 1]; ++Where)
			{
				if (!this->comp(this->Kfn(*Where), Kv))
				{
					for (First = Where; Where != m_vec[Bucket + 1]; ++Where)
					{
						if (this->comp(Kv, this->Kfn(*Where)))
							break;
					}
					if (First == Where)
						break;
					return (Pairii(First, Where));
				}
			}
			return (Pairii(end(), end()));
		}

		Paircc equal_range(const key_type& Kv) const
		{
			size_type Bucket = _hashval(Kv);
			iterator First;
			iterator Where;
			for (Where = m_vec[Bucket]; Where != m_vec[Bucket + 1]; ++Where)
			{
				if (!this->comp(this->Kfn(*Where), Kv))
					{
					for (First = Where; Where != m_vec[Bucket + 1]; ++Where)
					{
						if (this->comp(Kv, this->Kfn(*Where)))
							break;
					}
					if (First == Where)
						break;
					return (Paircc(First, Where));
					}
			}
			return (Paircc(end(), end()));
		}

		void swap(Hash_table& X)
		{
			if (get_allocator() == X.get_allocator())
			{
				m_list.swap(X.m_list);
				ft::swap(m_vec, X.m_vec);
				ft::swap(m_mask, X.m_mask);
				ft::swap(m_maxidx, X.m_maxidx);
				ft::swap(this->m_hash, X.m_hash);
				ft::swap(this->comp, X.comp);
			}
			else
			{
				Hash_table Tmp = *this;
				*this = X;
				X = Tmp;
			}
		}

	protected:
		void _copy(const Hash_table& Right)
		{
			m_vec.resize(Right.m_vec.size(), end());
			m_mask = Right.m_mask;
			m_maxidx = Right.m_maxidx;
			m_list.clear();

			try
			{
				m_list.insert(end(), Right.m_list.begin(), Right.m_list.end());
				this->comp = Right.comp;
			}
			catch(...)
			{
				m_list.clear();
				ft::fill(m_vec.begin(), m_vec.end(), end());
				throw;
			}

			iterator Whereto = begin();
			const_iterator Wherefrom = Right.begin();
			for (size_type Bucket = 0; Bucket < m_vec.size(); )
			{
				if (Wherefrom == Right.m_vec[Bucket])
					m_vec[Bucket] = Whereto, ++Bucket;
				else
					++Whereto, ++Wherefrom;
			}
		}

		size_type _hashval(const key_type& Kv) const
		{
			size_type N = this->m_hash(Kv) & m_mask;
			if (m_maxidx <= N)
				N -= (m_mask >> 1) + 1;
			// size_type N = this->m_hash(Kv) % m_maxidx;
			return (N);
		}
	};

	template<class T> inline
	bool operator==(const Hash_table<T>& X, const Hash_table<T>& Y) { return (X.size() == Y.size() && ft::equal(X.begin(), X.end(), Y.begin())); }

	template<class T> inline
	bool operator!=(const Hash_table<T>& X, const Hash_table<T>& Y) { return (!(X == Y)); }

	template<class T> inline
	bool operator<(const Hash_table<T>& X, const Hash_table<T>& Y) { return (ft::lexicographical_compare(X.begin(), X.end(), Y.begin(), Y.end())); }

	template<class T> inline
	bool operator>(const Hash_table<T>& X, const Hash_table<T>& Y) { return (Y < X); }

	template<class T> inline
	bool operator<=(const Hash_table<T>& X, const Hash_table<T>& Y) { return (!(Y < X)); }

	template<class T> inline
	bool operator>=(const Hash_table<T>& X, const Hash_table<T>& Y) { return (!(X < Y)); }

	template<class T> inline
	void swap(Hash_table<T>& X, Hash_table<T>& Y) { X.swap(Y); }

}
