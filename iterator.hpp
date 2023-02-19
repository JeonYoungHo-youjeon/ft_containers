#ifndef ITERATOR_HPP
 #define ITERATOR_HPP

#include "utils.hpp"
#include "node.hpp"
#include <iterator>

namespace ft
{
	template <typename T>
	class random_access_iterator : public std::iterator<std::random_access_iterator_tag, T>
	{
		public:
			typedef T*															iterator_type;
			typedef typename iterator_traits<iterator_type>::value_type			value_type;
			typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
			typedef typename iterator_traits<iterator_type>::pointer			pointer;
			typedef typename iterator_traits<iterator_type>::reference			reference;

		protected:
			pointer	current;

		public:
			random_access_iterator() : current(pointer()) { };
			random_access_iterator(pointer ptr) : current(ptr) { };

			template<typename U>
			random_access_iterator(const random_access_iterator<U>& ref) : current(ref.base()) { };
			~random_access_iterator(void) { };

			template<typename U>
			random_access_iterator& operator=(random_access_iterator<U>& rhs) 
			{
				current = rhs.base();
				return *this;
			}

			iterator_type base(void) const { return current; }
			pointer operator->(void) const { return current; }
			reference operator*(void) const { return *current; }
			reference operator[](difference_type n) const { return current[n]; }

			random_access_iterator& operator++(void)
			{
				++current;
				return *this;
			}

			random_access_iterator operator++(int)
			{
				random_access_iterator tmp(*this);
				++current;
				return tmp;
			}

			random_access_iterator& operator--(void)
			{
				--current;
				return *this;
			}

			random_access_iterator operator--(int)
			{
				random_access_iterator tmp(*this);
				--current;
				return tmp;
			}

			random_access_iterator operator+(difference_type n) const
			{
				return random_access_iterator(current + n);
			}

			random_access_iterator operator-(difference_type n) const
			{
				return random_access_iterator(current - n);
			}

			random_access_iterator& operator+=(difference_type n)
			{
				current += n;
				return *this;
			}

			random_access_iterator& operator-=(difference_type n)
			{
				current -= n;
				return *this;
			}
		
			friend bool operator==(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() == rhs.base();
			}
			
			friend bool operator!=(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() != rhs.base();
			}
			
			friend bool operator<(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() < rhs.base();
			}
			
			friend bool operator>(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() > rhs.base();
			}
			
			friend bool operator<=(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() <= rhs.base();
			}
			
			friend bool operator>=(const random_access_iterator& lhs, const random_access_iterator& rhs)
			{
				return lhs.base() >= rhs.base();
			}
			friend random_access_iterator operator+(typename random_access_iterator::difference_type n,
													const random_access_iterator& rhs)
			{
				return random_access_iterator(rhs.base() + n);
			}
			
			friend typename random_access_iterator::difference_type operator-(const random_access_iterator& lhs,
																			const random_access_iterator& rhs)
			{
				return lhs.base() - rhs.base();
			}
	};



	template <typename Iterator>
	class reverse_iterator: public std::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
												typename ft::iterator_traits<Iterator>::value_type,
												typename ft::iterator_traits<Iterator>::difference_type,
												typename ft::iterator_traits<Iterator>::pointer,
												typename ft::iterator_traits<Iterator>::reference >
	{

	public:
		typedef Iterator													iterator_type;
		typedef typename iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename iterator_traits<iterator_type>::value_type			value_type;
		typedef typename iterator_traits<iterator_type>::pointer			pointer;
		typedef typename iterator_traits<iterator_type>::reference			reference;
		typedef typename iterator_traits<iterator_type>::iterator_category	iterator_category;

	protected:
		iterator_type	current;

	public:
		reverse_iterator(void) : current(iterator_type()){ };
		explicit reverse_iterator(iterator_type iter) : current(iter) { };
		template<typename U>
		reverse_iterator(const reverse_iterator<U>& rhs) : current(rhs.base()) { };
		~reverse_iterator(void) { };

		iterator_type base(void) const { return current; };

		template<typename U>
		reverse_iterator& operator=(const reverse_iterator<U>& rhs)
		{
			current = rhs.base();
			return *this;
		}

		reverse_iterator operator+(difference_type n) const	{ return reverse_iterator(current - n); }
		reverse_iterator operator-(difference_type n) const	{ return reverse_iterator(current + n); }

		reverse_iterator& operator++(void)
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp(*this);
			--current;
			return tmp;
		}

