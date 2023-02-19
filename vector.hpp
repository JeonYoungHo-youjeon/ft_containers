#ifndef VECTOR_HPP
 #define VECTOR_HPP

 #include <memory>
 #include "iterator.hpp"
 #include "utils.hpp"

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:	// Member types
			typedef T												value_type;
			typedef Alloc											allocator_type;
			typedef value_type&										reference;
			typedef const value_type&								const_reference;
			typedef value_type*										pointer;
			typedef const value_type*								const_pointer;
			typedef ft::random_access_iterator<value_type>          iterator; 
			typedef ft::random_access_iterator<const value_type>    const_iterator;
			typedef ft::reverse_iterator<iterator>                  reverse_iterator; 
			typedef ft::reverse_iterator<const_iterator>            const_reverse_iterator;
			typedef typename std::ptrdiff_t		                    difference_type;
			typedef typename std::size_t							size_type;

		private: // member variable
			allocator_type	_alloc;
			pointer			_start;
			pointer			_end;
			pointer			_cap;

			void _init_(size_type n)
			{
				_start = _alloc.allocate(n);
				_end = _start;
				_cap = _start + n;
			}

		public: // Member functions
			// Constuctor & Destructor
			explicit vector (const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(0), _end(0), _cap(0)
			{ }

			explicit vector	(size_type n, const value_type& val = value_type(),
				 			 const allocator_type& alloc = allocator_type())
			: _alloc(alloc), _start(0), _end(0),_cap(0)
			{
				_init_(n);
				for (; n; ++_end, --n) 
					_alloc.construct(_end, val);
			}

			template <class InputIterator>
			vector (InputIterator first, InputIterator last,
					const allocator_type& alloc = allocator_type(),
					typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			: _alloc(alloc)
			{
				difference_type n = ft::distance(first, last);
				_init_(n);
				for (; first != last; ++_end, --n, ++first) 
					_alloc.construct(_end, *first);
			}

			vector (const vector& x)
			:_alloc(x._alloc), _start(0), _end(0),_cap(0)
			{
				this->insert(this->begin(), x.begin(), x.end());
			}

			~vector()
			{
				this->clear();
				_alloc.deallocate(_start, this->capacity());
			}

			vector &operator=(const vector& x)
			{
				if (x == *this)
					return (*this);
				this->clear();
				this->insert(this->end(), x.begin(), x.end());
				return (*this);
			}


			// Iterators
			iterator 				begin() { return _start; };
			const_iterator			begin() const { return _start; }
			iterator				end() { return _end; }
			const_iterator			end() const { return _end; }
			reverse_iterator		rbegin(void) { return reverse_iterator(end()); }
			const_reverse_iterator	rbegin(void) const { return reverse_iterator(end()); }
			reverse_iterator		rend(void) { return reverse_iterator(begin()); }
			const_reverse_iterator	rend(void) const { return reverse_iterator(begin()); }


			// Capacity
			size_type	size(void) const { return _end - _start; }
			size_type	max_size(void) const { return _alloc.max_size(); }
			void		resize (size_type n, value_type val = value_type())
			{
				if (n > this->max_size())
					throw (std::length_error("ERROR - vector::resize"));
				
				if (this->size() > n)
				{
					size_type tmp_size = this->size();
					while (tmp_size > n)
					{
						--_end;
						_alloc.destroy(_end);
						--tmp_size;
					}
				}
				else
					this->insert(this->end(), n - this->size(), val);
			}
			size_type	capacity (void) const { return _cap - _start; }
			bool		empty (void) const { return begin() == end(); }
			void        reserve (size_type n)
			{
				if (n > this->max_size())
					throw (std::length_error("ERROR - vector::reserve"));
				
				if (n > this->capacity())
				{
					pointer tmp_start = _start;
					pointer tmp_end = _end;
					size_type tmp_size = this->size();
					size_type tmp_capacity = this->capacity();
					
					_init_(n);

					while (tmp_start != tmp_end)
					{
						_alloc.construct(_end, *tmp_start);
						_end++;
						tmp_start++;
					}
					_alloc.deallocate(tmp_start - tmp_size, tmp_capacity);
				}
			}


			// Element access
			reference operator[] (size_type n) { return *(_start + n); }
			const_reference operator[] (size_type n) const { return *(_start + n); }
			reference at (size_type n)
			{
				if (size() < n)
					throw std::out_of_range("ERROR - vector::at");
				return (*this)[n];
			}
			reference front () { return *_start; }
			const_reference front () const { return *_start; }
			reference back () { return *(_end - 1); }
			const_reference back () const { return *(_end - 1); }
			value_type* data(void) { return reinterpret_cast<value_type*>(_start); }
			const value_type* data(void) const { return reinterpret_cast<const value_type*>(_start); }


			// Modifiers
			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename enable_if<!ft::is_integral<InputIterator>::value>::type* = 0) 
			{
				size_type n = ft::distance(first, last);
				if (capacity() < n) 
					reserve(n);
				pointer tmp = _start;
				_end = _start + n;
				while (first != last)
					*tmp = *(first++); 
			}

			void assign (size_type count, const T& value)
			{
				clear();
				if (capacity() < count)
					reserve(count);
				while (count--)
					_alloc.construct(_end++, value);
			}

			void push_back (const value_type& val)
			{
				if (_end == _cap)
				{
					if (empty())
						reserve(1);
					else
						reserve(size() * 2);
				}
				_alloc.construct(_end, val);
				_end++;
			}

			void pop_back()
			{
				_alloc.destroy(&back());
				_end--;
			}

			iterator insert (iterator position, const value_type& val)
			{
				size_type n = &(*position) - _start;
				insert(position, 1, val);
				return begin() + n;
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n == 0)
					return ;
				if (n > max_size())
					throw (std::length_error("ERROR - vector::insert"));
				if (capacity() < size() + n) 
					reserve(size() + n);
				size_type tmp = 0;
				while (n > tmp++)
					_alloc.construct(_end++);
				pointer ptr = &(*position);
				pointer tmp_end = _end;
				while (ptr != tmp_end - n)
				{
					*(tmp_end) = *(tmp_end - n);
					tmp_end--;
				}
				tmp = 0;
				while (n > tmp)
					ptr[tmp++] = val;				
			}

			// 입력되는 크기를 받아와서 새로운 크기의 배열을 만들고, 그 다음에 기존의 왼쪽값, 입력값, 오른쪽값 순서로 입력해줌
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0)
			{
				size_type i;

				iterator pbegin, pend;
				pbegin = this->begin();
				pend = this->end();

				size_type _size = size();
				difference_type n = std::distance(first, last);
				size_type _capacity = capacity();
				if (_size + n > _capacity) 
				{
					pointer newStorage;
					size_type newCap;
					newCap = _size + n > _capacity * 2 ? _size + n : _capacity * 2;
					newStorage = _alloc.allocate(newCap);
					for (i = 0; pbegin != position; i++, pbegin++)
						_alloc.construct(&newStorage[i], *pbegin);
					for (; first != last; i++, first++)
						_alloc.construct(&newStorage[i], *first);
					for (; pbegin != pend; i++, pbegin++)
						_alloc.construct(&newStorage[i], *pbegin);
					this->clear();
					if (_capacity)
						_alloc.deallocate(_start, _capacity);
					_start = newStorage;
					_cap = _start + newCap;
					_size = i;
					_end = &newStorage[_size];
				}
				else 
				{
					iterator tmp = position;
					for (size_type i = 1; tmp != pend; i++, tmp++)
						*(pend + n - i) = *(pend - i);
					for (; first != last; first++, position++)
						_alloc.construct(&*position, *first);
					_end += n;
				}
			}

			iterator erase (iterator position)
			{
				size_type n = position - begin();
				pointer ptr = _start + n;
				while (ptr + 1 != _end)
				{
					*ptr = *(ptr + 1);
					ptr++;
				}	
				pop_back();
				return iterator(_start + n);
			}

			iterator erase (iterator first, iterator last)
			{
				size_type n = ft::distance(first, last);
				while (last != end())
					*(first++) = *(last++);
				while (n--)
					pop_back();
				return first;
			}

			void swap (vector& x)
			{
				if (this == &x)
					return ;
				pointer tmp_start = x._start;
				pointer tmp_end = x._end;
				pointer tmp_cap = x._cap;
				allocator_type tmp_alloc = x._alloc;
				x._start = this->_start;
				x._end = this->_end;
				x._cap = this->_cap;
				x._alloc = this->_alloc;
				this->_start = tmp_start;
				this->_end = tmp_end;
				this->_cap = tmp_cap;
				this->_alloc = tmp_alloc;
			}

			void clear()
			{
				while (_start != _end)
					pop_back();				
			}


			// Allocator
			allocator_type get_allocator(void) const { return _alloc; }
			
			// Non-member function overloads
			friend bool operator==(const vector& lhs, const vector& rhs) 
			{
				if (lhs.size() != rhs.size())
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
			friend bool operator!= (const vector& lhs, const vector& rhs) { return (!(lhs == rhs)); }
			friend bool operator<  (const vector& lhs, const vector& rhs) { return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); }
			friend bool operator<= (const vector& lhs, const vector& rhs) { return (!(rhs < lhs)); }
			friend bool operator>  (const vector& lhs, const vector& rhs) { return (rhs < lhs); }
			friend bool operator>= (const vector& lhs, const vector& rhs) { return (!(lhs < rhs)); }

			friend void swap (vector<T,Alloc>& x, vector<T,Alloc>&y) { x.swap(y); }
	};


} // namespace ft


#endif