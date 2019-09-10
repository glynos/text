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
		struct __is_ignorable_error_handler_sfinae : std::false_type {};

		template <typename _Type>
		struct __is_ignorable_error_handler_sfinae<_Type,
			std::enable_if_t<__detail::__is_detected_v<__is_ignorable_error_handler_test, _Type>>>
		: std::integral_constant<bool, _Type::assume_valid::value> {};
	} // namespace __detail

	template <typename _Type>
	struct is_ignorable_error_handler : __detail::__is_ignorable_error_handler_sfinae<_Type> {};

	template <typename _Type>
	constexpr inline bool is_ignorable_error_handler_v = is_ignorable_error_handler<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_TRANSPARENT_ERROR_HANDLER_HPP
