#ifndef PAIR_HPP
#define PAIR_HPP

namespace ft {
    template<typename T1, typename T2>
    struct pair
    {
        typedef T1  first_type;
        typedef T2  second_type;

        first_type  first;
        second_type second;

        pair(): first(T1()), second(T2()) {};

        pair(const T1& x, const T2& y): first(x), second(y) {};

        template<class U1, class U2>
        pair(const pair<U1, U2>& p): first(p.first), second(p.second) {};

        pair(const pair& p): first(p.first), second(p.second) {};

        pair& operator=(const pair& other) {
            if (*this != other) {
                first = other.first;
                second = other.second;
            }
            return *this;
        }
    };

    template< class T1, class T2 >
    ft::pair<T1, T2> make_pair(T1 t, T2 u) {
        return pair<T1, T2>(t, u);
    }

    template< class T1, class T2 >
    bool operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }

    template< class T1, class T2 >
    bool operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return !(lhs == rhs);
    }

    template< class T1, class T2 >
    bool operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return (lhs.first == rhs.first) ? (lhs.second < rhs.second) : (lhs.first < rhs.first);
    }

    template< class T1, class T2 >
    bool operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return !(lhs < rhs || lhs == rhs);
    }

    template< class T1, class T2 >
    bool operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return lhs < rhs || lhs == rhs;
    }
    
    template< class T1, class T2 >
    bool operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs ) {
        return lhs > rhs || lhs == rhs;
    }

    template <typename first_type, typename second_type>
    std::ostream& operator<<(std::ostream &os, ft::pair<first_type, second_type> pair) {
        (void)os;
        return std::cout << pair.first << std::endl << pair.second << std::endl;
    }
}


#endif