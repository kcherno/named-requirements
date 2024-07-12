#pragma once

#include <concepts>

namespace name_requirement::library_wide
{
    template<typename T>
    concept CharTraits = requires {
	typename T::char_type;
	typename T::int_type;
	typename T::off_type;
	typename T::pos_type;
	typename T::state_type;

	requires std::default_initializable<typename T::state_type>;
	requires std::destructible<typename T::state_type>;
	requires std::copyable<typename T::state_type>;

    } &&

    requires(typename T::char_type c,
	     typename T::char_type d)
    {
	{ T::eq(c, d) }       -> std::same_as<bool>;
	{ T::lt(c, d) }       -> std::same_as<bool>;
	{ T::to_int_type(c) } -> std::same_as<typename T::int_type>;

    } &&

    requires(const typename T::char_type* p,
	     const typename T::char_type* q,
	     typename T::char_type* s,
	     typename T::char_type  c,
	     std::size_t n)
    {
	{ T::compare(p, q, n) } -> std::same_as<int>;
	{ T::length(p) }        -> std::same_as<std::size_t>;
	{ T::find(p, n, c) }    -> std::same_as<const typename T::char_type*>;
	{ T::move(s, p, n) }    -> std::same_as<typename T::char_type*>;
	{ T::copy(s, p, n) }    -> std::same_as<typename T::char_type*>;
	{ T::assign(s, n, c) }  -> std::same_as<typename T::char_type*>;

    } &&

    requires(typename T::char_type r, typename T::char_type d)
    {
	{ T::assign(r, d) };

    } &&

    requires(typename T::int_type e, typename T::int_type f)
    {
	{ T::not_eof(e) }        -> std::same_as<typename T::int_type>;
	{ T::to_char_type(e) }   -> std::same_as<typename T::char_type>;
	{ T::eq_int_type(e, f) } -> std::same_as<bool>;
	{ T::eof() }             -> std::same_as<typename T::int_type>;
    };
}
