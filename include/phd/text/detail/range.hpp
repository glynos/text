// ============================================================================
//
// phd.text
// Copyright © 2019 JeanHeyd "ThePhD" Meneide
// Contact: phdofthehouse@gmail.com
//
// Commercial License Usage
// Licensees holding valid commercial phd.text licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and JeanHeyd "ThePhD" Meneide.
// For licensing terms and conditions see your agreement. For
// further information contact phdofthehouse@gmail.com.
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of GNU General
// Public license version 3. The licenses are as published by the Free
// Software Foundation and appearing in the file LICENSE included in the
// packaging of this file. Please review the following information to
// ensure the GNU General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html.
//
// ============================================================================

#pragma once

#ifndef PHD_TEXT_DETAIL_RANGE_HPP
#define PHD_TEXT_DETAIL_RANGE_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/adl.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <iterator>
#include <type_traits>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	struct contiguous_iterator_tag {};

	namespace __detail {

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

		template <typename _It, typename _Diff>
		constexpr _It __next(_It __it, _Diff __diff) noexcept(noexcept(++__it)) {
			for (; __diff > 0; --__diff) {
				++__it;
			}
			return __it;
		}

		template <typename _It>
		constexpr auto __prev(_It&& __it) noexcept(noexcept(--::std::forward<_It>(__it)))
			-> decltype(--::std::forward<_It>(__it)) {
			return --::std::forward<_It>(__it);
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
		using __iterator_category_t =
			typename ::std::iterator_traits<::std::remove_reference_t<_It>>::iterator_category;

		template <typename _It, typename = void>
		struct __iterator_concept_or_fallback {
			using type = ::std::conditional_t<::std::is_pointer_v<__remove_cvref_t<_It>>, contiguous_iterator_tag,
				__iterator_category_t<_It>>;
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
		inline constexpr bool __is_iterator_concept_or_better_v
			= ::std::is_base_of_v<_Tag, __iterator_concept_t<_It>>;

		template <typename _Range>
		using __range_iterator_t
			= decltype(__adl::__adl_begin(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

		template <typename _Range>
		using __range_sentinel_t
			= decltype(__adl::__adl_end(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

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

	} // namespace __detail
}}     // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_DETAIL_ADL_HPP
