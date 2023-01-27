#ifndef STACK_HPP
# define STACK_HPP

#include "./../vector/vector.hpp"

namespace ft {
	/*The std::stack class is a container adaptor that gives the programmer the 
	functionality of a stack - specifically, a LIFO (last-in, first-out) data structure.*/
	template<typename T, typename Container = ft::vector<T> >
	class stack {
	private:
		typedef Container 							container_type;
		typedef typename Container::value_type 		value_type;
		typedef typename Container::size_type    	size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;
	private:
		container_type	_cont;
	public:
		//Default constructor. Value-initializes the container.
		explicit stack(const Container& cont = Container()): _cont(cont) {};

		/*Destructs the stack. The destructors of the elements are called and the used storage is deallocated.
		Note, that if the elements are pointers, the pointed-to objects are not destroyed.*/
		~stack() {};

		//Replaces the contents of the container adaptor with those of other.
		//Copy assignment operator. Replaces the contents with a copy of the contents of other.
		stack& operator=(const stack& other) {
			if (this != &other) {
				_cont = other._cont;
			}
			return *this;
		}

		//Returns reference to the top element in the stack.
		//This is the most recently pushed element. This element will be removed on a call to pop().
		reference top() {
			return _cont.back();
		}

		//Checks if the underlying container has no elements.
		bool empty() const {
			return _cont.empty();
		}

		//Returns the number of elements in the underlying container
		size_type size() const {
			return _cont.size();
		}

		//Pushes the given element value to the top of the stack.
		void push(const value_type& value) {
			_cont.push_back(value);
		}

		//Removes the top element from the stack. Effectively calls 
		void pop() {
			_cont.pop_back();
		}

		template<class T2, class Container2>
		friend bool operator==(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

		template<class T2, class Container2>
		friend bool operator!=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

		template<class T2, class Container2>
		friend bool operator<(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

		template<class T2, class Container2>
		friend bool operator<=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);

		template<class T2, class Container2>
		friend bool operator>(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);
		
		template<class T2, class Container2>
		friend bool operator>=(const ft::stack<T2,Container2>& lhs, const ft::stack<T2,Container2>& rhs);
	};

	template<class T, class Container>
	bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return lhs._cont == rhs._cont;
	}

	template<class T, class Container>
	bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return lhs._cont != rhs._cont;
	}
	
	template<class T, class Container>
	bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs._cont < rhs._cont;
	}
	
	template<class T, class Container>
	bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs._cont <= rhs._cont;
	}

	template<class T, class Container>
	bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs._cont > rhs._cont;
	}
	
	template<class T, class Container>
	bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs ) {
		return lhs._cont >= rhs._cont;
	}
};

#endif
