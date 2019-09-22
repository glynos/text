#pragma once

#ifndef PHD_TEXT_IS_UNICODE_CODE_POINT_HPP
#define PHD_TEXT_IS_UNICODE_CODE_POINT_HPP

#include <phd/text/forward.hpp>

#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Type>
	struct is_unicode_code_point
	: ::std::integral_constant<bool,
		  ::std::is_same_v<_Type, unicode_code_point> || ::std::is_same_v<_Type, unicode_scalar_value>> {};

	template <typename _Type>
	constexpr inline bool is_unicode_code_point_v = is_unicode_code_point<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_UNICODE_CODE_POINT_HPP
