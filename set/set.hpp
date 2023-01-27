#ifndef SET_HPP
#define SET_HPP

#include "./../red_black_tree/red_black_tree.hpp"
#include "./../utils/pair.hpp"
#include "./../iterators/tree_iterator.hpp"
#include "./../iterators/reverse_tree_iterator.hpp"

namespace ft {
    template<typename Key, typename Compare = std::less<Key>,
    typename Allocator = std::allocator<Key> >
    class set {
    public:
        typedef Key										key_type;
        typedef Key										value_type;
		typedef size_t									size_type;
		typedef	std::ptrdiff_t							defference_type;			
		typedef Compare									key_compare;
		typedef Compare									value_compare;
		typedef Allocator								allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_iterator<const value_type>			const_iterator;
		typedef reverse_tree_iterator<value_type>		reverse_iterator;
		typedef reverse_tree_iterator<const value_type>	const_reverse_iterator;
		
		typedef ft::red_black_tree<value_type, value_compare, allocator_type> red_black_tree;

	public:
		red_black_tree	_tree;
		key_compare		_comp;
	public:

		set() {};

		template <class InputIt>
		set(InputIt first, InputIt last, const Compare& comp = Compare(),
			const Allocator& alloc = Allocator())
			: _tree(first, last, value_compare(comp), alloc), _comp(comp) {};

		set(const set& other): _comp(other._comp) {
			_tree = other._tree;
		};

		~set() {};

		set& operator=(const set& other) {
			if (this != &other) {
				this->_tree = other._tree;
				_comp = other._comp;
			}
			return *this;
		}

		allocator_type get_allocator() const {
			return _tree.get_alloc();
		}


		iterator begin() {
			return _tree.begin();
		}

		iterator end() {
			return _tree.end();
		}

		const_iterator begin() const{
			return _tree.begin();
		}

		const_iterator end() const{
			return _tree.end();
		}

		reverse_iterator rbegin() {
			return _tree.rbegin();
		}

		reverse_iterator rend() {
			return _tree.rend();
		}

		const_reverse_iterator rbegin() const{
			return _tree.rbegin();
		}

		const_reverse_iterator rend() const{
			return _tree.rend();
		}

		bool empty() const {
			return (_tree.size() == 0);
		}

		size_type size() const { 
			return _tree.size();
		}

		size_type max_size() const {
			return _tree.max_size();
		}

		void clear() {
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type& value) {
			return _tree.insert(value);
		}

		iterator insert(iterator pos, const value_type& value) {
			return iterator(_tree.insert(pos, value));
		}

		template< class InputIt >
		void insert(InputIt first, InputIt last) {
			for (InputIt it = first; it != last; ++it) {
				_tree.insert(*it);
			}
		}

		void erase(iterator pos) {
			_tree.erase(pos.get_node()->_key);
		}

		void erase(iterator first, iterator last) {
			for (iterator it = first; it != last; ++it) {
				_tree.erase(*it);
			}
		}

		size_type erase(const Key& key) {
			return _tree.erase(key);
		}

		void swap(set& other) {
			_tree.swap(other._tree);
			std::swap(this->_comp, other._comp);
		}

		iterator find(const Key& key) {
			return _tree.find(key);
		}

		const_iterator find( const Key& key ) const {
			return _tree.find(key);
		}

		key_compare key_comp() const {
			return _comp;
		}

		set::value_compare value_comp() const {
			return _tree.value_comp();
		}

		size_type count( const Key& key ) const {
			return (_tree.count(key) == NULL) ? 0 : 1;
		}

		iterator lower_bound( const Key& key ) {
			return _tree.lower_bound(key);
		}

		const_iterator lower_bound( const Key& key ) const {
			return _tree.lower_bound(key);
		}

		iterator upper_bound( const Key& key ) {
			return _tree.upper_bound(key);
		}

		const_iterator upper_bound( const Key& key ) const {
			return _tree.upper_bound(key);	
		}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			return _tree.equal_range(key);
		}

    };

	template< class Key, class Compare, class Alloc >
	bool operator==( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return lhs._tree == rhs._tree;
	}

	template< class Key, class Compare, class Alloc >
	bool operator!=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs._tree == rhs._tree);
	}

	template< class Key, class Compare, class Alloc >
	bool operator<( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return lhs._tree < rhs._tree;
	}

	template< class Key, class Compare, class Alloc >
	bool operator<=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return (lhs._tree < rhs._tree || lhs._tree == rhs._tree);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs <= rhs);
	}

	template< class Key, class Compare, class Alloc >
	bool operator>=( const ft::set<Key,Compare,Alloc>& lhs,
					const ft::set<Key,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template< class Key, class Compare, class Alloc >
	void swap( ft::set<Key,Compare,Alloc>& lhs,
			ft::set<Key,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif