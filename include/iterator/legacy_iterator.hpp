#pragma once

#include <type_traits>
#include <iterator>
#include <utility>

#include "feature-macros/include/feature_macros.hpp"
#include "library/swappable.hpp"

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
	class LEGACY_ITERATOR_DEPRECATED__ is_legacy_iterator;

	template<typename T>
	class is_legacy_iterator<T*>;
    }
}

template<typename T>
class name_requirement::iterator::is_legacy_iterator
{
private:
    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto dereference(int) noexcept
	-> decltype(std::declval<T>().operator*(), bool {})
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool dereference(...) noexcept
    {
	return false;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto pre_increment(int) noexcept
	-> decltype(std::declval<T>().operator++(), bool {})
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool pre_increment(...) noexcept
    {
	return false;
    }

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

    static_assert(library::is_swappable<T>::value,
		  "T type must satisfy Swappable");

    static_assert(dereference(0),
		  "T type must support the dereference operator*()");

    static_assert(pre_increment(0),
		  "T type must support the pre-increment operator++()");

    static_assert(std::is_same<typename std::add_lvalue_reference<T>::type,
		               decltype(std::declval<T>().operator++())
		               >::value,
		  "The return value of operator++() must be an lvalue reference T&");

    constexpr static bool value = std::true_type::value;
};

template<typename T>
class name_requirement::iterator::is_legacy_iterator<T*>
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
