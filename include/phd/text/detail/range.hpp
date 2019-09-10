#pragma once

#ifndef PHD_TEXT_DETAIL_RANGE_HPP
#define PHD_TEXT_DETAIL_RANGE_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/adl.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail {

	template <typename _It>
	constexpr auto __dereference(_It&& __it) noexcept(noexcept(*::std::forward<_It>(__it)))
		-> decltype(*::std::forward<_It>(__it)) {
		return *::std::forward<_It>(__it);
	}

	template <typename _It>
	constexpr auto __next(_It&& __it) noexcept(noexcept(++::std::forward<_It>(__it)))
		-> decltype(++::std::forward<_It>(__it)) {
		return ++::std::forward<_It>(__it);
	}

	template <typename _It>
	constexpr auto __prev(_It&& __it) noexcept(noexcept(::std::prev(::std::forward<_It>(__it))))
		-> decltype(::std::prev(::std::forward<_It>(__it))) {
		return ::std::prev(::std::forward<_It>(__it));
	}

	template <typename _It>
	using __iterator_value_type_t = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::value_type;

	template <typename _It>
	using __iterator_pointer_t = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::pointer;

	template <typename _It>
	using __iterator_reference_t = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::reference;

	template <typename _It>
	using __iterator_difference_type_t =
		typename ::std::iterator_traits<::std::remove_reference_t<_It>>::difference_type;

	template <typename _It>
	using __iterator_category_t = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_category;

	template <typename _It, typename = void>
	struct __iterator_concept_or_fallback {
		using type = __iterator_category_t<_It>;
	};

	template <typename _It>
	struct __iterator_concept_or_fallback<_It,
		::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept>> {
		using type = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_concept;
	};

	template <typename _It>
	using __iterator_concept_or_fallback_t =
		typename __iterator_concept_or_fallback<::std::remove_reference_t<_It>>::type;

	template <typename _It>
	using __iterator_concept_t = __iterator_concept_or_fallback_t<_It>;

	template <typename _Tag, typename _It>
	inline constexpr bool __is_iterator_concept_or_better_v = ::std::is_base_of_v<_Tag, __iterator_concept_t<_It>>;

	template <typename _Range>
	using __range_iterator_t = decltype(__adl::__adl_begin(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

	template <typename _Range>
	using __range_sentinel_t = decltype(__adl::__adl_end(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

	template <typename _Range>
	using __range_value_type_t = __iterator_value_type_t<__range_iterator_t<_Range>>;

	template <typename _Range>
	using __range_pointer_t = __iterator_pointer_t<__range_iterator_t<_Range>>;

	template <typename _Range>
	using __range_reference_t = __iterator_reference_t<__range_iterator_t<_Range>>;

	template <typename _Range>
	using __range_difference_type_t = __iterator_difference_type_t<__range_iterator_t<_Range>>;

	template <typename _Range>
	using __range_iterator_category_t = __iterator_category_t<__range_iterator_t<_Range>>;

	template <typename _Range>
	using __range_iterator_concept_t = __iterator_concept_t<__range_iterator_t<_Range>>;

	template <typename _Tag, typename _Range>
	inline constexpr bool __is_range_iterator_concept_or_better_v
		= ::std::is_base_of_v<_Tag, __range_iterator_concept_t<_Range>>;

}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail

#endif // PHD_TEXT_DETAIL_ADL_HPP
