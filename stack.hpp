#ifndef STACK_H
# define STACK_H

#include "vector.hpp"

namespace ft
{
	template <typename T, class Container = ft::vector<T> >
	class stack
	{
		public: // Member types
			typedef T				value_type;
			typedef Container		container_type;
			typedef size_t			size_type;

		protected: // Member objects
			container_type	c;
		

		public: // Member functions
			explicit stack (const container_type& ctn = container_type()) : c(ctn) { }
			~stack() { };
			stack& operator=(const stack& rhs)
			{
				if (this == &rhs)
					return *this;
				c = rhs.c;
				return *this;
			}
			
			bool empty() const { return (this->c.empty()); }
			size_type size() const { return (this->c.size()); }
			value_type& top() { return (this->c.back()); }
			const value_type& top() const { return (this->c.back()); }
			void push (const value_type& value) { this->c.push_back(value); }
			void pop() { this->c.pop_back(); }


		// Non-member function overloads
		friend bool operator== (const stack& lhs, const stack& rhs) { return lhs.c == rhs.c; }
		friend bool operator!= (const stack& lhs, const stack& rhs) { return lhs.c != rhs.c; }
		friend bool operator<  (const stack& lhs, const stack& rhs) { return lhs.c <  rhs.c; }
		friend bool operator<= (const stack& lhs, const stack& rhs) { return lhs.c <= rhs.c; }
		friend bool operator>  (const stack& lhs, const stack& rhs) { return lhs.c >  rhs.c; }
		friend bool operator>= (const stack& lhs, const stack& rhs) { return lhs.c >= rhs.c; }
		
	};

} // namespace ft

#endif