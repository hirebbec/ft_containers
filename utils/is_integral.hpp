#ifndef IS_INTEGRAL_HPP
#define IS_INTEGRAL_HPP

#include <stdint.h>

namespace ft {
    template <class T>
    struct is_integral : public ft::integral_constant<T, false> {};
    template <>
    struct is_integral<bool> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<signed char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned char> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<wchar_t> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<short> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned short> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<int> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned int> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<long long> : public ft::integral_constant<bool, true> {};
    template <>
    struct is_integral<unsigned long long> : public ft::integral_constant<bool, true> {};
};
#endif