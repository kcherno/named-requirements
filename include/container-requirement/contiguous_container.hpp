#pragma once

#include <iterator>

#include "container.hpp"

namespace name_requirement::container_requirement
{
    template<typename T>
    concept ContiguousContainer =
	Container<T>                                         &&
	std::contiguous_iterator<typename T::const_iterator> &&
	std::contiguous_iterator<typename T::iterator>;
}
