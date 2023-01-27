#include <string>
#include <iostream>
#include <stdlib.h>

#if flag
#include <vector>
namespace ft = std;
#else
    #include "./../vector/vector.hpp"
#endif

void constructors() {
	ft::vector<int>::iterator it;
	ft::vector<int> v1;
	ft::vector<int> v2(5);
	ft::vector<int> v3(5, 123);
	ft::vector<int> v4(v2);
	ft::vector<int> v5(v3.begin(), v3.end());
	std::cout << "======CONSTRUCTORS======\n";
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v2.begin(); it != v2.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v3.begin(); it != v3.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v4.begin(); it != v4.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v5.begin(); it != v5.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "v2 size = " << v2.size() << std::endl;
	std::cout << "v2 capasity= " << v2.capacity() << std::endl;
	std::cout << "v3 size = " << v3.size() << std::endl;
	std::cout << "v3 capasity = " << v3.capacity() << std::endl;
	std::cout << "v4 size = " << v4.size() << std::endl;
	std::cout << "v4 capasity = " << v4.capacity() << std::endl;
	std::cout << "v5 size = " << v5.size() << std::endl;
	std::cout << "v5 capasity= " << v5.capacity() << std::endl;
	std::cout << "====================\n";
}

void	copy_operator() {
	std::cout << "======COPY_OPERATOR======\n";
	ft::vector<char>::iterator it;
	ft::vector<char> v1(10, '$');
	ft::vector<char> v2(5, '@');
	ft::vector<char> v3(15, '#');
	v2 = v1;
	v3 = v1;
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v2.begin(); it != v2.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "---------------------\n";
	for (it = v3.begin(); it != v3.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "v2 size = " << v2.size() << std::endl;
	std::cout << "v2 capasity= " << v2.capacity() << std::endl;
	std::cout << "v3 size = " << v3.size() << std::endl;
	std::cout << "v3 capasity = " << v3.capacity() << std::endl;
	std::cout << "====================\n";
}

void assign() {
	std::cout << "======ASSIGN======\n";
	ft::vector<double>::iterator it;
	ft::vector<double> v1(3, 3.3);
	ft::vector<double> v2(4, 4.4);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.assign(5, 5.5);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.assign(v2.begin(), v2.end());
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "====================\n";
}

void at() {
	std::cout << "======AT======\n";
	ft::vector<std::string> v1(3, "lol");
	std::cout << v1.at(0) << std::endl;
	std::cout << v1.at(1) << std::endl;
	std::cout << v1.at(2) << std::endl;
	try {
		std::cout << v1.at(3) << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	std::cout << "====================\n";
}

void square_brackets() {
	std::cout << "======SQUARE_BRACKETS======\n";
	ft::vector<long> v1(5, 1);
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	v1[4] = 5;
	std::cout << v1[0] << std::endl;
	std::cout << v1[1] << std::endl;
	std::cout << v1[2] << std::endl;
	std::cout << v1[3] << std::endl;
	std::cout << v1[4] << std::endl;
	std::cout << "====================\n";
}

void front_and_back() {
	std::cout << "======FRONT_AND_BACK======\n";
	ft::vector<float> v1(6, 1.1f);
	std::cout << v1.front() << std::endl;
	std::cout << v1.back() << std::endl;
	std::cout << "====================\n";
}

void data(){
	std::cout << "======DATA======\n";
	ft::vector<int> v1(5, 5);
	int *data = v1.data();
	for (size_t i = 0; i < v1.size(); ++i)
		std::cout << data[i] << std::endl;
	std::cout << "====================\n";
}

void empty_and_max_size() {
	std::cout << "======EMPTY_AND_MAX_SIZE======\n";
	ft::vector<char> v1(10, '%');
	ft::vector<double> v2;
	std::cout << v1.empty() << std::endl;
	std::cout << v2.empty() << std::endl;
	std::cout << "v1 max size = " << v1.max_size() << std::endl;
	std::cout << "v2 max size = " << v2.max_size() << std::endl;
	std::cout << "====================\n";
}

void size_and_capasity() {
	std::cout << "======SIZE_AND_CAPASITY======\n";
	ft::vector<char> v1(10, '%');
	ft::vector<double> v2;
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v2 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "v2 capasity = " << v2.capacity() << std::endl;
	std::cout << "====================\n";
}

void reserve() {
	std::cout << "======RESERVE======\n";
	ft::vector<std::string>::iterator it;
	ft::vector<std::string> v1(5, "SCHOOL 21");
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.reserve(10);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.reserve(3);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "====================\n";
}

void clear() {
	std::cout << "======CLEAR======\n";
	ft::vector<std::string>::iterator it;
	ft::vector<std::string> v1(5, "CLEAR_TEST");
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.clear();
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	std::cout << "====================\n";
}

void insert() {
	std::cout << "======INSERT======\n";
	ft::vector<int>::iterator it;
	ft::vector<int> v1(4, 42);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	v1.insert(v1.begin(), v1.begin(), v1.begin() + 2);
	v1.insert(v1.begin(), 1, 666);
	v1.insert(v1.end(), 21);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "====================\n";
}

void erase() {
	std::cout << "======INSERT======\n";
	ft::vector<int>::iterator it;
	ft::vector<int> v1(5);
	v1[0] = 1;
	v1[1] = 2;
	v1[2] = 3;
	v1[3] = 4;
	v1[4] = 5;
	v1.erase(v1.begin() + 3);
	v1.erase(v1.begin(), v1.begin() + 2);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "====================\n";
}

void push_back() {
	std::cout << "======PUSH_BACK======\n";
	ft::vector<std::string>::iterator it;
	ft::vector<std::string> v1(10);
	v1.push_back("lol");
	v1.push_back("123");
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "====================\n";
}

void pop_back() {
	std::cout << "======POP_BACK======\n";
	ft::vector<std::string>::iterator it;
	ft::vector<std::string> v1(10);
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	v1.pop_back();
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "====================\n";
}

void resize() {
	std::cout << "======RESIZE======\n";
	ft::vector<int>::iterator it;
	ft::vector<int> v1(300);
	v1.resize(5);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	v1.resize(15);
	for (it = v1.begin(); it != v1.end(); ++it) {
		std::cout << *it << std::endl;
	}
	std::cout << "v1 size = " << v1.size() << std::endl;
	std::cout << "v1 capasity = " << v1.capacity() << std::endl;
	std::cout << "---------------------\n";
	std::cout << "====================\n";
}

void reverse_iterator() {
	std::cout << "======REVERSE_ITERATOR======\n";
	ft::vector<int> v(5, 21);
	v[0] = 1;
	v[1] = 2;
	v[2] = 3;
	v[3] = 4;
	ft::vector<int>::reverse_iterator rit;
	for (rit = v.rbegin(); rit != v.rend(); ++rit)
		std::cout << *rit << std::endl;
	std::cout << "====================\n";
}

void operators() {
	ft::vector<int> v1(666, 4221);
	ft::vector<int> v2(2142, 666);
	std::cout << (v1 == v2) << std::endl;
	std::cout << (v1 != v2) << std::endl;
	std::cout << (v1 < v2) << std::endl;
	std::cout << (v1 <= v2) << std::endl;
	std::cout << (v1 > v2) << std::endl;
	std::cout << (v1 >= v2) << std::endl;
}

int main() {
	constructors();
	copy_operator();
	assign();
	at();
	square_brackets();
	front_and_back();
	data();
	empty_and_max_size();
	size_and_capasity();
	reserve();
	clear();
	insert();
	erase();
	push_back();
	pop_back();
	resize();
	reverse_iterator();
	operators();
}