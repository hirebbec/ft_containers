#ifndef RED_BLACK_TREE
# define RED_BLACK_TREE

#include <memory>
#include <iostream>
#include "node.hpp"
#include "./../iterators/tree_iterator.hpp"
#include "./../iterators/reverse_tree_iterator.hpp"
#include "./../utils/pair.hpp"
#include "./../utils/lexicographical_compare.hpp"
#include "./../utils/equal.hpp"


//СМОТРЕТЬ ЭТО ФАЙЛ ТОЛЬКО ПОД ТРЕК ДЕРЕВО(КИНО)!!!
//Совутую посмотреть https://www.youtube.com/watch?v=T70nn4EyTrs&t=3924s
//Визуализатор, чтобы лучше понять https://www.cs.usfca.edu/~galles/visualization/RedBlack.html

/*Красно черное дерево
	Во-первых, является деревом поиска, а значит выполняет следущие условия(согласно вики):
		1)значение ключа у левого узла меньше или равно значению ключа у данного узла.
		2)значение ключа у правого узла больше значения ключа у данного узла.
	Красно черное дерево - самобалансирующие, это значит вставляя или удаляя из него
	какие-то значения она может перестраиваться(также по правилам дерева поиска), 
	так происходит для того, чтобы у ветки нашего дерева были примерно одинаковы
	по длинне(типо баланс). Это позволит обеспечить сложность алгоритма поиска за O(log(N)).
	Механизм, по которму происходит балансировка можно описать следующими правилами:
		1)узел может быть либо красным, либо черным и имеет двух потомков
		2)корень дерева всегла черный
		3)все пустые листья - черные
		4)у красного узла черные потомки
		5)все пути, идущие от корня к листьям, содержат одинаковое количество черных вершин
*/

namespace ft {
	template<typename value_type,  class Compare = std::less<value_type>,
		  class Allocator = std::allocator<value_type> >
	class red_black_tree {
	public:
		typedef size_t									size_type;
		typedef typename ft::node<value_type>			node_type;
		typedef typename ft::node<value_type>*			pointer;
		typedef typename ft::node<value_type>&			reference;
		typedef Allocator								allocator_type;
		typedef	Compare									key_compare;
		typedef typename std::allocator<node_type>		node_alloc;
		typedef tree_iterator<value_type>				iterator;
		typedef tree_iterator<const value_type>			const_iterator;
		typedef reverse_tree_iterator<value_type>		reverse_iterator;
		typedef reverse_tree_iterator<const value_type>	reverse_const_iterator;

	private:
		pointer			_root;
		size_type		_size;
		allocator_type	_alloc;
		node_alloc		_node_alloc;
		key_compare		_compare;
		pointer			_after_end;
		pointer			_before_begin;

	public:

		red_black_tree(): _root(NULL), _size(0) {};

		red_black_tree(Compare comp, allocator_type alloc): _compare(comp), _alloc(alloc) {};
		
		~red_black_tree() {
			clear();
		}

		template <class InputIt>
		red_black_tree(InputIt first, InputIt last, const Compare& comp = Compare(),
				const Allocator& alloc = Allocator())
			: _size(0), _node_alloc(alloc), _compare(comp) {
			InputIt it = first;
			for (; it != last; ++it) insert(*it);
		}

		red_black_tree& operator=(const red_black_tree& other) {
			if (this != &other) {
				clear();
				_alloc = other._alloc;
				_node_alloc = other._node_alloc;
				_compare = other._compare;
				for(const_iterator it = other.begin(); it != other.end(); ++it) {
					insert(*it);
				}
			}
			return *this;
		}

