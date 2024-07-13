#pragma once

#include <concepts>

#include "container.hpp"

namespace name_requirement::container_requirement
{
    template<typename T>
    concept ReservableContainer =
	Container<T> && requires(T c, typename T::size_type n)
	{
	    { c.capacity() } -> std::same_as<typename T::size_type>;
	    { c.reserve(n) };
	    { c.shrink_to_fit() };
	};
}
