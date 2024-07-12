#pragma once

#include <concepts>
#include <iterator>
#include <limits>

namespace name_requirement::container_requirement
{
    template<typename T>
    concept Container = requires {
	typename T::value_type;
	typename T::reference;
	typename T::const_reference;
	typename T::iterator;
	typename T::const_iterator;
	typename T::difference_type;
	typename T::size_type;

	requires std::destructible<typename T::value_type>;

	requires std::convertible_to<typename T::iterator,
	                             typename T::const_iterator>;

	requires std::forward_iterator<typename T::const_iterator>;

	requires std::same_as<typename T::difference_type,
	                      std::iter_difference_t<typename T::const_iterator>>;

	requires std::same_as<typename T::difference_type,
	                      std::iter_difference_t<typename T::iterator>>;

	requires std::numeric_limits<typename T::difference_type>::max() <=
	                             std::numeric_limits<typename T::size_type>::max();
    } &&

    std::destructible<T> &&
    std::semiregular<T>  && 
    std::movable<T>      &&

    requires(T a) {
	{ a.begin() }    -> std::same_as<typename T::iterator>;
	{ a.end() }      -> std::same_as<typename T::iterator>;
	{ a.cbegin() }   -> std::same_as<typename T::const_iterator>;
	{ a.cend() }     -> std::same_as<typename T::const_iterator>;
	{ a.size() }     -> std::same_as<typename T::size_type>;
	{ a.max_size() } -> std::same_as<typename T::size_type>;
	{ a.empty() }    -> std::same_as<bool>;

    } &&

    std::three_way_comparable<T, std::strong_ordering> &&
    std::equality_comparable<T>;
}