		/*
		Взято из https://www.youtube.com/watch?v=T70nn4EyTrs&t=1166s
		Краткий алгоритм вставки:
			Находим место куда должен встать новый элемент, то есть идем по узлам впарво или влево
			по правилам дерева поиска. Потом вместо пустого узла вставляем вставляем новый с красным цветом,
			а дальше происходит балансировка. Могут возникнуть 2 кейса:
				1)новый узел - корень, нарушается правило 2, чтобы пофиксить, просто меняем цвет узла на черный.
				2)у нового узла родитель тоже красный, нарушается правило 4. У этого кейса еще 2 кейса:
					Надо смотреть на цвет второго ребенка родителя родителя(дяди).
					Стоит отметить, что в этих кейсах цвет родителя родителя(дедушки) всегда черный, тк
					мы предпологаем, что дерево было правильным, а это соответсвует 4 правилу.
					2.1)цвет дяди - красный. Чтобы пофиксить дерево необходимо поменять цвета у родителя,
					дедушки и дяди на противоположные. В этом случаем локально проблема решиться,
					но возникате проблема, которая также делиться на 2 кейса.
						2.1.1)дедушка - корень, нарушается правило 2. Чтобы пофиксить просто делаем его черным,
						вставка закончена.
						2.1.2)родитель дедушки тоже красный. нарушается праило 4. На самом деле это кейс -
						точная копия кейса 2, но теперь мы немного ближе к корьню, а значит нужно запустить тот же
						алгоритм фикса и ждать пока мы таким образом дойдем до корня, то есть до кейса 2.2.1.
						Простыми словами - рекурсия. 
					2.2)цвет дяди - черный. Снова возникают 2 кейса(в видео об этом не говорится, 
						но на самом деле тут 4 кейса, нужно также смотреть с какой стороны от дедушки это все происходит,
						хорошо показано здесь: https://www.geeksforgeeks.org/insertion-in-red-black-tree/),
						смотрим на то какой новый узел(правый или левый сын).
						2.2.1)Новый узел - левый сын и находиться слево от дедушки. Чтобы пофиксить делаем малый левый(или правый) поворот(гугл в помощь)
						между новым родителем и его родителем, а потом меняем цвета у них(можно сперва поменять, а потом крутить).
						2.2.2)Новый узел - правый сын и находиться слево от дедушки. Чтобы пофиксить делаем малый левый(или правый) поворот между новым узлом
						и его родителем. После этого мы попадаем в кейс 2.2.1.
						2.2.3)Новый узел - левый сын и находиться справо от дедушки. Чтобы пофиксить делаем малый левый(или правый) поворот(гугл в помощь)
						между новым родителем и его родителем, а потом меняем цвета у них(можно сперва поменять, а потом крутить).
						2.2.4)Новый узел - правый сын и находиться справо от дедушки. Чтобы пофиксить делаем малый левый(или правый) поворот между новым узлом
						и его родителем. После этого мы попадаем в кейс 2.2.4.
		*/

		ft::pair<iterator, bool> insert(const value_type &key) {
			iterator res = find(key);
			if (res.get_node() != NULL)
				return ft::make_pair<iterator, bool>(res, false);
			if (_size == 0) { //CASE 1
				node_type tmp(key);
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, tmp);
				_root->_color = BLACK;
				++_size;
				return ft::make_pair<iterator, bool>(iterator(&tmp), true);
			} else {
				pointer new_node = simple_insert(key);
				if (new_node->_parent->_color == RED) //CASE 2
					fix_tree(new_node);
				++_size;
				return ft::make_pair<iterator, bool>(new_node, true);
			}
		}

		pointer insert(iterator pos, const value_type &key) {
			(void)pos;
			iterator res = find(key);
			if (res.get_node() != NULL)
				return NULL;
			if (_size == 0) { //CASE 1
				node_type tmp(key);
				_root = _node_alloc.allocate(1);
				_node_alloc.construct(_root, tmp);
				_root->_color = BLACK;
				++_size;
				return _root;
			} else {
				pointer new_node = simple_insert(key);
				if (new_node->_parent->_color == RED) //CASE 2
					fix_tree(new_node);
				++_size;
				return new_node;
			}
		}

		/*
		Тут все просто красно черное дерево - это дерево поиска, значит если искомое значение меньше
		текущего - идем на лево ветке, если искомое значение больше - идем на право по ветке.
		Если дощли до NIL - значение не найдено, возвращаем NULL 
		*/
		iterator find(const value_type& key) {
			return iterator(tree_search(_root, key));
		}

		pointer count(const value_type& key) const {
			return tree_search(_root, key);
		}

		pointer tree_search(pointer node, value_type key) const {
			if (node == NIL ||
				(!_compare(key, node->_key) && !_compare(node->_key, key))) {
				return node;
			}
			if (_compare(key, node->_key))
				return tree_search(node->_lnode, key);
			else
				return tree_search(node->_rnode, key);
		}

