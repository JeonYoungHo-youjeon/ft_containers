#ifndef TREE_HPP
#define TREE_HPP

#include "node.hpp"
#include "utils.hpp"


namespace ft {

	template< class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator< ft::pair<const Key, T> > >
	class avl_tree 
	{
		public:
			typedef avl_node<Key, T, Compare, Allocator>						node;
			typedef node*														node_ptr;
			typedef Key															key_type;
			typedef T															value_type;
			typedef ft::pair<Key, T>											pair_type;
			typedef ft::pair<const Key, T>										const_pair_type;
			typedef std::size_t													size_type;
			typedef ptrdiff_t													difference_type;
			typedef Allocator													allocator_type;
			typedef ft::tree_iterator<Key, T, Compare, Allocator>			iterator;
			typedef ft::tree_const_iterator<Key, T, Compare, Allocator>		const_iterator;

		private:
			typedef typename allocator_type::template rebind<node>::other node_allocator;

		private:
			node_allocator	_allocator; // AVL 트리 노드의 메모리 할당을 담당할 allocator
			node_ptr		_root; // AVL 트리의 루트 노드 
			size_type		_size; // AVL 트리의 크기

		public:
			avl_tree(allocator_type alloc = allocator_type()) : _allocator(alloc), _root(NULL), _size(0) { }
			~avl_tree() { this->clear(); }

			node_ptr root() { return _root; }

			void swap(avl_tree& other)
			{
				ft::swap(this->_allocator, other._allocator);
				ft::swap(this->_root, other._root);
				ft::swap(this->_size, other._size);
			}
			
			iterator begin()
			{
				if (this->_size == 0) // 빈 경우 end 반환
					return this->end();

				return iterator(this->_root, this->min());
			}
			iterator end() { return iterator(this->_root, NULL); }
			
			const_iterator begin() const
			{
				if (this->_size == 0) // 빈 경우 end 반환
					return this->end();

				return const_iterator(this->_root, this->min());
			}
			const_iterator end() const { return const_iterator(this->_root, NULL); }
			
			bool insert(pair_type data)
			{
				// 삽입하려는 키가 이미 AVL 트리에 존재하는 경우, 삽입하지 않고 false 반환
				if (node::find(this->_root, data.first) != NULL) 
					return false;
				this->_root = node::insert(this->_root, data, _allocator);
				this->_size++;

				return true;
			}

			bool insert(key_type key, value_type value) { return insert(ft::make_pair(key, value)); }

			void remove(const key_type& key)
			{
				if (node::find(this->_root, key) == NULL) // 해당 키가 없으면 동작하지 않음
					return ;
				this->_root = node::del_node(this->_root, key, _allocator);
				this->_size--;
			}

			size_type size() const { return this->_size; }

			// tree 가장 왼쪽의 노드 반환
			node_ptr min() const 
			{
				if (this->_root == NULL) 
					throw std::out_of_range("Map : empty");

				return node::min(this->_root);
			}

			// tree 가장 오른쪽의 노드 반환
			node_ptr max() const 
			{
				if (this->_root == NULL) 
					throw std::out_of_range("Map : empty");

				return node::max(this->_root);
			}

			// 주어진 key보다 큰 node중 가장 작은 node 반환. 없을경우 NULL
			node_ptr upper(const key_type& key) const
			{
				return node::upper(this->_root, key);
			}

			// 주어진 node의 바로 다음 노드를 반환.
			node_ptr next(node_ptr node) { return node::next(node, _root); }

			const_pair_type& find(const key_type& key) const
			{
				node_ptr node = node::find(this->_root, key);
				if (node == NULL) 
					throw std::out_of_range("map - find");

				return reinterpret_cast<const_pair_type&>(node->key_value_pair());
			}

			node_ptr find_node(const key_type& key) const
			{
				node_ptr node = node::find(this->_root, key);

				return node;
			}

			void clear()
			{
				size_type size = _size;
				for (size_type i = 0; i < size; ++i) 
					remove(_root->key());
			}

			size_type max_size() const
			{
				return std::min(_allocator.max_size(), static_cast<size_type>(std::numeric_limits<difference_type>::max()));
			}
	};

}
#endif