#ifndef MAP_HPP
 #define MAP_HPP

#include "iterator.hpp"
#include "tree.hpp"
#include "utils.hpp"

namespace ft {

	template < typename Key, typename T, typename Compare = std::less<Key>,	
			typename Allocator = std::allocator< ft::pair<const Key, T> > >
	class map {
		public:	// Member types
			typedef Key																	key_type;
			typedef T																	mapped_type;
			typedef ft::pair<const Key, T>												value_type;
			typedef Compare																key_compare;
			typedef Allocator															allocator_type;
			typedef std::size_t															size_type;
			typedef ptrdiff_t															difference_type;
			typedef value_type&															reference;
			typedef const value_type&													const_reference;
			typedef value_type*															pointer;
			typedef const value_type*													const_pointer;
			typedef typename ft::avl_tree<Key, T, Compare, Allocator>::iterator			iterator;
			typedef typename ft::avl_tree<Key, T, Compare, Allocator>::const_iterator	const_iterator;
			typedef ft::reverse_iterator<iterator>										reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>								const_reverse_iterator;
			

		private: // member variable
			typedef	ft::avl_tree<Key, T, Compare, Allocator>	tree_type;
			tree_type											_tree;

			class value_compare
			{
				friend class map;
				public:
					typedef bool		result_type;
					typedef value_type	first_argument_type;
					typedef value_type	second_argument_type;
				protected:
					key_compare comp;

				public:
					bool operator()(const value_type& x, const value_type& y) const
					{
						return key_compare()(x.first, y.first);
					}
			};

		public: // Member functions
			// Constuctor & Destructor
			map() : _tree(tree_type()) { }

			explicit map(const Compare& comp, const Allocator& alloc = Allocator()) : _tree(tree_type(alloc)) { (void)comp; }

			template<class InputIt>
			map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
				: _tree(tree_type(alloc))
			{
				(void)comp;
				while (first != last)
					this->_tree.insert(*first++);
			}
			
			map(const map& other) : _tree(tree_type())
			{
				for (const_iterator it = other.begin(); it != other.end(); ++it)
					this->_tree.insert(*it);
			}
			
			~map() { }
			
			map& operator=(const map& other)
			{
				this->clear();
				for (const_iterator it = other.begin(); it != other.end(); ++it)
					this->_tree.insert(*it);
				return *this;
			}
			
			// Iterators
			iterator begin() { return _tree.begin(); }
			iterator end() { return _tree.end(); }
			const_iterator begin() const { return _tree.begin(); }
			const_iterator end() const { return _tree.end(); }
			reverse_iterator rbegin() { return reverse_iterator(this->end()); }
			reverse_iterator rend() { return reverse_iterator(this->begin()); }

			// Capacity
			bool empty() const { return this->size() == 0; }
			size_type size() const { return this->_tree.size(); }
			size_type max_size() const { return this->_tree.max_size(); }

			// Element access
			mapped_type& at(const Key& key) { return this->_tree.find(key).second; }
			const mapped_type& at(const Key& key) const { return this->_tree.find(key).second; }
			mapped_type& operator[](const Key& key) 
			{
				this->_tree.insert(key, mapped_type());
				return this->_tree.find(key).second;
			}

			// Modifiers
			ft::pair<iterator, bool> insert(const value_type& value)
			{
				bool result = this->_tree.insert(value);
				iterator it = iterator(_tree.root(), this->_tree.find_node(value.first));
				return ft::make_pair(it, result);
			}

			iterator insert(iterator hint, const value_type& value)
			{
				(void)hint;
				this->_tree.insert(value);
				return iterator(_tree.root(), this->_tree.find_node(value.first));
			}

			template<class InputIt>
			void insert(InputIt first, InputIt last)
			{
				while (first != last)
					this->_tree.insert(*first++);
			}

			void erase(iterator pos) { this->_tree.remove(pos->first); }

			void erase(iterator first, iterator last)
			{
				while (first != iterator(this->_tree.root(), last.current_node()))
				{
					iterator next = first + 1;
					this->erase(first);
					first = iterator(this->_tree.root(), next.current_node());
				}
			}
			
			size_type erase(const Key& key)
			{
				size_type ret = (_tree.find_node(key) != NULL);
				this->_tree.remove(key);
				return ret;
			}

			void swap(map& other) { this->_tree.swap(other._tree); }
			void clear() { this->_tree.clear(); }


			// Observers
			key_compare key_comp() const { return key_compare(); }
			value_compare value_comp() const { return value_compare(); }

			// Operations
			size_type count(const Key& key) const { return this->_tree.find_node(key) ? 1 : 0; }
			iterator find(const Key& key) { return iterator(this->_tree.root(), this->_tree.find_node(key)); }
			const_iterator find(const Key& key) const { return const_iterator(this->_tree.root(), this->_tree.find_node(key)); }
			ft::pair<iterator,iterator> equal_range(const Key& key) { return ft::make_pair(lower_bound(key), upper_bound(key)); } 

			ft::pair<const_iterator,const_iterator> equal_range(const Key& key) const 
			{ 
				return ft::make_pair(lower_bound(key), upper_bound(key)); 
			}

			iterator lower_bound(const Key& key)
			{
				iterator v = this->find(key);
				if (v == this->end())
					return iterator(this->_tree.root(), this->_tree.upper(key));
				return v;
			}
			
			const_iterator lower_bound(const Key& key) const
			{
				const_iterator v = this->find(key);
				if (v == this->end())
					return const_iterator(this->_tree.root(), this->_tree.upper(key));
				return v;
			}

			iterator upper_bound(const Key& key) { return iterator(this->_tree.root(), this->_tree.upper(key)); }
			const_iterator upper_bound(const Key& key) const { return const_iterator(this->_tree.root(), this->_tree.upper(key)); }

			// Allocator
			allocator_type get_allocator() const { return allocator_type(); }
			
			// Non-member functions
			friend void swap( map& lhs, map& rhs ) { lhs.swap(rhs); }

			friend bool operator==(const map& lhs,const map& rhs)
			{
				if (lhs.size() != rhs.size()) 
					return false;
				return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
			}
			friend bool operator!=(const map& lhs,const map& rhs) { return !(lhs == rhs); }
			friend bool operator<(const map& lhs, const map& rhs) 
			{ 
				return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
			}
			friend bool operator<=(const map& lhs, const map& rhs) { return !(lhs > rhs); }
			friend bool operator>(const map& lhs, const map& rhs) { return (rhs < lhs); }
			friend bool operator>=(const map& lhs, const map& rhs) { return !(lhs < rhs); }
	};


}
#endif