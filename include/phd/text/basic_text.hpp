#pragma once

#ifndef PHD_TEXT_BASIC_TEXT_HPP
#define PHD_TEXT_BASIC_TEXT_HPP

#include <phd/text/version.hpp>

#include <phd/text/basic_text_view.hpp>
#include <phd/text/text_traits.hpp>

#include <string>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Encoding, typename _NormalizationForm = nfkc,
		typename _Container = std::basic_string<encoding_code_unit_t<_Encoding>>>
	class basic_text : private basic_text_view<_Encoding, _NormalizationForm, _Container> {};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_BASIC_TEXT_HPP
