#ifndef MAP_HPP
#define MAP_HPP

#include "./../red_black_tree/red_black_tree.hpp"
#include "./../utils/pair.hpp"
#include "./../iterators/tree_iterator.hpp"
#include "./../iterators/reverse_tree_iterator.hpp"

namespace ft {
    template<typename Key, typename T, typename Compare = std::less<Key>,
    typename Allocator = std::allocator<ft::pair<const Key, T> > >
    class map {
    public:
        typedef Key										key_type;
        typedef T										mapped_type;
        typedef ft::pair<const Key, T>					value_type;
		typedef size_t									size_type;
		typedef	std::ptrdiff_t							defference_type;			
		typedef Compare									key_compare;
		typedef Allocator								allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef typename Allocator::pointer				pointer;
		typedef typename Allocator::const_pointer		const_pointer;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_iterator<const value_type>			const_iterator;
		typedef reverse_tree_iterator<value_type>		reverse_iterator;
		typedef reverse_tree_iterator<const value_type>	const_reverse_iterator;

		class value_compare {
		public:
			Compare _comp;
			value_compare(Compare c) : _comp(c) {};

			value_compare() {};

			bool operator()(const value_type& lhs, const value_type& rhs) const {
				return _comp(lhs.first, rhs.first);
			}
		};
		
		typedef ft::red_black_tree<value_type, value_compare, allocator_type> red_black_tree;

	public:
		red_black_tree	_tree;
		key_compare		_comp;
	public:

		map() {};

		explicit map(const Compare& comp, const Allocator& alloc = Allocator()):
		_tree(value_compare(_comp), alloc), _comp(comp) {};

		template <class InputIt>
		map(InputIt first, InputIt last, const Compare& comp = Compare(),
			const Allocator& alloc = Allocator())
			: _tree(first, last, value_compare(comp), alloc), _comp(comp) {};

		map(const map& other): _comp(other._comp) {
			_tree = other._tree;
		};

		~map() {};

		map& operator=(const map& other) {
			if (this != &other) {
				this->_tree = other._tree;
				_comp = other._comp;
			}
			return *this;
		}

		allocator_type get_allocator() const {
			return _tree.get_alloc();
		}

		T& at(const Key& key) {
			iterator tmp = _tree.find(ft::make_pair(key, mapped_type()));
			if (tmp.get_node() == NULL)
				throw std::out_of_range("map::at");
			return tmp.get_node()->_key.second;
		}

		const T& at( const Key& key ) const {
			iterator tmp = _tree.find(ft::make_pair(key, mapped_type()));
			if (tmp.get_node() == NULL)
				throw std::out_of_range("");
			return tmp.get_node()->_key.second;
		}

		T& operator[](const Key& key) {
			return insert(ft::make_pair(key, mapped_type())).first.get_node()->_key.second;
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
			std::allocator<Key> alloc;
			return alloc.max_size();
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
			return _tree.erase(ft::make_pair(key, mapped_type()));
		}

		void swap(map& other) {
			_tree.swap(other._tree);
			std::swap(this->_comp, other._comp);
		}

		iterator find(const Key& key) {
			return _tree.find(ft::make_pair(key, mapped_type()));
		}

		const_iterator find( const Key& key ) const {
			return _tree.find(ft::make_pair(key, mapped_type()));
		}

		key_compare key_comp() const {
			return _comp;
		}

		map::value_compare value_comp() const {
			return _tree.value_comp();
		}

		size_type count( const Key& key ) const {
			return (_tree.count(ft::make_pair(key, mapped_type())) == NULL) ? 0 : 1;
		}

		iterator lower_bound( const Key& key ) {
			return _tree.lower_bound(ft::make_pair(key, mapped_type()));
		}

		const_iterator lower_bound( const Key& key ) const {
			return _tree.lower_bound(ft::make_pair(key, mapped_type()));
		}

		iterator upper_bound( const Key& key ) {
			return _tree.upper_bound(ft::make_pair(key, mapped_type()));
		}

		const_iterator upper_bound( const Key& key ) const {
			return _tree.upper_bound(ft::make_pair(key, mapped_type()));	
		}

		ft::pair<iterator,iterator> equal_range( const Key& key ) {
			return _tree.equal_range(ft::make_pair(key, mapped_type()));
		}

    };

	template< class Key, class T, class Compare, class Alloc >
	bool operator==( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return lhs._tree == rhs._tree;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator!=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs._tree == rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return lhs._tree < rhs._tree;
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator<=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (lhs._tree < rhs._tree || lhs._tree == rhs._tree);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs <= rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	bool operator>=( const ft::map<Key,T,Compare,Alloc>& lhs,
					const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return !(lhs < rhs);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key,T,Compare,Alloc>& lhs,
			ft::map<Key,T,Compare,Alloc>& rhs ) {
		lhs.swap(rhs);
	}
}

#endif