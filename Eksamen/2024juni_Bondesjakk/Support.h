#pragma once


#include <type_traits>

template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_equality_operator : std::false_type {
};

template <typename T>
struct has_equality_operator<
    T, void_t<
        decltype(operator==(std::declval<T>(), std::declval<T>()))
    >
> : std::true_type
{ };



template <typename T>
typename std::enable_if<has_equality_operator<T>::value, bool>::type support_equal(T p1, T p2) {
    return operator==(p1,p2);
}

template <typename T>
typename std::enable_if<!has_equality_operator<T>::value, bool>::type support_equal(T p1, T p2) {
    return p1.x == p2.x && p1.y == p2.y;
}





