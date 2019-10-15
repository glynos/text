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

#ifndef PHD_TEXT_IS_BIDIRECTIONAL_ENCODING
#define PHD_TEXT_IS_BIDIRECTIONAL_ENCODING

#include <phd/text/version.hpp>

#include <phd/text/detail/type_traits.hpp>

#include <type_traits>
#include <span>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {
	namespace __detail {
		template <typename _Type, typename _Input, typename _Output, typename _State, typename _ErrorHandler>
		using __encode_backward_test = decltype(::std::declval<_Type>().encode_backward(::std::declval<_Input&>(),
			::std::declval<_Output&>(), ::std::declval<_State&>(), ::std::declval<_ErrorHandler&>()));

		template <typename _Type, typename _Input, typename _Output, typename _State, typename _ErrorHandler>
		using __decode_backward_test = decltype(std::declval<_Type&>().decode_backward(::std::declval<_Input&>(),
			::std::declval<_Output&>(), ::std::declval<_State&>(), ::std::declval<_ErrorHandler&>()));
	} // namespace __detail

	template <typename _Type, typename _Input, typename _Output, typename _State, typename _ErrorHandler>
	struct is_bidirectional_encoding
	: ::std::integral_constant<bool,
		  __detail::__is_detected_v<__detail::__decode_backward_test, _Type, _Input, _Output, _State,
		       _ErrorHandler> && __detail::__is_detected_v<__detail::__encode_backward_test, _Type, _Input, _Output, _State, _ErrorHandler>> {
	};

	template <typename _Type, typename _Input, typename _Output, typename _State, typename _ErrorHandler>
	constexpr inline bool is_bidirectional_encoding_v = is_bidirectional_encoding<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_BIDIRECTIONAL_ENCODING
