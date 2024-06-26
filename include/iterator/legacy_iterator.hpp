#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

namespace name_requirement
{
    namespace iterator
    {
	template<typename T>
	class is_legacy_iterator;

	template<typename T>
	class is_legacy_iterator<T*>;
    }
}

template<typename T>
class name_requirement::iterator::is_legacy_iterator
{
public:
#if   __cplusplus >= 202002L

    // TODO(#1): add C++20 changes

#elif __cplusplus >= 201103L

    using difference_type   = typename std::iterator_traits<T>::difference_type;
    using value_type        = typename std::iterator_traits<T>::value_type;
    using pointer           = typename std::iterator_traits<T>::pointer;
    using reference         = typename std::iterator_traits<T>::reference;
    using iterator_category = typename std::iterator_traits<T>::iterator_category;

    constexpr static bool value =
	std::is_copy_constructible<T>::value &&
	std::is_copy_assignable<T>::value    &&
	std::is_destructible<T>::value;

private:
    auto dereference()
	-> decltype(std::declval<T>().operator*());

    auto increment()
	-> decltype(static_cast<T&>(std::declval<T>().operator++()));

#endif
};

template<typename T>
class name_requirement::iterator::is_legacy_iterator<T*>
{
private:
    using this_type = typename std::add_pointer<T>::type;
    
public:
#if   __cplusplus >= 202002L

    // TODO(#2): add C++20 changes

#elif __cplusplus >= 201103L

    using difference_type =
	typename std::iterator_traits<this_type>::difference_type;

    using value_type =
	typename std::iterator_traits<this_type>::value_type;

    using pointer =
	typename std::iterator_traits<this_type>::pointer;

    using reference =
	typename std::iterator_traits<this_type>::reference;

    using iterator_category =
	typename std::iterator_traits<this_type>::iterator_category;

    constexpr static bool value = std::true_type::value;

#endif
};
