#pragma once

#ifndef PHD_TEXT_FORWARD_HPP
#define PHD_TEXT_FORWARD_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <typename, typename, bool, bool, bool>
		struct __utf8_with;

		template <typename, typename, bool>
		struct __utf16_with;

		template <typename, typename, bool>
		struct __utf32_with;

		struct __empty_state;
	} // namespace __detail

	using unicode_code_point   = char32_t;
	using unicode_scalar_value = char32_t;

	template <typename>
	struct locale_state;

	struct execution;
	struct wide_execution;
	struct utf8;
	struct utf16;
	struct utf32;

	struct nfc;
	struct nfd;
	struct nfkc;
	struct nfkd;

	template <typename Encoding, typename NormalizationForm, typename View>
	class basic_text_view;

	template <typename Encoding, typename NormalizationForm, typename Container>
	class basic_text;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_FORWARD_HPP
