#ifndef RANDOM_ITERATOR_HPP
# define RANDOM_ITERATOR_HPP

#include <cstddef>
#include <string>
#include "./../utils/iterator_traits.hpp"
#include "./../utils/enable_if.hpp"
#include "./../utils/lexicographical_compare.hpp"
#include "./../utils/is_integral.hpp"

//https://cplusplus.com/reference/iterator/
namespace ft {
    template<typename Iter>
    class random_iterator
    {
    public:
        typedef typename std::random_access_iterator_tag                iterator_category;
        typedef typename ft::iterator_traits<Iter*>::value_type         value_type;
        typedef typename ft::iterator_traits<Iter*>::difference_type    difference_type;
        typedef typename ft::iterator_traits<Iter*>::pointer            pointer;
        typedef typename ft::iterator_traits<Iter*>::reference          reference;
        typedef pointer                                                 iterator_type;
        pointer _element;
    
    

    public:
        random_iterator() : _element(NULL) {_element = 0;}

        random_iterator(pointer element) : _element(element) {};

        random_iterator(const random_iterator* other) : _element(other->_element) {};

        random_iterator(const random_iterator<typename ft::remove_const<value_type>::type > & value) : _element(&(*value)) {}

        random_iterator& operator=(const random_iterator<Iter>& other) {
            if (this != &other) {
                _element = other._element;
            }
            return *this;
        }

        bool operator==(const random_iterator<Iter>& other) {
            return _element == other._element;
        }

        bool operator!=(const random_iterator<Iter>& other) {
            return _element != other._element;
        }

        reference operator*() const {
            return *_element;
        }

        pointer operator->() const {
            return &(*_element);
        }

        random_iterator& operator++() {
            ++_element;
            return *this;
        }

        random_iterator operator++(int) {
            random_iterator tmp(*this);
            _element++;
            return tmp;
        }

        random_iterator& operator--() {
            --_element;
            return *this;
        }

        random_iterator operator--(int) {
            random_iterator tmp(*this);
            _element--;
            return tmp;
        }

        difference_type operator-(const random_iterator<Iter> value) const {
            return (_element - value._element);
        };

        difference_type operator+(const random_iterator<Iter> value) const {
            return (_element + value._element);
        };

        random_iterator operator+(const difference_type n) const {
            random_iterator tmp(_element + n);
            return tmp;
        }

        random_iterator operator-(const difference_type n) const {
            random_iterator tmp(_element - n);
            return tmp;
        }

        bool operator<(const random_iterator& other) {
            return (_element < other._element);
        }

        bool operator>(const random_iterator& other) {
            return (_element > other._element);
        }

        bool operator<=(const random_iterator& other) {
            return (_element <= other._element);
        }

        bool operator>=(const random_iterator& other) {
            return (_element >= other._element);
        }

        reference operator[](difference_type n) {
            return *(_element + n);
        }

        ~random_iterator() {};
    };

    template<typename T>
    random_iterator<T> operator+(int n, const random_iterator<T>& value) {
        random_iterator<T> tmp(value._element + n);
        return tmp;
    }

    template<typename T>
    random_iterator<T> operator-(int n, const random_iterator<T>& value) {
        random_iterator<T> tmp(value._element - n);
        return tmp;
    }
};

#endif