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
	template <typename>
	class basic_utf8;
	template <typename>
	class basic_utf16;
	template <typename>
	class basic_utf32;
	using utf8  = basic_utf8<char8_t>;
	using utf16 = basic_utf16<char16_t>;
	using utf32 = basic_utf32<char32_t>;

	class nfc;
	class nfd;
	class nfkc;
	class nfkd;

	template <typename, typename, typename, typename>
	class basic_text_view;
#if 0
	using text_view = basic_text_view<execution, nfkc, ::std::basic_string_view<char, ::std::char_traits<char>>>;
	using wtext_view
		= basic_text_view<wide_execution, nfkc, ::std::basic_string_view<wchar_t, ::std::char_traits<wchar_t>>>;
	using u8text_view  = basic_text_view<utf8, nfkc, ::std::basic_string_view<char8_t, ::std::char_traits<char8_t>>>;
	using u16text_view = basic_text_view<utf16, nfkc, ::std::basic_string_view<char16_t, ::std::char_traits<char16_t>>>;
	using u32text_view = basic_text_view<utf32, nfkc, ::std::basic_string_view<char32_t, ::std::char_traits<char32_t>>>;
#endif

	template <typename, typename, typename, typename>
	class basic_text;

#if 0
	using text  = basic_text<execution, nfkc, ::std::basic_string<char, ::std::char_traits<char>, ::std::allocator<char>>>;
	using wtext = basic_text<wide_execution, nfkc,
		::std::basic_string<wchar_t, ::std::char_traits<wchar_t>, ::std::allocator<wchar_t>>>;
	using u8text
		= basic_text<utf8, nfkc, ::std::basic_string<char8_t, ::std::char_traits<char8_t>, ::std::allocator<char8_t>>>;
	using u16text
		= basic_text<utf16, nfkc, ::std::basic_string<char16_t, ::std::char_traits<char16_t>, ::std::allocator<char16_t>>>;
	using u32text
		= basic_text<utf32, nfkc, ::std::basic_string<char32_t, ::std::char_traits<char32_t>, ::std::allocator<char32_t>>>;
#endif

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_FORWARD_HPP
