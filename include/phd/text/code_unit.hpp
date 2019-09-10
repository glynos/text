#pragma once

#ifndef PHD_TEXT_CODE_UNIT_HPP
#define PHD_TEXT_CODE_UNIT_HPP

#include <phd/text/version.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _T>
	struct encoding_code_unit {
		using type = typename _T::code_unit;
	};

	template <typename _T>
	using encoding_code_unit_t = typename encoding_code_unit<_T>::type;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_CODE_UNIT_HPP
