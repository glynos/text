#pragma once

#ifndef PHD_TEXT_IS_CODE_UNIT_REPLACEABLE_HPP
#define PHD_TEXT_IS_CODE_UNIT_REPLACEABLE_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/type_traits.hpp>

#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <typename _Type>
		using __is_code_unit_replaceable_test = decltype(_Type::replacement_code_unit);
	} // namespace __detail

	template <typename _Type>
	struct is_code_unit_replaceable : __detail::__is_detected<__detail::__is_code_unit_replaceable_test, _Type> {};

	template <typename _Type>
	constexpr inline bool is_code_unit_replaceable_v = is_code_unit_replaceable<_Type>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_CODE_UNIT_REPLACEABLE_HPP
