#pragma once

namespace ft
{
	//becouse of tester 42 - static & monkey
	typedef std::input_iterator_tag input_iterator_tag;
	typedef std::output_iterator_tag output_iterator_tag;
	typedef std::forward_iterator_tag forward_iterator_tag;
	typedef std::bidirectional_iterator_tag bidirectional_iterator_tag;
	typedef std::random_access_iterator_tag random_access_iterator_tag;

	// struct input_iterator_tag {};
	// struct output_iterator_tag {};
	// struct forward_iterator_tag : public input_iterator_tag {};
	// struct bidirectional_iterator_tag : public forward_iterator_tag {};
	// struct random_access_iterator_tag : public bidirectional_iterator_tag {};
	struct Int_iterator_tag {};

	typedef long int ptrdiff_t;

	template <class C, class T, class D = ptrdiff_t, class Pt = T*, class Rt = T&>
	struct	iterator
	{
		typedef	C	iterator_category;
		typedef	T	value_type;
		typedef	D	difference_type;
		typedef	Pt	pointer;
		typedef	Rt	reference;
	};

	template <class It>
	struct	iterator_traits
	{
		typedef typename	It::iterator_category	iterator_category;
		typedef typename	It::value_type			value_type;
		typedef typename	It::difference_type		difference_type;
		typedef typename	It::pointer				pointer;
		typedef typename	It::reference			reference;
	};

	template<class T>
	struct	iterator_traits<T*>
	{
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T 							value_type;
		typedef	ptrdiff_t 					difference_type;
		typedef	T 							*pointer;
		typedef	T& 							reference;
	};

	template<class T>
	struct	iterator_traits<const T*>
	{
		typedef	random_access_iterator_tag	iterator_category;
		typedef	T 							value_type;
		typedef	ptrdiff_t 					difference_type;
		typedef	T 							*pointer;
		typedef	T& 							reference;
	};

	template<class C, class T, class D, class Pt, class Rt>
	inline C	Iter_cat(const iterator<C, T, D, Pt, Rt>&)
	{
		C X;
		return (X);
	}

