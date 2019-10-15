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

#ifndef PHD_TEXT_IS_FULL_RANGE_REPRESENTABLE_HPP
#define PHD_TEXT_IS_FULL_RANGE_REPRESENTABLE_HPP

#include <phd/text/version.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <typename _Type>
		using __is_encode_injective_test = decltype(_Type::is_encode_injective);

		template <typename _Type>
		using __is_decode_injective_test = decltype(_Type::is_decode_injective);

		template <typename, typename = void>
		struct __is_full_range_representable_sfinae : ::std::false_type {};

		template <typename _Type>
		struct __is_full_range_representable_sfinae<_Type,
			::std::enable_if_t<__detail::__is_detected_v<__is_decode_injective_test,
			                        _Type> && __detail::__is_detected_v<__is_encode_injective_test, _Type>>>
		: ::std::integral_constant<bool, _Type::is_encode_injective::value && _Type::is_decode_injective::value> {};
	} // namespace __detail

	template <typename _Type>
	struct is_decode_injective
	: std::integral_constant<bool, __detail::__is_detected_v<__detail::__is_decode_injective_test, _Type>> {};

	template <typename _Type>
	constexpr inline bool is_decode_injective_v = is_decode_injective<_Type>::value;

	template <typename _Type>
	struct is_encode_injective
	: std::integral_constant<bool, __detail::__is_detected_v<__detail::__is_encode_injective_test, _Type>> {};

	template <typename _Type>
	constexpr inline bool is_encode_injective_v = is_encode_injective<_Type>::value;

	template <typename _Type>
	struct is_full_range_representable : __detail::__is_full_range_representable_sfinae<_Type> {};

	template <typename _Type>
	constexpr inline bool is_full_range_representable_v = is_full_range_representable<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_FULL_RANGE_REPRESENTABLE_HPP