		reverse_iterator& operator--(void)
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp(*this);
			++current;
			return tmp;
		}

		reverse_iterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		//	Access
		reference operator*(void) const
		{
			iterator_type	tmp(current);
			return *--tmp;
		}

		pointer operator->(void) const { return &operator*(); }
		reference operator[](difference_type n) const { return *(*this + n); };

		
		friend bool operator==(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() == rhs.base();
		}
		
		friend bool operator!=(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() != rhs.base();
		}
		
		friend bool operator<(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() > rhs.base();
		}
		
		friend bool operator>(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() < rhs.base();
		}
		
		friend bool operator<=(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() >= rhs.base();
		}
		
		friend bool operator>=(const reverse_iterator& lhs, const reverse_iterator& rhs)
		{
			return lhs.base() <= rhs.base();
		}

		friend reverse_iterator operator+(typename reverse_iterator::difference_type n,
										const reverse_iterator& iter)
		{
			return reverse_iterator(iter.base() - n);
		}
		
		friend typename reverse_iterator::difference_type operator-(const reverse_iterator& lhs,
																	const reverse_iterator& rhs)
		{
			return rhs.base() - lhs.base();
		}
	};


	template<class K, class V, class C, class A>
	class tree_const_iterator;

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class tree_iterator : public std::iterator< std::bidirectional_iterator_tag, ft::pair<const Key, T> >
	{
		public:
			typedef ft::pair<const Key, T>			value_type;
			typedef ptrdiff_t						difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;

		private:
			typedef avl_node<Key, T, Compare, Allocator>	node;
			typedef node*	node_ptr;
			typedef ft::pair<const Key, T>				const_pair_type;

		public:
			node_ptr	_root;
			node_ptr	_current;

		public:
			tree_iterator(node_ptr root, node_ptr current) : _root(root), _current(current) { }
			tree_iterator(const tree_iterator& other) : _root(other._root), _current(other._current) { }
			~tree_iterator() {}
			tree_iterator& operator=(const tree_iterator& other)
			{
				_root = other._root;
				_current = other._current;
				return *this;
			}

			reference operator*() const { return *reinterpret_cast<const_pair_type*>(&_current->key_value_pair()); }
			pointer operator->() const { return &(operator*()); }

			tree_iterator& operator++()
			{
				_current = node::next(this->_current, this->_root);
				return *this;
			}

			tree_iterator operator++(int)
			{
				node_ptr ret = _current;
				_current = node::next(this->_current, this->_root);
				return tree_iterator(this->_root, ret);
			}

			tree_iterator& operator--()
			{
				_current = node::prev(this->_current, this->_root);
				return *this;
			}

			tree_iterator operator--(int)
			{
				node_ptr ret = _current;
				_current = node::prev(this->_current, this->_root);
				return tree_iterator(this->_root, ret);
			}

			tree_iterator operator+(difference_type n) const
			{
				tree_iterator ret(this->_root, this->_current);
				while (n--) 
					++ret;

				return ret;
			}

			tree_iterator& operator+=(difference_type n)
			{
				while (n--)
					operator++();

				return *this;
			}

			tree_iterator operator-(difference_type n) const
			{
				tree_iterator ret(this->_root, this->_current);
				while (n--) 
					--ret;

				return ret;
			}

			tree_iterator& operator-=(difference_type n)
			{
				while (n--) 
					operator--();

				return *this;
			}

			node_ptr current_node() { return _current; }

			reference operator[](difference_type n) const
			{
				tree_iterator it(this->_root, this->_current);
				while (n--)
					++it;

				return *it;
			}

			bool operator==(const tree_iterator& other)
			{
				return (this->_root == other._root) && (this->_current == other._current);
			}
			
			bool operator==(const tree_const_iterator<Key, T, Compare, Allocator>& other)
			{
				return (this->_root == other._root) && (this->_current == other._current);
			}

			bool operator!=(const tree_iterator& other)
			{
				return (this->_root != other._root) || (this->_current != other._current);
			}
	};

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class tree_const_iterator : public std::iterator< std::bidirectional_iterator_tag, ft::pair<const Key, T> >
	{
		public:
			typedef ft::pair<const Key, T>		value_type;
			typedef ptrdiff_t						difference_type;
			typedef std::bidirectional_iterator_tag	iterator_category;
			typedef value_type*						pointer;
			typedef const value_type*				const_pointer;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;

		private:
			typedef avl_node<Key, T, Compare, Allocator>	node;
			typedef node*	node_ptr;
			typedef ft::pair<const Key, T>				const_pair_type;

		public:
			node_ptr	_root;
			node_ptr	_current;

		public:
			tree_const_iterator(node_ptr root, node_ptr current) : _root(root), _current(current) { }
			tree_const_iterator(const tree_const_iterator& other) : _root(other._root), _current(other._current) { }
			
			tree_const_iterator(const tree_iterator<Key, T, Compare, Allocator>& non_const) 
			: _root(non_const._root), _current(non_const._current)
			{ }

			~tree_const_iterator() {}

			tree_const_iterator& operator=(const tree_const_iterator& other)
			{
				_root = other._root;
				_current = other._current;
			
				return *this;
			}

			const_reference operator*() const { return *reinterpret_cast<const_pair_type*>(&_current->key_value_pair()); }
			const_pointer operator->() const { return &(operator*()); }

			tree_const_iterator& operator++()
			{
				_current = node::next(this->_current, this->_root);

				return *this;
			}

			tree_const_iterator operator++(int)
			{
				node_ptr ret = _current;
				_current = node::next(this->_current, this->_root);

				return tree_const_iterator(this->_root, ret);
			}

			tree_const_iterator& operator--()
			{
				_current = node::prev(this->_current, this->_root);

				return *this;
			}

			tree_const_iterator operator--(int)
			{
				node_ptr ret = _current;
				_current = node::prev(this->_current, this->_root);

				return tree_const_iterator(this->_root, ret);
			}

			tree_const_iterator operator+(difference_type n) const
			{
				tree_const_iterator ret(this->_root, this->_current);
				while (n--)
					++ret;

				return ret;
			}

			tree_const_iterator& operator+=(difference_type n)
			{
				while (n--) 
					operator++();

				return *this;
			}

			tree_const_iterator operator-(difference_type n) const
			{
				tree_const_iterator ret(this->_root, this->_current);
				while (n--) 
					--ret;

				return ret;
			}

			tree_const_iterator& operator-=(difference_type n)
			{
				while (n--) 
					operator--();

				return *this;
			}

			node_ptr current_node() { return _current; }

			reference operator[](difference_type n) const
			{
				tree_const_iterator it(this->_root, this->_current);
				while (n--)
					++it;

				return *it;
			}
			
			bool operator==(const tree_iterator<Key, T, Compare, Allocator>& other)
			{
				return (this->_root == other._root) && (this->_current == other._current);
			}

			bool operator==(const tree_const_iterator& other)
			{
				return (this->_root == other._root) && (this->_current == other._current);
			}

			bool operator!=(const tree_const_iterator& other)
			{
				return (this->_root != other._root) || (this->_current != other._current);
			}
	};


} // namespace ft

#endif