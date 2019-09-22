#pragma once

#ifndef PHD_TEXT_DETAIL_ADL_HPP
#define PHD_TEXT_DETAIL_ADL_HPP

#include <phd/text/version.hpp>

#include <iterator>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail {
	// Blessed Overload Overlord Xeo,
	// may his name be praised.
	namespace __adl {
		// using ::std::cdata;
		using ::std::data;
		using ::std::empty;
		using ::std::size;

		using ::std::begin;
		using ::std::cbegin;
		using ::std::crbegin;
		using ::std::rbegin;

		using ::std::cend;
		using ::std::crend;
		using ::std::end;
		using ::std::rend;

		template <typename _Range>
		constexpr auto __adl_begin(_Range& __range) noexcept(noexcept(begin(__range))) -> decltype(begin(__range)) {
			return begin(__range);
		}

		template <typename _Range>
		constexpr auto __adl_cbegin(_Range& __range) noexcept(noexcept(cbegin(__range)))
			-> decltype(cbegin(__range)) {
			return cbegin(__range);
		}

		template <typename _Range>
		constexpr auto __adl_rbegin(_Range& __range) noexcept(noexcept(rbegin(__range)))
			-> decltype(rbegin(__range)) {
			return rbegin(__range);
		}

		template <typename _Range>
		constexpr auto __adl_crbegin(_Range& __range) noexcept(noexcept(crbegin(__range)))
			-> decltype(crbegin(__range)) {
			return crbegin(__range);
		}

		template <typename _Range>
		constexpr auto __adl_end(_Range& __range) noexcept(noexcept(end(__range))) -> decltype(end(__range)) {
			return end(__range);
		}

		template <typename _Range>
		constexpr auto __adl_cend(_Range& __range) noexcept(noexcept(cend(__range))) -> decltype(cend(__range)) {
			return cend(__range);
		}

		template <typename _Range>
		constexpr auto __adl_rend(_Range& __range) noexcept(noexcept(rend(__range))) -> decltype(rend(__range)) {
			return rend(__range);
		}

		template <typename _Range>
		constexpr auto __adl_crend(_Range& __range) noexcept(noexcept(crend(__range))) -> decltype(crend(__range)) {
			return crend(__range);
		}

		template <typename _Range>
		constexpr auto __adl_data(_Range& __range) noexcept(noexcept(data(__range))) -> decltype(data(__range)) {
			return data(__range);
		}

		template <typename _Range>
		constexpr auto __adl_size(_Range& __range) noexcept(noexcept(size(__range))) -> decltype(size(__range)) {
			return size(__range);
		}

		template <typename _Range>
		constexpr auto __adl_empty(_Range& __range) noexcept(noexcept(empty(__range))) -> decltype(empty(__range)) {
			return empty(__range);
		}
	} // namespace __adl

	template <typename _Range>
	using __detect_adl_size = decltype(__adl::__adl_size(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail

#endif // PHD_TEXT_DETAIL_ADL_HPP
