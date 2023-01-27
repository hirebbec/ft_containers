#ifndef VECTOR_HPP
# define VECTOR_HPP

#include <iostream>
#include <vector>
#include "./../iterators/random_iterator.hpp"
#include "./../iterators/reverse_random_iterator.hpp"
#include <sstream>

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()


namespace ft {
    template<typename T, typename Allocator = std::allocator<T> >
    class vector {
	public:
        typedef	T												value_type;
        typedef	Allocator										allocator_type;
        typedef	size_t											size_type;
        typedef	std::ptrdiff_t									difference_type;
        typedef	value_type&										reference;
        typedef	const value_type&								const_reference;
        typedef	value_type*										pointer;
        typedef	typename Allocator::const_pointer				const_pointer;
        typedef ft::random_iterator<value_type>					iterator;
        typedef ft::random_iterator<const value_type>			const_iterator;
        typedef ft::reverse_random_iterator<value_type>			reverse_iterator;
		typedef ft::reverse_random_iterator<const value_type>	const_reverse_iterator;
	private:
		Allocator	_alloc;
		pointer		_array;
		size_type	_capacity;
		size_type	_size;
	public:
		//Default constructor. Constructs an empty container with a default-constructed allocator.
		vector(): _array(NULL), _capacity(0), _size(0) {};

		//Constructs an empty container with the given allocator alloc.
		explicit vector(const Allocator& alloc): _alloc(alloc), _array(NULL), _capacity(0), _size(0) {};

		//Constructs the container with count copies of elements with value value.
		explicit vector(size_type count, const T& value = T(),
                const Allocator& alloc = Allocator()): _alloc(alloc), _array(_alloc.allocate(count)), _capacity(count), _size(count) {
			for (size_type i = 0; i < count; ++i) {
				try {
					_alloc.construct((_array + i), value);
				} catch (...) {
					for (size_type j = 0; j < i; ++j) {
						_alloc.destroy(_array + j);
					}
					_alloc.deallocate(_array, _capacity);
					_capacity = 0;
					_size = 0;
					throw;
				}
			}
		}

		//Copy constructor. Constructs the container with the copy of the contents of other.
		vector(const vector& other): _array(_alloc.allocate(other._capacity)), _capacity(other._capacity), _size(other._size) {
			for (size_type i = 0; i < other._size; ++i) {
				try {
					_alloc.construct((_array + i), *(other._array + i));
				} catch (...) {
					for (size_type j = 0; j < i; ++j) {
						_alloc.destroy(_array + j);
					}
					_alloc.deallocate(_array, _capacity);
					_capacity = 0;
					_size = 0;
					throw;
				}
			}
		}

		//Constructs the container with the contents of the range [first, last).
		template<class InputIt>
		vector(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last,
				const Allocator& alloc = Allocator()): _alloc(alloc), _array(NULL), _capacity(0), _size(0) {
			difference_type n = last - first;
			if (n < 0)
				throw std::length_error("vector");
			if (n == 0)
				return;
			_size = n;
			_capacity = n;
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < _size; ++i) {
				try {
					_alloc.construct(_array + i, *(first + i));
				} catch (...) {
					for (size_type j = 0; j < i; ++j) {
						_alloc.destroy(_array + j);
					}
					_alloc.deallocate(_array, _capacity);
					_size = 0;
					_capacity = 0;
				}
			}
		}

		//Destructor
		~vector() {
			if (_array != NULL) {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				_alloc.deallocate(_array, _capacity);
			}
		}

		//Copy assignment operator
		vector& operator=(const vector& other) {
			if (this != &other) {
				size_type new_cap = (_capacity > other._capacity) ? _capacity : other._capacity;
				value_type* _newarray = _alloc.allocate(new_cap);
				for (size_type i = 0; i < other._size; ++i) {
					try {
						_alloc.construct((_newarray + i), *(other._array + i));
					} catch (...) {
						for (size_type j = 0; j < i; ++j) {
							_alloc.destroy(_newarray + j);
						}
						_alloc.deallocate(_newarray, new_cap);
						throw;
					}
				}
				if (_array != NULL) {
					for (size_type i = 0; i < _size; ++i) {
						_alloc.destroy(_array + i);
					}
					_alloc.deallocate(_array, _capacity);
				}
				_array = _newarray;
				_capacity = new_cap;
				_size = other._size;
			}
			return *this;
		}

