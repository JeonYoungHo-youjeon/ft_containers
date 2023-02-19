#ifndef UTILS_HPP
 #define UTILS_HPP

 #include <iterator>

namespace ft
{
	template <class Iterator> 
	struct iterator_traits
	{
		typedef typename Iterator::difference_type       difference_type;
		typedef typename Iterator::value_type            value_type;
		typedef typename Iterator::pointer               pointer;
		typedef typename Iterator::reference             reference;
		typedef typename Iterator::iterator_category     iterator_category;
	};

	template <class T> 
	struct iterator_traits<T*>
	{
		typedef ptrdiff_t                       difference_type;
		typedef T                               value_type;
		typedef T*                              pointer;
		typedef T&                              reference;
		typedef std::random_access_iterator_tag  iterator_category;
	};

	template <class T> 
	struct iterator_traits<const T*>
	{
		typedef ptrdiff_t                       difference_type;
		typedef T                               value_type;
		typedef const T*                        pointer;
		typedef const T&                        reference;
		typedef std::random_access_iterator_tag  iterator_category;
	};

	// 생각해보니 구현 안하고 std::distance 가져다 썻어도 되지않나
	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type distance (InputIterator first, InputIterator last)
	{
		typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
		while (first != last)
		{
			first++;
			rtn++;
		}
		return (rtn);
	}


	template <typename T, T v>
	struct integral_constant 
	{
		static const T value = v;
		typedef T value_type;
		typedef integral_constant<T, v> type;
		operator value_type() { return value; }
		value_type operator()() const ;
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	template <typename T>
	struct	is_integral_base : public false_type {};

	template <>	struct	is_integral_base<bool> : public true_type {};
	template <>	struct	is_integral_base<char> : public true_type {};
	template <>	struct	is_integral_base<signed char> : public true_type {};
	template <>	struct	is_integral_base<unsigned char> : public true_type {};
	template <>	struct	is_integral_base<char16_t> : public true_type {};
	template <>	struct	is_integral_base<char32_t> : public true_type {};
	template <>	struct	is_integral_base<wchar_t> : public true_type {};
	template <>	struct	is_integral_base<short> : public true_type {};
	template <>	struct	is_integral_base<unsigned short> : public true_type {};
	template <>	struct	is_integral_base<int> : public true_type {};
	template <>	struct	is_integral_base<unsigned int> : public true_type {};
	template <>	struct	is_integral_base<long> : public true_type {};
	template <>	struct	is_integral_base<unsigned long> : public true_type {};
	template <>	struct	is_integral_base<long long> : public true_type {};
	template <>	struct	is_integral_base<unsigned long long> : public true_type {};
	template <>	struct	is_integral_base<__int128_t> : public true_type {};
	template <>	struct	is_integral_base<__uint128_t> : public true_type {};

	template<typename T>
	struct is_integral : public is_integral_base<typename std::remove_cv<T>::type> {};


	template <bool, typename = void>
	struct	enable_if {};

	template <typename T>
	struct	enable_if<true, T> { typedef T	type; };


	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}


	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2,
									Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
			++first1;
			++first2;
		}
		return (first2 != last2);
	}

	template<class InputIterator1, class InputIterator2>
	bool equal( InputIterator1 first1, InputIterator1 last1,
				InputIterator2 first2 )
	{
		for (; first1 != last1; ++first1, ++first2) 
		{
			if (!(*first1 == *first2)) 
				return false;
		}
		return true;
	}

	template<class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal( InputIterator1 first1,
				InputIterator1 last1,
				InputIterator2 first2,
				BinaryPredicate p )
	{
		for (; first1 != last1; ++first1, ++first2) 
		{
			if (!p(*first1, *first2)) 
				return false;
		}
		return true;
	}


	template<class T1, class T2>
	struct pair 
	{
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() : first(), second() {}
		pair(const T1& a, const T2& b) : first(a), second(b) { }
		
		template<class U1, class U2>
		pair (const pair<U1, U2>& p) : first(p.first), second(p.second) { }

		friend bool operator== (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (x.first == y.first && x.second == y.second);
		}

		friend bool operator< (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (x.first < y.first || (!(y.first < x.first) && x.second < y.second));
		}

		friend bool operator!= (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (!(x == y));
		}

		friend bool operator> (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (y < x);
		}

		friend bool operator<= (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (!(y < x));
		}

		friend bool operator>= (const pair<T1, T2>& x, const pair<T1, T2>& y)
		{
			return (!(x < y));
		}
	};

	template <class T1, class T2>
	pair<T1, T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}


	template<class T>
	void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
	
} // namespace ft


#endif