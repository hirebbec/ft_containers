#ifndef NODE_HPP
# define NODE_HPP

#include <memory>

#define BLACK	0
#define RED		1
#define NIL		NULL

namespace ft {
    template<typename value_type, typename Allocator = std::allocator<value_type> >
    struct node{
    public:
        value_type	_key;
        node*		_parent;
        node*		_lnode;
        node*		_rnode;
		int			_color;
        bool         _end;
        node*       _root;

		node(value_type key) : _key(key), _parent(NIL), _lnode(NIL), _rnode(NIL), _color(RED), _end(false) {};

        node(value_type key, node* parent) : _key(key), _parent(parent), _lnode(NIL), _rnode(NIL), _color(RED), _end(false) {};

        node(node *nil): _key(value_type()) ,_end(true), _root(nil) {};

        ~node(){};

        bool isLeaf() {
            return (_lnode == NULL && _rnode == NULL);
        }

        bool isEnd() {
            return _end;
        }
    };
}

    std::ostream& operator<<(std::ostream &os, ft::node<int> *node) {
        if (node == NULL) {
            return std::cout << "\nNIL\n";
        }
        std::cout << "\nkey = " << node->_key << "\n" << "color = ";
        if (node->_color == 1) {
            std::cout << "red";
        } else {
            std::cout << "black";
        }
        (void)os;
        return std::cout << std::endl;
    }
#endif