		/*
		Взято из https://www.youtube.com/watch?v=T70nn4EyTrs&t=1166s
		Краткий алгоритм удаления.
		Находим узел, который нужно удалить и первым делом смортим на кол-во его валидных детей.
		1) Детей нет. Смотрим на цвет удаляемого узла.
			1.1) узел - красный. Просто заменяем удалямый узел на NIL.
			1.2) узел - черный. Также заменяем удалямый узел на NIL, но при этом уменьшается черная длинна ветки,
			теперь надо это пофиксить. ATTENTION!!! ВОТ ТУТ запускаем фиксищую функцию(пригодиться в пункте 1.2.3.2.2).
			Смотрим на цвет родителя.
				1.2.1) Если родителя нет - ничего не делаем(мы просто удалили последний узел - корень).
				1.2.2) Родитель - красный. У него точно есть второй черный сын(чтобы правило 5 и 4 работало).
						смотрим на потомков этого узла(племмяников удаляемого узла).
						1.2.2.1) Есть хотя бы 1 красный племянник, в этом случаем делаем либо 2 малых поворота,
							либо 1(точно также как в insert пункт 2.2). Родитель становиться красным, племянник черным.
						1.2.2.2) Красных племянников нету. Родитель становиться черным, брат красным.
				1.2.3) Родитель - черный. Смотрим на цвет его сына(нашего брата).
						1.2.3.1) Брат - красный. Значит у него точно есть черный сын. чтобы не нарушались правила 4 и 5.
							Смотрим на детей этого племянника(внучатых племянников).
								1.2.3.1.1) Есть хотя бы 1 красный внучатый племянник. В этом кейсе также 
									происходит 1 или поворота(как в insert пункт 2.2). Цвета меняються только у
									этого красного внучатого племяника. 
								1.2.3.1.2) Нет красных внучатых племянников. В этом кейсе 1 поворот между братом и родителем.
									Цвета меняються у брата, и племянника, у которого нет черных детей.
						1.2.3.2) Брат - черный. Смотрим на его детей.
								1.2.3.2.1) Есть хотя бы 1 красный племянник. Два поворота(как в insert пункт 2.2).
									Этот красный племянник становиться черным(теперь все черные).
								1.2.3.2.2) Нет красных племянников. Перекрашиваем брата в красный цвет.
									Рекурсивно вызываем фиксищую функцию, но теперь у нее в аргументе родитель,
									как бы удаленного узла.
		2) Один ребенок. В этом случаем, чтобы дерево было корректным этот ребенок должен быть черным(правило 5),
			а также его ребенок будет красным бездетным узлом. Заменяем удаляемый узел на его ребенка
			и перекрашиваем его в черный цвет.
		3) Два ребенка. Из левого поддерева берем узел с самым большим значением и копируем его в удаляемый узел.
			Остается только удалить оригинальный узел с таким значением, а это сводиться к пункту 1 или 2.
			(псевдорекурсия, тк применится только 1 раз).
		*/

		size_type erase(value_type key) {
				pointer node = tree_search(_root, key);
				if (node == NIL)
					return 0;
				--_size;
				if (node->isLeaf() == true)
					zero_child(node); //CASE 1
				else if (node->_lnode && node->_rnode)
					two_child(node); //CASE 3
				else
					one_child(node); //CASE 2
				return 1;
			}

		void printTree() { printBT("", _root, false); }

		iterator begin() { return iterator(rb_min(_root)); }

		const_iterator begin() const { return const_iterator(rb_min(_root)); }

		iterator end() { return iterator(rb_max(_root), true); }

		const_iterator end() const { return const_iterator(rb_max(_root), true); }

		reverse_iterator rbegin() { return reverse_iterator(rb_max(_root)); }

		reverse_const_iterator rbegin() const { return reverse_const_iterator(rb_max(_root)); }

		reverse_iterator rend() { return reverse_iterator(rb_min(_root), true); }

		reverse_const_iterator rend() const { return reverse_const_iterator(rb_min(_root), true); }

	private:

		void printBT(const std::string& prefix, const pointer nodeV,
				 bool isLeft) const {
			std::cout << prefix;
			std::cout << (isLeft ? "├──" : "└──");
			if (nodeV == NIL) {
				std::cout << "\033[0;36m"
						<< "nil"
						<< "\033[0m" << std::endl;
				return;
			}
			// print the value of the node
			if (nodeV->_color == 0)
				std::cout << "\033[0;36m" << nodeV->_key << "\033[0m" << std::endl;
			else
				std::cout << "\033[0;31m" << nodeV->_key << "\033[0m" << std::endl;
			printBT(prefix + (isLeft ? "│   " : "    "), nodeV->_lnode, true);
			printBT(prefix + (isLeft ? "│   " : "    "), nodeV->_rnode, false);
		}

