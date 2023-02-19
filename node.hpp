#ifndef NODE_HPP
#define NODE_HPP

#include "utils.hpp"

namespace ft 
{

	template< class Key, class T, class Compare, class Allocator >
	class avl_node
	{
		public:
			typedef avl_node<Key, T, Compare, Allocator>	node;
			typedef node*									node_ptr;
			typedef Key										key_type;
			typedef T										value_type;
			typedef ft::pair<Key, T>						pair_type;
			typedef size_t									size_type;
			typedef ssize_t									balance_type;
			typedef Allocator								allocator_type;

		private:
			typedef typename allocator_type::template rebind<node>::other node_allocator;
			// 내부적으로 avl_node<Key, T, Compare, Allocator> 만 전담하는 allocator

			pair_type	_data;
			size_type	_height;
			node_ptr 	left;
			node_ptr 	right;
			Compare		key_compare;

		public:
			avl_node(pair_type data) : _data(data), _height(1), left(NULL), right(NULL) { }
			const key_type& key() const { return this->_data.first; }
			value_type& value() { return this->_data.second; }
			pair_type& key_value_pair() { return this->_data; }

			static size_type height(node *n)
			{
				if (n == NULL) 
					return 0;
				return n->_height;
			}
			
			static balance_type balance(node_ptr n)
			{
				if (n == NULL) 
					return 0;
				return height(n->left) - height(n->right);
			}

			static node_ptr right_rotate(node_ptr y)
			{
				node_ptr x = y->left;
				node_ptr t2 = x->right;

				x->right = y;
				y->left = t2;
				y->_height = std::max(height(y->left), height(y->right)) + 1;
				x->_height = std::max(height(x->left), height(x->right)) + 1;

				return x;
			}

			static node_ptr left_rotate(node_ptr x)
			{
				node_ptr y = x->right;
				avl_node *t2 = y->left;

				y->left = x;
				x->right = t2;
				x->_height = std::max(height(x->left), height(x->right)) + 1;
				y->_height = std::max(height(y->left), height(y->right)) + 1;

				return y;
			}

			static node_ptr find(node_ptr node, key_type key)
			{
				while (node != NULL) 
				{
					if (node->key() == key) 
						return node;
					if (node->key_compare(key, node->key())) 
						node = node->left;
					else if (key > node->key())
						node = node->right;
				}
				return NULL;
			}

			static node_ptr new_node(pair_type data, node_allocator& alloc)
			{
				node_ptr node = alloc.allocate(1);
				alloc.construct(node, data);
				return node;
			}

			static node_ptr insert(node_ptr node, pair_type data, node_allocator& alloc)
			{
				// 노드가 없을경우 생성
				if (node == NULL)
					return(new_node(data, alloc));
				// data 의 key 가 node 의 키보다 작으면 왼쪽으로 이동
				if (data.first < node->key()) 
					node->left = insert(node->left, data, alloc);
				//  data 의 key 가 node 의 키보다 크면 오른쪽으로 이동
				else if (data.first > node->key()) 
					node->right = insert(node->right, data, alloc);
				// 키가 중복될수없기때문에 바로 반환
				else
					return node;

				node->_height = 1 + std::max(height(node->left), height(node->right));

				// 균형을 계산해서 균형이 깨진 경우에 LL RR LR RL 동작을 수행
				int bal = balance(node);

				// 루트의 왼쪽 자식의 왼쪽 서브트리에 노드를 삽입한 경우(LL), 오른쪽으로 회전
				if (bal > 1 && data.first < node->left->key())
					return right_rotate(node);
				// 루트의 오른쪽 자식의 오른쪽 서브트리에 노드를 삽입한 경우(RR), 왼쪽으로 회전
				if (bal < -1 && data.first > node->right->key()) 
					return left_rotate(node);
				// 루트의 왼쪽 자식의 오른쪽 서브트리에 노드를 삽입한 경우(LR), 왼쪽 자식을 왼쪽으로 회전한 후, 루트를 오른쪽으로 회전
				if (bal > 1 && data.first > node->left->key()) 
				{
					node->left = left_rotate(node->left);
					return right_rotate(node);
				}
				// 루트의 오른쪽 자식의 왼쪽 서브트리에 노드를 삽입한 경우(RL), 오른쪽 자식을 오른쪽으로 회전한 후, 루트를 왼쪽으로 회전
				if (bal < -1 && data.first < node->right->key()) 
				{
					node->right = right_rotate(node->right);
					return left_rotate(node);
				}

				return node;
			}

