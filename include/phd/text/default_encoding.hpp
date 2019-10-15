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

#ifndef PHD_TEXT_DEFAULT_ENCODING_HPP
#define PHD_TEXT_DEFAULT_ENCODING_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>
#include <phd/text/utf8.hpp>
#include <phd/text/utf16.hpp>
#include <phd/text/utf32.hpp>
#include <phd/text/execution.hpp>
#include <phd/text/wide_execution.hpp>
#include <phd/text/encoding_scheme.hpp>

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

	template <>
	class default_encoding<::std::byte> {
	public:
		using type = encoding_scheme<utf8, endian::native, ::std::byte>;
	};

	template <typename _Type>
	using default_encoding_t = typename default_encoding<_Type>::type;

	template <typename _Type>
	using default_encoding_t = typename default_encoding<_Type>::type;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_DEFAULT_ENCODING_HPP
