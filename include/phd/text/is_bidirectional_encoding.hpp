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
