#pragma once

#include <utility>

#include "feature-macros/include/feature_macros.hpp"

#define SWAPPABLE_DEPRECATED__

#if   __cplusplus >= CXX20_STANDARD__
#  undef  SWAPPABLE_DEPRECATED__
#  define SWAPPABLE_DEPRECATED__ [[deprecated ("use std::swappable concepts")]]

#elif __cplusplus >= CXX17_STANDARD__
#  undef  SWAPPABLE_DEPRECATED__
#  define SWAPPABLE_DEPRECATED__ [[deprecated ("use std::is_swappable variants")]]

#endif

namespace name_requirement
{
    namespace library
    {
	using std::swap;

	template<typename T, typename U = T>
	class SWAPPABLE_DEPRECATED__ is_swappable;
    }
}

template<typename T, typename U>
class name_requirement::library::is_swappable {
private:
    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto swappable(int) noexcept
	-> decltype(swap(std::declval<T&>(), std::declval<U&>()),
		    swap(std::declval<U&>(), std::declval<T&>()), bool {})
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool swappable(...) noexcept
    {
	return false;
    }

public:
    constexpr static bool value = swappable(0);
};
