#ifndef REVERSE_TREE_ITERATOR_HPP
#define REVERSE_TREE_ITERATOR_HPP

#include "./../utils/iterator_traits.hpp"
#include "./../red_black_tree/node.hpp"

namespace ft {
    template<typename T>
    class reverse_tree_iterator {
    private:
        typedef std::bidirectional_iterator_tag						iterator_category;
        typedef typename ft::iterator_traits<T*>::value_type		value_type;
        typedef typename ft::iterator_traits<T*>::reference			reference;
        typedef typename ft::iterator_traits<T*>::pointer			pointer;
        typedef typename ft::iterator_traits<T*>::difference_type	difference_type;
        typedef ft::node<value_type>*								node_pointer;
        typedef ft::node<T>*										iterator_type;
	private:
		node_pointer	_node;
		bool			_flag;

		node_pointer max(node_pointer begin_node) {
			if (begin_node == NULL)
				return NULL;
			node_pointer tmp = begin_node;
			while (tmp->_rnode != NIL)
				tmp = tmp->_rnode;
			return tmp;
		}

		node_pointer min(node_pointer begin_node) {
			if (begin_node == NULL)
				return NULL;
			node_pointer tmp = begin_node;
			while (tmp->_lnode != NIL)
				tmp = tmp->_lnode;
			return tmp;
		}
		
	public:
		reverse_tree_iterator(): _node(NULL), _flag(false) {};

		reverse_tree_iterator(void* node, bool _flag = false) : _node(static_cast<node_pointer>(node)), _flag(_flag) {}

		reverse_tree_iterator(const reverse_tree_iterator<typename remove_const<value_type>::type>& value) {
			_node = value._node;
			_flag = value._flag;
		}

		virtual ~reverse_tree_iterator() {};

		reverse_tree_iterator& operator=(const reverse_tree_iterator<typename remove_const<value_type>::type>& value) {
			if (this != &value) {
				this->_node = value._node;
				this->_flag = value._flag;
			}
			return *this;
		}

		node_pointer get_node() { return _node; }

		reference operator*() const { return _node->_key; }

		pointer operator->() const { return &(_node->_key); }

		bool check_min(node_pointer node) {
			if (node->_lnode != NULL)
				return false;
			node_pointer tmp  = node;
			while (tmp->_parent != NULL) {
				if (tmp->_parent->_rnode == tmp)
					return false;
				tmp = tmp->_parent;
			}
			return true;
		}

		bool check_max(node_pointer node) {
			if (node->_rnode != NULL)
				return false;
			node_pointer tmp  = node;
			while (tmp->_parent != NULL) {
				if (tmp->_parent->_lnode == tmp)
					return false;
				tmp = tmp->_parent;
			}
			return true;
		}

		reverse_tree_iterator& operator++() {
			if (check_min(_node)) {
				_flag = true;
			}
			else if (_node->_lnode != NIL) {
				_node = max(_node->_lnode);
			} else {
				node_pointer tmp;
				tmp = _node->_parent;
				while (tmp != NULL && _node == tmp->_lnode) {
					_node = tmp;
					tmp = tmp->_parent;
				}
				_node = tmp;
			}
			return *this;
		}

		reverse_tree_iterator& operator--() {
			if (_flag == true)
				_flag = false;
			if (_node->_rnode != NIL) {
				_node = min(_node->_rnode);
			} else {
				node_pointer tmp;
				tmp = _node->_parent;
				while (tmp != NULL  && _node == tmp->_rnode) {
					_node = tmp;
					tmp = tmp->_parent;
				}
				_node = tmp;
			}
			return *this;
		}

		reverse_tree_iterator operator++(int) {
			if (_node->_lnode != NULL)
				_node = max(_node->_lnode);
			else {
				node_pointer tmp;
				tmp = _node->_parent;
				while (tmp != NULL && _node == tmp->_lnode) {
					_node = tmp;
					tmp = tmp->parent;
				}
				_node = _node->parent;
			}
			return *this;
		}

		reverse_tree_iterator operator--(int) {
			if (_node->_rnode != NULL)
				_node = min(_node->_rnode);
			else {
				node_pointer tmp;
				tmp = _node->_parent;
				while (tmp != NULL && _node == tmp->_rnode) {
					_node = tmp;
					tmp = tmp->parent;
				}
				_node = _node->parent;
			}
			return *this;
		}

		bool operator==(const reverse_tree_iterator<T> value) {
			return (_node == value._node && _flag == value._flag);
		}

		bool operator!=(const reverse_tree_iterator<T> value) {
			return !(*this == value);
		}
    };

	template <typename T>
	bool operator==(const reverse_tree_iterator<T> lhs, const reverse_tree_iterator<T> rhs) {
		return (lhs.get_node() == rhs.get_node() && lhs._flag == rhs._flag);
	}

	template <typename T>
	bool operator!=(const reverse_tree_iterator<T> lhs, const reverse_tree_iterator<T> rhs) {
		return !(lhs == rhs);
	}
}

#endif