		void free_tree(pointer node) {
			if (node != NULL) {
				if (node->_lnode != NULL)
					free_tree(node->_lnode);
				if (node->_rnode != NULL)
					free_tree(node->_rnode);
				_node_alloc.destroy(node);
				_node_alloc.deallocate(node, 1);
				node = NULL;
			}
		}

		pointer	simple_insert(value_type key) {
			pointer	tmp = _root;
			while (true) {
				if (key <= tmp->_key) {
					if (tmp->_lnode == NIL) {
						node_type	new_node(key, tmp);
						tmp->_lnode = _node_alloc.allocate(1);
						_node_alloc.construct(tmp->_lnode, new_node);
						return tmp->_lnode;
					} else {
						tmp = tmp->_lnode;
					}
				} else {
					if (tmp->_rnode == NIL) {
						node_type	new_node(key, tmp);
						tmp->_rnode = _node_alloc.allocate(1);
						_node_alloc.construct(tmp->_rnode, new_node);
						return tmp->_rnode;
					} else {
						tmp = tmp->_rnode;
					}
				}
			}
		}

		pointer	simple_insert(pointer node) {
			pointer	tmp = _root;
			while (true) {
				if (node._key <= tmp->_key) {
					if (tmp->_lnode == NIL) {
						tmp->_lnode = node;
						return tmp->_lnode;
					} else {
						tmp = tmp->_lnode;
					}
				} else {
					if (tmp->_rnode == NIL) {
						tmp->_rnode = node;
						return tmp->_rnode;
					} else {
						tmp = tmp->_rnode;
					}
				}
			}
		}

		void	red_uncle_case(pointer	new_node) {
			new_node->_parent->_color = BLACK;
			new_node->_parent->_parent->_color = RED;
			if (new_node->_parent->_parent->_lnode != new_node->_parent) {
				new_node->_parent->_parent->_lnode->_color = BLACK;
			} else {
				new_node->_parent->_parent->_rnode->_color = BLACK;
			}
			if (new_node->_parent->_parent == _root) { //CASE 2.1.1
				new_node->_parent->_parent->_color = BLACK;
			} else if (new_node->_parent->_parent->_parent->_color == RED) { //CASE 2.1.2
				fix_tree(new_node->_parent->_parent);
			}
		}

		//Повороты написал по картинкам из https://www.geeksforgeeks.org/insertion-in-red-black-tree/
		void	left_left_turn(pointer node) {
			pointer	parent = node->_parent;
			pointer grandparent = node->_parent->_parent;
			grandparent->_lnode = parent->_rnode;
			if (grandparent->_lnode != NIL) {
				grandparent->_lnode->_parent = grandparent;
			}
			parent->_rnode = grandparent;
			parent->_parent = grandparent->_parent;
			grandparent->_color = RED;
			parent->_color = BLACK;
			if (_root == grandparent) {
				_root = parent;
			} else {
				if (grandparent->_parent->_lnode == grandparent) {
					grandparent->_parent->_lnode = parent;
				} else {
					grandparent->_parent->_rnode = parent;
				}
			}
			grandparent->_parent = parent;
		}

		void	left_right_turn(pointer node) {
			pointer	parent = node->_parent;
			pointer grandparent = node->_parent->_parent;
			grandparent->_lnode = node;
			node->_parent = grandparent;
			if (node->_lnode != NIL) {
				node->_lnode->_parent = parent;
			}
			parent->_rnode = node->_lnode;
			parent->_parent = node;
			node->_lnode = parent;
			left_left_turn(parent);
		}

		void	right_right_turn(pointer node) {
			pointer	parent = node->_parent;
			pointer grandparent = node->_parent->_parent;
			grandparent->_rnode = parent->_lnode;
			if (grandparent->_rnode != NIL) {
				grandparent->_rnode->_parent = grandparent;
			}
			parent->_lnode = grandparent;
			parent->_parent = grandparent->_parent;
			grandparent->_color = RED;
			parent->_color = BLACK;
			if (_root == grandparent) {
				_root = parent;
			} else {
				if (grandparent->_parent->_lnode == grandparent) {
					grandparent->_parent->_lnode = parent;
				} else {
					grandparent->_parent->_rnode = parent;
				}
			}
			grandparent->_parent = parent;
		}

		void	right_left_turn(pointer node) {
			pointer	parent = node->_parent;
			pointer grandparent = node->_parent->_parent;
			grandparent->_rnode = node;
			node->_parent = grandparent;
			if (node->_rnode != NIL) {
				node->_rnode->_parent = parent;
			}
			parent->_lnode = node->_rnode;
			parent->_parent = node;
			node->_rnode = parent;
			right_right_turn(parent);
		}


