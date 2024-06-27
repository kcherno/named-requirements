#pragma once

#include <utility>

#include "feature-macros/include/feature_macros.hpp"

#define EQUALITY_COMPARABLE_DEPRECATED__

#if __cplusplus >= CXX20_STANDARD__
#  undef  EQUALITY_COMPARABLE_DEPRECATED__
#  define EQUALITY_COMPARABLE_DEPRECATED__ [[deprecated ("use std::equality_comparable concepts")]]

#endif

namespace name_requirement
{
    namespace library
    {
	template<typename T, typename U>
	class EQUALITY_COMPARABLE_DEPRECATED__ is_equality_comparable;
    }
}

template<typename T, typename U>
class name_requirement::library::is_equality_comparable {
private:
    IMMEDIATE_FUNCTION_SPECIFIER__
    static auto equality(int) noexcept
	-> decltype(static_cast<bool>(std::declval<T>() == std::declval<U>()))
    {
	return true;
    }

    IMMEDIATE_FUNCTION_SPECIFIER__
    static bool equality() noexcept
    {
	return false;
    }

public:
    constexpr static bool value = equality(0);
};
