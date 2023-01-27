#include <string>
#include <iostream>
#include <stdlib.h>

#if flag
#include <set>
#include <utility>
namespace ft = std;
#else
    #include "./../utils/pair.hpp"
    #include "./../set/set.hpp"
#endif

void insert() {
    std::cout << "======INSERT======\n";
    ft::set<int> m;
    ft::set<char> m2;
    ft::set<int>::iterator it;
    m.insert(1);
    m.insert(2);
    m.insert(3);
    m.insert(5);
    m.insert(4);
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------------------\n";
    m2.insert('q');
    m2.insert('w');
    m2.insert('e');
    m2.insert('r');
    m2.insert('t');
    m2.insert(m2.begin(), m2.end());
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------------------\n";
    m.insert(m.begin(), 151);
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << *it<< std::endl;
    std::cout << m.size() << std::endl;
    std::cout << "====================\n";
}

void constructors() {
    std::cout << "======CONSRUCTORS======\n";
    ft::set<int> m1;
    ft::set<int>::iterator it;
    m1.insert(111);
    m1.insert(222);
    m1.insert(333);
    ft::set<int> m3(m1);
    for (it = m1.begin(); it != m1.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------------------\n";
    for (it = m3.begin(); it != m3.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------------------\n";
    std::cout << m1.size() << std::endl;
    std::cout << m3.size() << std::endl;
    std::cout << "====================\n";
}

void empty() {
    std::cout << "=====EMPTY======\n";
    ft::set<char> m1;
    std::cout << m1.empty() << std::endl;
    m1.insert('c');
    std::cout << m1.empty() << std::endl;
    std::cout << "====================\n";
}

void size() {
    std::cout << "=====SIZE======\n";
    ft::set<char> m1;
    std::cout << m1.size() << std::endl;
    m1.insert('c');
    std::cout << m1.size() << std::endl;
    m1.insert('c');
    std::cout << m1.size() << std::endl;
    m1.insert('b');
    std::cout << m1.size() << std::endl;
    m1.insert('a');
    std::cout << m1.size() << std::endl;
    std::cout << "====================\n";
}


void erase() {
    std::cout << "======ERASE======\n";
    ft::set<int> m;
    ft::set<int>::iterator it;
    m.insert(1);
    m.insert(11);
    m.insert(111);
    m.insert(1111);
    m.insert(11111);
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << "---------------------\n";
    m.erase(11);
    m.erase(m.begin());
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << *it << std::endl;
    std::cout << m.size() << std::endl;
    std::cout << "====================\n";
}

void find() {
    std::cout << "======FIND======\n";
    ft::set<std::string> m;
    ft::set<std::string>::iterator it;
    m.insert("lol");
    m.insert("rofl");
    m.insert("haha");
    m.insert("kek");
    std::cout << "---------------------\n";
    std::cout << *(m.find("lol")) << std::endl;
    std::cout << *(m.find("kek")) << std::endl;
    std::cout << "====================\n";
}

void count() {
    std::cout << "======COUNT======\n";
    ft::set<char> m;
    ft::set<char>::iterator it;
    m.insert('1');
    m.insert('1');
    m.insert('4');
    m.insert('5');
    m.insert('2');
    std::cout << "---------------------\n";
    std::cout << m.count('1') << std::endl;
    std::cout << m.count('q') << std::endl;
    std::cout << "====================\n";
}

void range() {
    std::cout << "======RANGE======\n";
    ft::set<int> m;
    ft::set<int>::iterator it;
    m.insert(11);
    m.insert(12);
    m.insert(13);
    m.insert(14);
    m.insert(15);
    std::cout << "---------------------\n";
    std::cout << *(m.lower_bound(11)) << std::endl;
    std::cout << *(m.upper_bound(12)) << std::endl;
    std::cout << *(m.equal_range(13).first) << std::endl;
    std::cout << *(m.equal_range(13).second) << std::endl;
    std::cout << "====================\n";
}

void revers_iterator() {
	std::cout << "======REVERSE_ITERATOR======\n";
	ft::set<int> m;
	m.insert(11);
    m.insert(12);
    m.insert(13);
    m.insert(14);
    m.insert(15);
	ft::set<int>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); ++rit)
		std::cout << *rit << std::endl;
	std::cout << "====================\n";
}

void operators() {
    std::cout << "======OPERATORS======\n";
    ft::set<int> m;
    ft::set<int> m1;
    ft::set<int>::iterator it;
    m.insert(11);
    m.insert(22);
    m.insert(33);
    m.insert(44);
    m.insert(55);
    m1.insert(66);
    m1.insert(77);
    m1.insert(88);
    m1.insert(99);
    m1.insert(00);
    std::cout << "---------------------\n";
    std::cout << (m == m1) << std::endl;
    std::cout << (m != m1) << std::endl;
    std::cout << (m < m1) << std::endl;
    std::cout << (m <= m1) << std::endl;
    std::cout << (m > m1) << std::endl;
    std::cout << (m >= m1) << std::endl;
    std::cout << "====================\n";
}

int main() {
    insert();
    constructors();
    empty();
    size();
    erase();
    find();
    count();
    range();
    operators();
    revers_iterator();
}