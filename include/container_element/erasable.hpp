#pragma once

#include <type_traits>

#include "feature-macros/include/cxx_standards.hpp"

#define ERASABLE_DEPRECATED__

#if __cplusplus >= CXX20_STANDARD__
#  undef  ERASABLE_DEPRECATED__
#  define ERASABLE_DEPRECATED__ [[deprecated ("use the std::destructible concept")]]

#endif

namespace name_requirement
{
    namespace container_element
    {
	template<typename T>
	struct ERASABLE_DEPRECATED__ is_erasable;

#if __cplusplus >= CXX17_STANDARD__

	template<typename T>
	inline constexpr auto is_erasable_v = is_erasable<T>::value;

#endif

    }
}

template<typename T>
struct name_requirement::container_element::is_erasable final {
    constexpr static bool value =
	(std::is_nothrow_destructible<T>::value || std::is_scalar<T>::value) &&
	(not (std::is_array<T>::value     ||
	      std::is_function<T>::value  ||
	      std::is_reference<T>::value ||
	      std::is_void<T>::value));
};