		void	black_uncle_left_case(pointer new_node) {
			pointer grandparent = new_node->_parent->_parent;
			if (grandparent->_lnode->_lnode == new_node) { //CASE 2.2.1
				left_left_turn(new_node);
			} else { //CASE 2.2.2
				left_right_turn(new_node);
			}
		}

		void	black_uncle_right_case(pointer new_node) {
			pointer grandparent = new_node->_parent->_parent;
			if (grandparent->_rnode->_rnode == new_node) { //CASE 2.2.3
				right_right_turn(new_node);
			} else { //CASE 2.2.4
				right_left_turn(new_node);
			}
		}

		void fix_tree(pointer new_node) {
			pointer grandparent = new_node->_parent->_parent;
			if (grandparent->_lnode == new_node->_parent) {
				if (grandparent->_rnode == NIL || grandparent->_rnode->_color == BLACK) //CASE 2.2
					black_uncle_left_case(new_node);
				else //CASE 2.1
					red_uncle_case(new_node);
			} else if (grandparent->_rnode == new_node->_parent) {
				if (grandparent->_lnode == NIL || grandparent->_lnode->_color == BLACK) //CASE 2.2
					black_uncle_right_case(new_node);
				else //CASE 2.1
					red_uncle_case(new_node);
			}
		}

		void red_parent_erase(pointer parent, pointer node) {
			pointer brother = ((parent->_lnode == node) ? parent->_rnode : parent->_lnode);
			if (brother->_lnode && brother->_lnode->_color == RED) { //CASE 1.2.2.1
				if (parent->_lnode == brother) {
					left_left_turn(brother->_lnode);
					parent->_parent->_lnode->_color = BLACK;
				}
				else
					right_left_turn(brother->_lnode);
				parent->_parent->_color = RED;
			} else if (brother->_rnode && brother->_rnode->_color == RED) { //CASE 1.2.2.1
				if (parent->_lnode == brother)
					left_right_turn(brother->_rnode);
				else {
					right_right_turn(brother->_rnode);
					parent->_parent->_rnode->_color = BLACK;
				}
				parent->_parent->_color = RED;
			}
			else //CASE 1.2.2.2
				brother->_color = RED;
			parent->_color = BLACK;
		}

		void left_rotate(pointer parent, pointer brother) {
			parent->_lnode = brother->_rnode;
			parent->_lnode->_parent = parent;
			parent->_lnode->_color = RED;
			if (parent == _root)
				_root = brother;
			else if (parent->_parent->_lnode == parent)
				parent->_parent->_lnode = brother;
			else
				parent->_parent->_rnode = brother;
			brother->_parent = parent->_parent;
			brother->_rnode = parent;
			parent->_parent = brother;
			brother->_color = BLACK;

		}

		void right_rotate(pointer parent, pointer brother) {
			parent->_rnode = brother->_lnode;
			parent->_rnode->_parent = parent;
			parent->_rnode->_color = RED;
			if (parent == _root)
				_root = brother;
			else if (parent->_parent->_lnode == parent)
				parent->_parent->_lnode = brother;
			else
				parent->_parent->_rnode = brother;
			brother->_parent = parent->_parent;
			brother->_lnode = parent;
			parent->_parent = brother;
			brother->_color = BLACK;
		}

		void red_brother(pointer parent, pointer brother) {
			pointer lnephew = brother->_lnode;
			pointer rnephew = brother->_rnode;
			if (lnephew != NULL) {
				if ((lnephew->_lnode && lnephew->_lnode->_color == RED) ||
				 (lnephew->_rnode && lnephew->_rnode->_color == RED)) { //CASE 1.2.3.1.1
					left_left_turn(lnephew);
					parent->_color = BLACK;
					rnephew->_color = RED;
					return;
				}
			} else if (rnephew != NULL) {
				if ((rnephew->_lnode && rnephew->_lnode->_color == RED) ||
				(rnephew->_rnode && rnephew->_rnode->_color == RED)) { //CASE 1.2.3.1.1
					right_right_turn(rnephew);
					parent->_color = BLACK;
					lnephew->_color = RED;
					return;
				}
			}
			//CASE 1.2.3.1.2
			if (brother == parent->_lnode)
				left_rotate(parent, brother);
			else
				right_rotate(parent, brother);
		}

