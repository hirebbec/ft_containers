#include <string>
#include <iostream>
#include <stdlib.h>

#if flag
#include <stack>
namespace ft = std;
#else
    #include "./../stack/stack.hpp"
#endif

void push_and_top_and_pop() {
    std::cout << "======PUSH_AND_TOP_AND_POP======\n";
    ft::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(42);
    s.push(21);
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << s.top() << std::endl;
    s.pop();
    std::cout << "====================\n";
}

void copy_operator() {
    std::cout << "======COPY_OPERATOR======\n";
    ft::stack<int> s1;
    s1.push(1);
    s1.push(2);
    s1.push(3);
    s1.push(42);
    s1.push(21);
    ft::stack<int> s2;
    s2 = s1;
    s1.pop();
    s1.pop();
    s1.pop();
    s1.pop();
    s1.pop();
    std::cout << s2.top() << std::endl;
    s2.pop();
    std::cout << s2.top() << std::endl;
    s2.pop();
    std::cout << s2.top() << std::endl;
    s2.pop();
    std::cout << s2.top() << std::endl;
    s2.pop();
    std::cout << s2.top() << std::endl;
    s2.pop();
    std::cout << "====================\n";
}

void    empty_and_size() {
    std::cout << "======EMPTY_AND_SIZE======\n";
    ft::stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(42);
    s.push(21);
    std::cout << "s empty = " << s.empty() << std::endl;
    std::cout << "s size = " << s.size() << std::endl;
    s.pop();
    s.pop();
    s.pop();
    std::cout << "s empty = " << s.empty() << std::endl;
    std::cout << "s size = " << s.size() << std::endl;
    s.pop();
    s.pop();
    std::cout << "s empty = " << s.empty() << std::endl;
    std::cout << "s size = " << s.size() << std::endl;
    std::cout << "====================\n";
}

void operators() {
	ft::stack<char> s1;
	ft::stack<char> s2;
    s1.push('*');
    s2.push('#');
    s1.push('#');
	std::cout << (s1 == s2) << std::endl;
	std::cout << (s1 != s2) << std::endl;
	std::cout << (s1 < s2) << std::endl;
	std::cout << (s1 <= s2) << std::endl;
	std::cout << (s1 > s2) << std::endl;
	std::cout << (s1 >= s2) << std::endl;
}

int main() {
    push_and_top_and_pop();
    copy_operator();
    empty_and_size();
    operators();
}