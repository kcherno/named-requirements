#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

#include "feature-macros/include/cxx_standard.hpp"

#define LEGACY_ITERATOR_DEPRECATED__

#if __cplusplus >= CXX20_STANDARD__
#  undef  LEGACY_ITERATOR_DEPRECATED__
#  define LEGACY_ITERATOR_DEPRECATED__ [[deprecated ("use iterator concepts")]]
#endif

namespace name_requirement
{
    namespace iterator
    {
	template<typename T>
	class LEGACY_ITERATOR_DEPRECATED__ legacy_iterator;

	template<typename T>
	class legacy_iterator<T*>;
    }
}

template<typename T>
class name_requirement::iterator::legacy_iterator
{
public:
    using difference_type   = typename std::iterator_traits<T>::difference_type;
    using value_type        = typename std::iterator_traits<T>::value_type;
    using pointer           = typename std::iterator_traits<T>::pointer;
    using reference         = typename std::iterator_traits<T>::reference;
    using iterator_category = typename std::iterator_traits<T>::iterator_category;

    static_assert(std::is_copy_constructible<T>::value,
		  "T type must satisfy CopyConstructible");

    static_assert(std::is_copy_assignable<T>::value,
		  "T type must satisfy CopyAssignable");

    static_assert(std::is_destructible<T>::value,
		  "T type must satisfy Destructible");

    // TODO(#1): add swappable requirement

    static_assert(std::is_same<typename std::add_lvalue_reference<T>::type,
		               decltype(std::declval<T>().operator++())
		               >::value,
		  "T type must support the pre-increment operator++() "
		  "and returns lvalue reference T&");

    constexpr static bool value = std::true_type::value;

private:
    auto dereference()
	-> decltype(std::declval<T>().operator*());
};

template<typename T>
class name_requirement::iterator::legacy_iterator<T*>
{
private:
    using this_type = typename std::add_pointer<T>::type;
    
public:
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
};
