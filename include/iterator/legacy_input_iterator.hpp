#pragma once

#include <type_traits>
#include <utility>

#include "feature-macros/include/feature_macros.hpp"
#include "library/equality_comparable.hpp"
#include "legacy_iterator.hpp"

#define LEGACY_INPUT_ITERATOR_DEPRECATED__

#if __cplusplus >= CXX20_STANDARD__
#  undef  LEGACY_INPUT_ITERATOR_DEPRECATED__
#  define LEGACY_INPUT_ITERATOR_DEPRECATED__ [[deprecated ("use input iterator concept")]]

#endif

namespace name_requirement
{
    namespace iterator
    {
	template<typename T>
	class LEGACY_INPUT_ITERATOR_DEPRECATED__ is_legacy_input_iterator;

	template<typename T>
	class is_legacy_input_iterator<T*>;
    }
}

template<typename T>
class name_requirement::iterator::is_legacy_input_iterator :
    public name_requirement::iterator::is_legacy_iterator<T>
{
private:
    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto no_equality(int) noexcept
	-> decltype(static_cast<bool>(std::declval<T>() != std::declval<T>()))
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool no_equality(...) noexcept
    {
	return false;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto arrow(int) noexcept
	-> decltype(std::declval<T>().operator->(), bool {})
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool arrow(...) noexcept
    {
	return false;
    }

public:
    using value_type = typename is_legacy_iterator<T>::value_type;
    using reference  = typename is_legacy_iterator<T>::reference;

    static_assert(no_equality(0),
		  "The T type must be able to test for non-equality");

    static_assert(arrow(0),
		  "The T type must support the arrow operator->()");

    static_assert(std::is_convertible<decltype(std::declval<T>().operator*()),
		                      reference
		                      >::value,
		  "The T::operator*() function method must return a reference");

    static_assert(std::is_convertible<reference, value_type>::value,
		  "The reference must be convertible to value_type");

    constexpr static bool value =
	std::true_type::value        &&
	is_legacy_iterator<T>::value &&
	library::is_equality_comparable<T, T>::value;
};

template<typename T>
class name_requirement::iterator::is_legacy_input_iterator<T*> :
    public name_requirement::iterator::is_legacy_iterator<T*>
{
public:
    constexpr static bool value = is_legacy_iterator<T*>::value;
};