		//Replaces the contents with count copies of value value
		void assign(size_type count, const T& value) {
			if (count < _capacity) {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				for (size_type i = 0; i < count; ++i) {
					_alloc.construct((_array + i), value);
				}
				_size = count;
			} else {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(count);
				_capacity = count;
				_size = count;
				for (size_type i = 0; i < count; ++i) {
					_alloc.construct((_array + i), value);
				}
			}
		}

		/*Replaces the contents with copies of those in the range [first, last).
		The behavior is undefined if either argument is an iterator into *this.*/
		template<class InputIt>
		void assign(typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
			reserve(last - first);
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_array + i);
			}
			for (size_type i = 0; i < _size; ++i) {
				_alloc.construct(_array + i, *(first + i));
			}
			_size = last - first;
		}

		//Returns the allocator associated with the container.
		allocator_type get_allocator() const {
			return _alloc;
		}

		//Returns a reference to the element at specified location pos, with bounds checking.
		//If pos is not within the range of the container, an exception of type std::out_of_range is thrown.
		reference at(size_type pos) {
			if (pos >= _size) {
				throw std::out_of_range(SSTR("vector::_M_range_check: __n (which is " << pos << ") >= this->size() (which is " << _size << ")"));
			}
			return *(_array + pos);
		}

		const_reference at( size_type pos ) const {
			if (pos >= _size) {
				throw std::out_of_range("vector::_M_range_check: __n  >= this->size()");
			}
			return *(_array + pos);
		}

		//Returns a reference to the element at specified location pos. No bounds checking is performed.
		reference operator[]( size_type pos ) {
			return *(_array + pos);
		}

		const_reference operator[]( size_type pos ) const {
			return *(_array + pos);
		}

		//Returns a reference to the first element in the container.
		//Calling front on an empty container is undefined.
		reference front() {
			return *_array;
		}

		const_reference front() const {
			return *_array;
		}

		//Returns a reference to the last element in the container.
		//Calling back on an empty container causes undefined behavior.
		reference back() {
			return *(_array + _size - 1);
		}

		const_reference back() const {
			return *(_array + _size - 1);
		}

		/*Returns pointer to the underlying array serving as element storage. 
		The pointer is such that range [data(); data()+size()) is always a valid range, 
		even if the container is empty (data() is not dereferenceable in that case).*/
		T* data() {
			return _array;
		}

		const T* data() const {
			return _array;
		}

		iterator begin() {
			return _array;
		}

		iterator end() {
			return _array + _size;
		}

		const iterator begin() const{
			return _array;
		}

		const iterator end() const {
			return _array + _size;
		}

		reverse_iterator rbegin() {
			return _array + _size - 1;
		}

		reverse_iterator rend() {
			return _array - 1;
		}

		const reverse_iterator rbegin() const{
			return _array + _size - 1;
		}

		const reverse_iterator rend() const {
			return _array - 1;
		}

		//Checks if the container has no elements.
		bool empty() const {
			return _size == 0 ? 1 : 0; 
		}

		//Returns the number of elements in the container
		size_type size() const {
			return _size;
		}

		//Returns the maximum number of elements the container is able to hold due to system or library implementation limitations.
		size_type max_size() const {
			return _alloc.max_size();
		}

		/*Increase the capacity of the vector (the total number of elements that the vector can hold without requiring reallocation)
		to a value that's greater or equal to new_cap. If new_cap is greater than the current capacity(),
		new storage is allocated, otherwise the function does nothing.

		reserve() does not change the size of the vector.

		If new_cap is greater than capacity(), all iterators, including the past-the-end iterator,
		and all references to the elements are invalidated. Otherwise, no iterators or references are invalidated.*/
		void reserve(size_type new_cap) {
			if (new_cap < _capacity)
				return;
			if (new_cap > max_size()) {
				throw std::length_error("new_cap > max_size");
			}
			value_type* newarray = _alloc.allocate(new_cap);
			for (size_type i = 0; i < _size; ++i) {
				try {
					_alloc.construct(newarray + i, *(_array + i));
				} catch (...) {
					for (size_type j = 0; j < i; ++j) {
						_alloc.destroy(newarray + j);
					}
					_alloc.deallocate(newarray, new_cap);
					throw;
				}
			}
			if (_array != NULL) {
				for (size_type i = 0; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				_alloc.deallocate(_array, _capacity);
			}
			_array = newarray;
			_capacity = new_cap;
		}
		
		//Returns the number of elements that the container has currently allocated space for.
		size_type capacity() const {
			return _capacity;
		}

		/*Erases all elements from the container. After this call, size() returns zero.
		
		Invalidates any references, pointers, or iterators referring to contained elements.
		Any past-the-end iterators are also invalidated.  
		
		Leaves the capacity() of the vector unchanged.*/
		void clear() {
			for (size_type i = 0; i < _size; ++i) {
				_alloc.destroy(_array + i);
			}
			_size = 0;
		}

		//Inserts elements at the specified location in the container.
		//inserts value before pos.
		/*Causes reallocation if the new size() is greater than the old capacity().
		If the new size() is greater than capacity(), all iterators and references are invalidated. 
		Otherwise, only the iterators and references before the insertion point remain valid.
		The past-the-end iterator is also invalidated.*/
		iterator insert(const_iterator pos, const T& value) {
			difference_type n = pos - _array;
			if (_size >= _capacity) {
				if (_capacity == 0)
					reserve(1);
				else 
					reserve(_capacity * 2);
			}
			for (size_type i = n; i < _size + 1; ++i) {
				_alloc.construct(_array + i + 1, *(_array + i));
				_alloc.destroy(_array + i);
			}
			_alloc.construct(_array + n, value);
			++_size;
			return (_array + n);
		}

		//inserts count copies of the value before pos.
		iterator insert(const_iterator pos, size_type count, const T& value) {
			difference_type n = pos - _array;
			while (_size + count > _capacity) {
				if (_capacity == 0)
					reserve(1);
				else 
					reserve(_capacity * 2);
			}
			for (size_type i = n; i < _size + count; ++i) {
				_alloc.construct(_array + count + i, *(_array + i));
				_alloc.destroy(_array + i);
			}
			for (size_type i = 0; i < count; ++i) {
				_alloc.construct(_array + i + n, value);
			}
			_size += count;
			return (_array + n);
		}

		//inserts elements from range [first, last) before pos.
		template< class InputIt >
		iterator insert(const_iterator pos, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type first, InputIt last) {
			difference_type count = last - first;
			difference_type n = pos - _array;
			while (_size + count > _capacity) {
				if (_capacity == 0)
					reserve(1);
				else 
					reserve(_capacity * 2);
			}
			for (size_type i = n; i < _size + count; ++i) {
				_alloc.construct(_array + count + i, *(_array + i));
				_alloc.destroy(_array + i);
			}
			for (size_type i = 0; first != last; ++first) {
				_alloc.construct(_array + i + n, *first);
				i++;
			}
			_size += count;
			return _array + n;
		}

		//Removes the element at pos.
		/*Invalidates iterators and references at or after the point of the erase, including the end() iterator.
		The iterator pos must be valid and dereferenceable.
		Thus the end() iterator (which is valid, but is not dereferenceable) cannot be used as a value for pos.
		The iterator first does not need to be dereferenceable if first == last: erasing an empty range is a no-op.*/
		iterator erase(iterator pos) {
			if (pos == end()) {
				return end();
			}
			value_type *it = &(*pos);
			_alloc.destroy(it);
			for (; it != _array + _size; ++it) {
				_alloc.construct(it, *(it + 1));
				_alloc.destroy(it + 1);
			}
			--_size;
			return pos;
		}

		//Removes the elements in the range [first, last).
		iterator erase(iterator first, iterator last) {
			difference_type count = last - first;
			difference_type n = first - _array;
			for (size_type i = n; i < static_cast<size_type>(n + count); ++i) {
				_alloc.destroy(_array + i);
			}
			for (size_type i = n; i < static_cast<size_type>(_size - count); ++i) {
				_alloc.construct(_array + i, *(_array + i + count));
				_alloc.destroy(_array + i + count);
			}
			_size -= count;
			return _array + n;
		}

		/*Appends the given element value to the end of the container.
		1) The new element is initialized as a copy of value.
		2) value is moved into the new element.
		If the new size() is greater than capacity() then all iterators and references are invalidated.
		Otherwise only the past-the-end iterator is invalidated.*/
		void push_back(const T& value) {
			if (_size >= _capacity) {
				if (_capacity == 0)
					reserve(1);
				else 
					reserve(_capacity * 2);
			}
			try {
				_alloc.construct((_array + _size), value);
			} catch (...) {
				throw;
			}
			++_size;
		}



		/*Removes the last element of the container.
		Calling pop_back on an empty container results in undefined behavior.
		Iterators and references to the last element, as well as the end() iterator, are invalidated.*/ 
		void pop_back() {
			if (empty())
				return;
			_alloc.destroy(_array + _size - 1);
			--_size;
		}

		/*Resizes the container to contain count elements.
		If the current size is greater than count, the container is reduced to its first count elements.
		If the current size is less than count, additional copies of value are appended.*/
		void resize( size_type count, T value = T() ) {
			if (_size <= count) {
				reserve(count);
				for (size_type i = _size; i < count; ++i) {
					try {
						_alloc.construct((_array + i), value);
					} catch (...) {
						for (size_type j = 0; j < i; ++j) {
							_alloc.destroy(_array + j);
						}
						throw;
					}
					_size = count;
				}
			} else {
				for (size_type i = count; i < _size; ++i) {
					_alloc.destroy(_array + i);
				}
				_size = count;
			}
		}

		/*Exchanges the contents of the container with those of other.
		Does not invoke any move, copy, or swap operations on individual elements.
		All iterators and references remain valid. The past-the-end iterator is invalidated. */
		void swap(vector& other) {
			std::swap(_array, other._array);
			std::swap(_size, other._size);
			std::swap(_capacity, other._capacity);
			std::swap(_alloc, other._alloc);
		}
    };

	/*Checks if the contents of lhs and rhs are equal, that is, they have the same number of 
	elements and each element in lhs compares equal with the element in rhs at the same position.*/
	template< class T, class Alloc >
	bool operator==(const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() == rhs.size()) {
			for (size_t i = 0; i < lhs.size(); ++i) {
				if (!(lhs[i] == rhs[i]))
					return false;
			}
			return true;
		}
		return false;
	}

	template< class T, class Alloc >
	bool operator!=(const ft::vector<T,Alloc>& lhs,
				const ft::vector<T,Alloc>& rhs) {
		return !(rhs == lhs);
	}

	//Compares the contents of lhs and rhs lexicographically.
	//The comparison is performed by a function equivalent to std::lexicographical_compare.
	template< class T, class Alloc >
	bool operator<(const ft::vector<T,Alloc>& lhs,
				   const ft::vector<T,Alloc>& rhs) {
		return ft::lexicographical_compare(lhs.begin(), lhs.end(),
			rhs.begin(), rhs.end());
	}

	template <class T, class Allocator>
	bool operator>(const ft::vector<T, Allocator>& lhs,
				const ft::vector<T, Allocator>& rhs) {
		return !(lhs < rhs || lhs == rhs);
	}

	template <class T, class Allocator>
	bool operator<=(const ft::vector<T, Allocator>& lhs,
				const ft::vector<T, Allocator>& rhs) {
		return (lhs < rhs || lhs == rhs);
	}

	template <class T, class Allocator>
	bool operator>=(const ft::vector<T, Allocator>& lhs,
				const ft::vector<T, Allocator>& rhs) {
		return (lhs > rhs || lhs == rhs);
	}

	template <class T, class Allocator>
	void swap(ft::vector<T, Allocator>& lhs, ft::vector<T, Allocator>& rhs) {
		lhs.swap(rhs);
}
};

#endif