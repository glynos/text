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

#ifndef PHD_TEXT_DETAIL_WINDOWS_HPP
#define PHD_TEXT_DETAIL_WINDOWS_HPP

#ifdef _WIN32

#pragma push_macro("NOMINMAX")
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("VC_EXTRALEAN")

#define NOMINMAX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1

#ifdef _MSC_VER
#include <cstddef>
#include <ciso646>
#include <cwchar>
#include <locale>
#endif

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail { namespace windows {

	extern "C" {
#include <Windows.h>
	}

	inline int __determine_active_code_page() noexcept {
#if defined(_STL_LANG) || defined(_YVALS_CORE_H) || defined(_STDEXT)
		// Removed in later versions of VC++
		if (___lc_codepage_func() == CP_UTF8) {
			return CP_UTF8;
		}
#endif // VC++ stuff

#if !defined(_KERNELX) && !defined(_ONECORE)
		if (!AreFileApisANSI()) {
			return CP_OEMCP;
		}
#endif // !defined(_KERNELX) && !defined(_ONECORE)

		return CP_ACP;
	}
}}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail::windows

#pragma pop_macro("VC_EXTRALEAN")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOMINMAX")

#endif // Windows shit

#endif // PHD_TEXT_DETAIL_WINDOWS_HPP