			static node_ptr min(node_ptr node)
			{
				node_ptr current = node;

				while (current->left != NULL) 
					current = current->left;
				return current;
			}

			static node_ptr max(node_ptr node)
			{
				node_ptr current = node;

				while (current->right != NULL) 
					current = current->right;

				return current;
			}

			// 수정된 서브트리의 루트를 반환
			static node_ptr del_node(node_ptr root, key_type key, node_allocator& alloc)
			{
				if (root == NULL)
					return root;

				// 해당 key를 찾기위한 재귀
				if (key < root->key())
					root->left = del_node(root->left, key, alloc);
				else if (key > root->key()) 
					root->right = del_node(root->right, key, alloc);
				// 해당 key 를 찾았을때 / 혹은 찾고자 하는 key가 없을때
				else 
				{
					if ((root->left == NULL) || (root->right == NULL)) 
					{
						node_ptr temp = root->left ? root->left : root->right;

						if (temp == NULL) 
						{
							temp = root;
							root = NULL;
						}
						else
							*root = *temp;
						alloc.destroy(temp);
						alloc.deallocate(temp, 1);
					}
					else // 노드에 자식이 둘일때 오른쪽에서 가장 작은 값을 찾아서 그것과 현재 key를 변경하고, 그 다음에 그 노드를 삭제한다.
					{
						node_ptr temp = min(root->right);
						root->_data = temp->_data;

						root->right = del_node(root->right, temp->key(), alloc);
					}
				}

				if (root == NULL) 
					return root;

				root->_height =	std::max(height(root->left), height(root->right)) + 1;

				int bal = balance(root);

				// Left Left
				if (bal > 1 && balance(root->left) >= 0) 
					return right_rotate(root);
				// Left Right
				if (bal > 1 && balance(root->left) < 0)
				{
					root->left = left_rotate(root->left);
					return right_rotate(root);
				}
				// Right Right
				if (bal < -1 && balance(root->right) <= 0)
					return left_rotate(root);

				// Right Left
				if (bal < -1 && balance(root->right) > 0) 
				{
					root->right = right_rotate(root->right);
					return left_rotate(root);
				}

				return root;
			}

			static node_ptr upper(node_ptr root, key_type key)
			{
				node_ptr current = root;
				node_ptr last_valid = NULL;
				while (current) 
				{
					if (key == current->key()) 
					{
						if (current->right) 
							return min(current->right);
						break ;
					}
					if (root->key_compare(key, current->key())) 
					{
						last_valid = current;
						current = current->left;
					} 
					else 
						current = current->right;
				}
				return (last_valid);
			}

			static node_ptr lower(node_ptr root, key_type key)
			{
				node_ptr current = root;
				node_ptr last_valid = NULL;
				while (current) 
				{
					if (key == current->key()) 
					{
						if (current->left) 
							return max(current->left);
						break ;
					}
					if (root->key_compare(key, current->key())) 
						current = current->left;
					else 
					{
						last_valid = current;
						current = current->right;
					}
				}

				return (last_valid);
			}

			static node_ptr next(node_ptr node, node_ptr root)
			{
				if (node->right)
					return min(node->right);

				return upper(root, node->key());
			}

			static node_ptr prev(node_ptr node, node_ptr root)
			{
				if (node == NULL) 
					return max(root);
				if (node->left) 
					return max(node->left);

				return lower(root, node->key());
			}

	};

}
#endif