		void black_brother(pointer parent, pointer brother) {
			pointer lnephew = brother->_lnode;
			pointer rnephew = brother->_rnode;
			if (lnephew != NULL && lnephew->_color == RED) { //CASE 1.2.3.2.1
				if (parent->_lnode == brother)
					left_left_turn(lnephew);
				else
					right_left_turn(lnephew);
				lnephew->_color = BLACK;
				parent->_color = BLACK;
			} else if (rnephew != NULL && rnephew->_color == RED) { //CASE 1.2.3.2.1
				if (parent->_lnode == brother)
					left_right_turn(rnephew);
				else
					right_right_turn(rnephew);
				rnephew->_color = BLACK;
				parent->_color = BLACK;
			} else { //CASE 1.2.3.2.2
				brother->_color = RED;
				erase_fix(parent->_parent, parent);
			}
		}

		void black_parent_erase(pointer parent, pointer node) {
			pointer brother = ((parent->_lnode == node) ? parent->_rnode : parent->_lnode);
			if (brother->_color == RED)//CASE 1.2.3.1
				red_brother(parent, brother);
			else
				black_brother(parent, brother); //CASE 1.2.3.2
		}

		void	erase_fix(pointer parent, pointer node) {
			if (parent == NULL) { //CASE 1.2.1
				return;
			} else if (parent->_color == RED) //CASE 1.2.2
				red_parent_erase(parent, node);
			else //CASE 1.2.3
				black_parent_erase(parent, node);
		}

		void	zero_child(pointer node) {
			pointer parent = node->_parent;
			int color = node->_color;
			((parent->_lnode == node) ? parent->_lnode : parent->_rnode) = NIL;
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
			node = NIL;
			if (color == BLACK) { //CASE 1.2
				erase_fix(parent, node);	
			}
			//CASE 1.1
		}
		
		void	one_child(pointer node) {
			pointer parent = node->_parent;
			pointer child = (node->_lnode == NIL) ? node->_rnode : node->_lnode;
			child->_parent = parent;
			((parent->_lnode == node) ? parent->_lnode : parent->_rnode) = child;
			child->_color = BLACK;
			_node_alloc.destroy(node);
			_node_alloc.deallocate(node, 1);
		}
		
		pointer find_max(pointer begin) {
			pointer tmp = begin;
			while (tmp->_rnode != NIL)
				tmp = tmp->_rnode;
			return tmp;
		}

		void	two_child(pointer node) {
			pointer max = find_max(node->_lnode);
			if (max->isLeaf() == true)
				zero_child(max);
			else
				one_child(max);
		}

		pointer	rb_min(pointer local_root) const {
			if (local_root == NULL)
				return NULL;
			pointer tmp = local_root;
			while (tmp->_lnode != NIL)
				tmp = tmp->_lnode;
			return tmp;
		}
		
		pointer	rb_max(pointer local_root) const {
			if (local_root == NULL)
				return NULL;
			pointer tmp = local_root;
			while (tmp->_rnode != NIL)
				tmp = tmp->_rnode;
			return tmp;
		}
		
	public:
		size_type size() const {return _size;}

		allocator_type get_alloc() const {
			return _alloc;
		}

		size_type max_size() const {
			return _alloc.max_size();
		}

		void	clear() {
			if (_size != 0)
				free_tree(_root);
			_size = 0;
			_root = NULL;
		}

		void swap(red_black_tree &other) {
			std::swap(_root, other._root);
			std::swap(_size, other._size);
			std::swap(_node_alloc, other._node_alloc);
			std::swap(_compare, other._compare);
			std::swap(_alloc, other._alloc);
		}

		key_compare value_comp() const { return _compare;}

		iterator lower_bound(const value_type& key) {
			iterator it = begin();
			while (it != end() && _compare(*it, key))
				++it;
			return it;
		}

		iterator upper_bound(const value_type& key) {
			iterator it = begin();
			while (it != end() && !(_compare(key, *it)))
				++it;
			return it;
		}

		ft::pair<iterator, iterator> equal_range(const value_type &key) {
			return ft::make_pair(lower_bound(key), upper_bound(key));
		}

		friend bool operator==(const red_black_tree<value_type, Compare, Allocator>& lhs,
				const red_black_tree<value_type, Compare, Allocator>& rhs) {
			return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
		}

		friend bool operator<(const red_black_tree<value_type, Compare, Allocator>& lhs,
			   const red_black_tree<value_type, Compare, Allocator>& rhs) {
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		}
	};
}

#endif