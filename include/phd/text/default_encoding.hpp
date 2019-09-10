#pragma once

#ifndef PHD_TEXT_DEFAULT_ENCODING_HPP
#define PHD_TEXT_DEFAULT_ENCODING_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>
#include <phd/text/utf8.hpp>
#include <phd/text/utf16.hpp>
#include <phd/text/utf32.hpp>
#include <phd/text/execution.hpp>
#include <phd/text/wide_execution.hpp>

#include <phd/text/detail/type_traits.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Type>
	class default_encoding {
		static_assert(__detail::__always_false_v<_Type>, "there is no default encoding for this type");
	};

	template <>
	class default_encoding<char> {
	public:
		using type = execution;
	};

	template <>
	class default_encoding<wchar_t> {
	public:
		using type = wide_execution;
	};

	template <>
	class default_encoding<char8_t> {
	public:
		using type = utf8;
	};

	template <>
	class default_encoding<char16_t> {
	public:
		using type = utf16;
	};

	template <>
	class default_encoding<char32_t> {
	public:
		using type = utf32;
	};

	template <typename _Type>
	using default_encoding_t = typename default_encoding<_Type>::type;

	template <typename _Type>
	using default_encoding_t = typename default_encoding<_Type>::type;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_DEFAULT_ENCODING_HPP