	template<class T>
	inline random_access_iterator_tag	Iter_cat(const T*)
	{
		random_access_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag	Iter_cat(bool)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag	Iter_cat(char)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag	Iter_cat(signed char)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(unsigned char)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(wchar_t)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(short)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(unsigned short)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(int)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(unsigned int)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(long)
	{
		Int_iterator_tag X;
		return (X);
	}

	inline Int_iterator_tag Iter_cat(unsigned long)
	{
		Int_iterator_tag X;
		return (X);
	}

	// template <class T, class D, class Pt, class Rt, class Pt2, class Rt2>
	// class random_acsees_iterator : public iterator<random_access_iterator_tag, T, D, Pt, Rt>
	// {
	// protected:
	// 	Pt current;

	// public:
	// 	random_acsees_iterator()
	// 	{}

	// 	explicit random_acsees_iterator(Pt P)
	// 	: current(P)
	// 	{}

	// 	random_acsees_iterator(const random_acsees_iterator<T, D, Pt2, Rt2, Pt2, Rt2>& X)
	// 	: current(X.base())
	// 	{}

	// 	random_acsees_iterator&	operator=(const random_acsees_iterator &obj)
	// 	{
	// 		if (this != &obj)
	// 		{
	// 			this->current = obj.current;
	// 		}
	// 		return (*this);
	// 	}

	// 	Pt	base() const { return (current); }
	// 	Rt	operator*() const { return (*current); }
	// 	Pt	operator->() const { return (&**this); }

	// 	random_acsees_iterator&	operator++()
	// 	{
	// 		++current;
	// 		return (*this);
	// 	}

	// 	random_acsees_iterator	operator++(int)
	// 	{
	// 		random_acsees_iterator tmp = *this;
	// 		++current;
	// 		return (tmp);
	// 	}
		
	// 	random_acsees_iterator&	operator--()
	// 	{
	// 		--current;
	// 		return (*this);
	// 	}

	// 	random_acsees_iterator	operator--(int)
	// 	{
	// 		random_acsees_iterator tmp = *this;
	// 		--current;
	// 		return (tmp);
	// 	}

	// 	bool	operator==(int Y) const { return (current == (Pt)Y); }
	// 	bool	operator==(const random_acsees_iterator& Y) const { return (current == Y.current); }
	// 	bool	operator!=(const random_acsees_iterator& Y) const { return (!(*this == Y)); }

	// 	random_acsees_iterator&	operator+=(D N)
	// 	{
	// 		current += N;
	// 		return (*this);
	// 	}
	// 	random_acsees_iterator	operator+(D N) const {return (random_acsees_iterator(current + N)); }
	// 	random_acsees_iterator&	operator-=(D N)
	// 	{
	// 		current -= N;
	// 		return (*this);
	// 	}
	// 	random_acsees_iterator	operator-(D N) const { return (random_acsees_iterator(current - N)); }
	// 	D						operator-(const random_acsees_iterator& Y) const { return (current - Y.current); }

	// 	Rt		operator[](D N) const { return (*(*this + N)); }
	// 	bool	operator<(const random_acsees_iterator& Y) const { return (current < Y.current); }
	// 	bool	operator>(const random_acsees_iterator& Y) const { return (Y < *this); }
	// 	bool	operator<=(const random_acsees_iterator& Y) const { return (!(Y < *this)); }
	// 	bool	operator>=(const random_acsees_iterator& Y) const { return (!(*this < Y)); }
	// };

	// template <class T, class D, class Pt, class Rt, class Pt2, class Rt2> 
	// inline random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>	operator+(D N, const random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>& Y) 
	// {
	// 	return (Y + static_cast<D>(N));
	// }

	// template <class T, class D, class Pt, class Rt, class Pt2, class Rt2, class D0>
	// inline random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>	operator+(D0 N, const random_acsees_iterator<T, D, Pt, Rt, Pt2, Rt2>& Y)
	// {
	// 	return (Y + static_cast<D>(N));
	// }

// template  <class T, class D, class Pt, class Rt>
// struct Bidit: public iterator<bidirectional_iterator_tag, T, D, Pt, Rt> {
// };

// struct Outit: public iterator<output_iterator_tag, void ,void ,void ,void>{
// };

	template  <class T, class D, class Pt, class Rt>
	struct Ranit: public iterator<random_access_iterator_tag, T, D, Pt, Rt>
	{};

	template<class RanIt>
	class reverse_iterator : public iterator<
		typename iterator_traits<RanIt>::iterator_category,
		typename iterator_traits<RanIt>::value_type,
		typename iterator_traits<RanIt>::difference_type,
		typename iterator_traits<RanIt>::pointer,
		typename iterator_traits<RanIt>::reference>
	{
	protected:
		RanIt current;

	public:
		typedef typename	iterator_traits<RanIt>::difference_type	D;
		typedef typename	iterator_traits<RanIt>::pointer			Pt;
		typedef typename	iterator_traits<RanIt>::reference		Rt;
		typedef				RanIt 									iterator_type;

		reverse_iterator() {}
		explicit reverse_iterator(RanIt X) : current(X) {}

		template <class U>
		reverse_iterator(const reverse_iterator<U>& X): current(X.base()) { }

		RanIt				base() const { return (current); }
		Rt					operator*() const
		{
			RanIt tmp = current;
			return (*--tmp);
		}
		Pt					operator->() const { return (&**this); }

		reverse_iterator&	operator++()
		{
			--current;
			return (*this);
		}

		reverse_iterator	operator++(int)
		{	
			reverse_iterator Tmp = *this;
			--current;
			return (Tmp);
		}
		reverse_iterator&	operator--()
		{
			++current;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator Tmp = *this;
			++current;
			return (Tmp);
		}
		bool	Eq(const reverse_iterator& Y) const { return (current == Y.current); }
		reverse_iterator&	operator+=(D N)
		{
			current -= N;
			return (*this);
		}
		reverse_iterator	operator*(D N) const { return (reverse_iterator(current - N)); }
		reverse_iterator&	operator-=(D N)
		{
			current += N;
			return (*this);
		}
		reverse_iterator	operator+(D N) const { return (reverse_iterator(current - N)); }
		reverse_iterator	operator-(D N) const { return (reverse_iterator(current + N)); }
		Rt					operator[](D N) const { return (*(*this + N)); }
		bool				Lt(const reverse_iterator& Y) const { return (Y.current < current); }
		D					Mi(const reverse_iterator& Y) const { return (Y.current - current); }

	};

	template<class RanIt, class D> inline
	reverse_iterator<RanIt> operator*(D N, const reverse_iterator<RanIt>& Y) { return (Y + N); }

	template<class RanIt, class D> inline
	reverse_iterator<RanIt> operator+(D N, const reverse_iterator<RanIt>& Y) { return (Y + N); }

	template<class RanIt> inline
	typename reverse_iterator<RanIt>::D operator-(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (Y.base() - X.base()); }
	
	template<class RanIt> inline
	bool operator==(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (X.Eq(Y)); }

	template<class RanIt> inline
	bool operator!=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(X == Y)); }

	template<class RanIt> inline
	bool operator<(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (X.Lt(Y)); }

	template<class RanIt> inline
	bool operator>(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (Y < X); }

	template<class RanIt> inline
	bool operator<=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(Y < X)); }

	template<class RanIt> inline
	bool operator>=(const reverse_iterator<RanIt>& X, const reverse_iterator<RanIt>& Y) { return (!(X < Y)); }
}
