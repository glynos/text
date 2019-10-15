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

#ifndef PHD_TEXT_C_STRING_VIEW_HPP
#define PHD_TEXT_C_STRING_VIEW_HPP

#include <phd/text/version.hpp>

#include <phd/text/basic_c_string_view.hpp>
#include <phd/text/char8_t.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	using c_string_view    = basic_c_string_view<char>;
	using c_wstring_view   = basic_c_string_view<wchar_t>;
	using c_u8string_view  = basic_c_string_view<char8_t>;
	using c_u16string_view = basic_c_string_view<char16_t>;
	using c_u32string_view = basic_c_string_view<char32_t>;

	inline namespace literals { inline namespace string_view_literals {
		// suffix for basic_c_string_view literals
		constexpr inline c_string_view operator"" _csv(const char* str_, size_t len_) noexcept {
			return c_string_view(str_, len_);
		}
#if defined(__cpp_char8_t)
		constexpr inline c_u8string_view operator"" _csv(const char8_t* str_, size_t len_) noexcept {
			return c_u8string_view(str_, len_);
		}
#else
		constexpr inline c_u8string_view operator"" _cu8sv(const char* str_, size_t len_) noexcept {
			return c_u8string_view(reinterpret_cast<const char8_t*>(str_), len_);
		}
#endif // char8_t hacks
		constexpr inline c_u16string_view operator"" _cu16sv(const char16_t* str_, size_t len_) noexcept {
			return c_u16string_view(str_, len_);
		}
		constexpr inline c_u32string_view operator"" _cu32sv(const char32_t* str_, size_t len_) noexcept {
			return c_u32string_view(str_, len_);
		}
		constexpr inline c_wstring_view operator"" _cwsv(const wchar_t* str_, size_t len_) noexcept {
			return c_wstring_view(str_, len_);
		}
	}} // namespace literals::string_view_literals

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_C_STRING_VIEW_HPP
