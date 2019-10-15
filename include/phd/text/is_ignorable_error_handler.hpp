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

#ifndef PHD_TEXT_IS_TRANSPARENT_ERROR_HANDLER_HPP
#define PHD_TEXT_IS_TRANSPARENT_ERROR_HANDLER_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/type_traits.hpp>

#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {
	namespace __detail {
		template <typename _Type>
		using __is_ignorable_error_handler_test = decltype(_Type::assume_valid);

		template <typename, typename = void>
		struct __is_ignorable_error_handler_sfinae : ::std::false_type {};

		template <typename _Type>
		struct __is_ignorable_error_handler_sfinae<_Type,
			::std::enable_if_t<__detail::__is_detected_v<__is_ignorable_error_handler_test, _Type>>>
		: ::std::integral_constant<bool, _Type::assume_valid::value> {};
	} // namespace __detail

	template <typename _Type>
	struct is_ignorable_error_handler : __detail::__is_ignorable_error_handler_sfinae<_Type> {};

	template <typename _Type>
	constexpr inline bool is_ignorable_error_handler_v = is_ignorable_error_handler<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_TRANSPARENT_ERROR_HANDLER_HPP
