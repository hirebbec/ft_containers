#include <string>
#include <iostream>
#include <stdlib.h>

#if flag
#include <map>
#include <utility>
namespace ft = std;
#else
    #include "./../utils/pair.hpp"
    #include "./../map/map.hpp"
#endif

void insert() {
    std::cout << "======INSERT======\n";
    ft::map<int, char> m;
    ft::map<int, char> m2;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "---------------------\n";
    m2.insert(ft::make_pair(11, 'q'));
    m2.insert(ft::make_pair(12, 'w'));
    m2.insert(ft::make_pair(13, 'e'));
    m2.insert(ft::make_pair(14, 'r'));
    m2.insert(ft::make_pair(15, 't'));
    m.insert(m2.begin(), m2.end());
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "---------------------\n";
    m.insert(m.begin(), ft::make_pair(151, 'x'));
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << m.size() << std::endl;
    std::cout << "====================\n";
}

void constructors() {
    std::cout << "======CONSRUCTORS======\n";
    ft::map<int, char> m1;
    ft::map<int, char>::iterator it;
    m1.insert(ft::make_pair(111, '1'));
    m1.insert(ft::make_pair(222, '2'));
    m1.insert(ft::make_pair(333, '3'));
    ft::map<int, char> m3(m1);
    for (it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "---------------------\n";
    for (it = m3.begin(); it != m3.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "---------------------\n";
    std::cout << m1.size() << std::endl;
    std::cout << m3.size() << std::endl;
    std::cout << "====================\n";
}

void at() {
    std::cout << "======AT======\n";
    ft::map<int, char> m1;
    ft::map<int, char>::iterator it;
    m1.insert(ft::make_pair(1, 'a'));
    m1.insert(ft::make_pair(2, 'b'));
    m1.insert(ft::make_pair(3, 'c'));
    m1.insert(ft::make_pair(4, 'd'));
    m1.insert(ft::make_pair(5, 'e'));
    std::cout << m1.at(1) << std::endl;
    std::cout << m1.at(2) << std::endl;
    std::cout << m1.at(3) << std::endl;
    std::cout << m1.at(4) << std::endl;
    std::cout << m1.at(5) << std::endl;
    try {
        std::cout << m1.at(6);
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }
    m1.at(1) = 'w';
    for (it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "====================\n";
}

void square_brackets() {
    std::cout << "=====SQUARE_BRACKETS======\n";
    ft::map<int, char> m1;
    ft::map<int, char>::iterator it;
    m1.insert(ft::make_pair(1, 'a'));
    m1.insert(ft::make_pair(2, 'b'));
    m1.insert(ft::make_pair(3, 'c'));
    m1.insert(ft::make_pair(4, 'd'));
    m1.insert(ft::make_pair(5, 'e'));
    std::cout << m1[1] << std::endl;
    std::cout << m1[2] << std::endl;
    std::cout << m1[3] << std::endl;
    std::cout << m1[4] << std::endl;
    std::cout << m1[5] << std::endl;
    m1[5] = 'w';
    for (it = m1.begin(); it != m1.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "====================\n";
}

void empty() {
    std::cout << "=====EMPTY======\n";
    ft::map<int, char> m1;
    std::cout << m1.empty() << std::endl;
    m1.insert(ft::make_pair(3, 'c'));
    std::cout << m1.empty() << std::endl;
    std::cout << "====================\n";
}

void size() {
    std::cout << "=====SIZE======\n";
    ft::map<int, char> m1;
    std::cout << m1.size() << std::endl;
    m1.insert(ft::make_pair(3, 'c'));
    std::cout << m1.size() << std::endl;
    m1.insert(ft::make_pair(3, 'c'));
    std::cout << m1.size() << std::endl;
    m1.insert(ft::make_pair(3, '1'));
    std::cout << m1.size() << std::endl;
    m1.insert(ft::make_pair(4, 'c'));
    std::cout << m1.size() << std::endl;
    std::cout << "====================\n";
}


void erase() {
    std::cout << "======ERASE======\n";
    ft::map<int, char> m;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << "---------------------\n";
    m.erase(3);
    m.erase(m.begin());
    for (it = m.begin(); it != m.end(); ++it)
        std::cout << it->first << std::endl;
    std::cout << m.size() << std::endl;
    std::cout << "====================\n";
}

void find() {
    std::cout << "======FIND======\n";
    ft::map<int, char> m;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    std::cout << "---------------------\n";
    std::cout << m.find(1)->first << std::endl;
    std::cout << m.find(2)->first << std::endl;
    std::cout << "====================\n";
}

void count() {
    std::cout << "======COUNT======\n";
    ft::map<int, char> m;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    std::cout << "---------------------\n";
    std::cout << m.count(1) << std::endl;
    std::cout << m.count(21) << std::endl;
    std::cout << "====================\n";
}

void range() {
    std::cout << "======RANGE======\n";
    ft::map<int, char> m;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    std::cout << "---------------------\n";
    std::cout << m.lower_bound(1)->first << std::endl;
    std::cout << m.upper_bound(2)->first << std::endl;
    std::cout << m.equal_range(3).first->first << std::endl;
    std::cout << m.equal_range(3).second->first << std::endl;
    std::cout << "====================\n";
}

void revers_iterator() {
	std::cout << "======REVERSE_ITERATOR======\n";
	ft::map<int, char> m;
	m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
	ft::map<int, char>::reverse_iterator rit;
	for (rit = m.rbegin(); rit != m.rend(); ++rit)
		std::cout << rit->first << std::endl;
	std::cout << "====================\n";
}

void operators() {
    std::cout << "======OPERATORS======\n";
    ft::map<int, char> m;
    ft::map<int, char> m1;
    ft::map<int, char>::iterator it;
    m.insert(ft::make_pair(1, '1'));
    m.insert(ft::make_pair(2, '2'));
    m.insert(ft::make_pair(3, '3'));
    m.insert(ft::make_pair(4, '4'));
    m.insert(ft::make_pair(5, '5'));
    m1.insert(ft::make_pair(11, '}'));
    m1.insert(ft::make_pair(22, 'x'));
    m1.insert(ft::make_pair(33, 'g'));
    m1.insert(ft::make_pair(44, 't'));
    m1.insert(ft::make_pair(55, 'q'));
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
    at();
    square_brackets();
    empty();
    size();
    erase();
    find();
    count();
    range();
    operators();
    revers_iterator();
}