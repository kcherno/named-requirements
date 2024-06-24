#pragma once

#include <type_traits>
#include <utility>
#include <limits>

namespace name_requirement
{
    template<typename T>
    struct is_container;
}

template<typename T>
struct name_requirement::is_container {
private:
    template<typename A, typename B>
    struct is_representable_by final {
	constexpr static bool is_representable() noexcept
	{
	    static_assert((std::numeric_limits<A>::max() <=
			   std::numeric_limits<B>::max()),
			  "size_type must be large enough to represent "
			  "all positive values of difference_type");

	    return (std::numeric_limits<A>::max() <=
		    std::numeric_limits<B>::max());
	}

	constexpr static bool value = is_representable();
    };

public:
    using value_type      = typename T::value_type; // TODO(#1): erasable C++11
    using reference       = typename T::reference;
    using const_reference = typename T::const_reference;
    using iterator        = typename T::iterator;
    using const_iterator  = typename T::const_iterator;
    using difference_type = typename T::difference_type;
    using size_type       = typename T::size_type;

    auto begin() const 
	-> decltype(static_cast<const_iterator>(std::declval<const T>().begin()));

    auto end() const
	-> decltype(static_cast<const_iterator>(std::declval<const T>().end()));

    auto begin()
	-> decltype(static_cast<iterator>(std::declval<T>().begin()));

    auto end()
	-> decltype(static_cast<iterator>(std::declval<T>().end()));

    auto cbegin()
	-> decltype(static_cast<const_iterator>(std::declval<T>().cbegin()));

    auto cend()
	-> decltype(static_cast<const_iterator>(std::declval<T>().cend()));

    // TODO(#2): a <=> b C++20

    auto operator==(T)
	-> decltype(static_cast<bool>(std::declval<T>() == std::declval<T>()));

    auto operator!=(T)
	-> decltype(static_cast<bool>(std::declval<T>() != std::declval<T>()));

    auto swappable()
	-> decltype(static_cast<void>(std::declval<T&>().swap(std::declval<T&>())));

    auto size()
	-> decltype(static_cast<size_type>(std::declval<T>().size()));

    auto max_size()
	-> decltype(static_cast<size_type>(std::declval<T>().max_size()));

    auto empty()
	-> decltype(static_cast<bool>(std::declval<T>().empty()));

    constexpr static bool value =
	std::is_convertible<iterator, const_iterator>::value &&
	
	std::is_same<difference_type,
		     typename
		     std::iterator_traits<iterator>::difference_type
		     >::value &&

	std::is_same<difference_type,
		     typename
		     std::iterator_traits<const_iterator>::difference_type
		     >::value &&

	is_representable_by<difference_type, size_type>::value &&
	
	std::is_default_constructible<T>::value &&
	std::is_copy_constructible<T>::value    &&
	std::is_move_constructible<T>::value    &&
	std::is_copy_assignable<T>::value       &&
	std::is_move_assignable<T>::value       &&
	std::is_destructible<T>::value;
};
