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

#ifndef PHD_TEXT_VERSION_HPP
#define PHD_TEXT_VERSION_HPP

#include <cstddef>
#include <cstdint>

#define phd_text_text_iterator 201912L
#define phd_text_encodings 201912L
#define phd_text_text_view 201912L
#define phd_text_text 201912L

#if defined(_GLIBCXX__)

#define PHD_TEXT_LIBSTDCXX 1
#define PHD_TEXT_LIBCXX 0
#define PHD_TEXT_LIBVCXX 0

#elif defined(_LIBCPP_VERSION)

#define PHD_TEXT_LIBSTDCXX 0
#define PHD_TEXT_LIBCXX 1
#define PHD_TEXT_LIBVCXX 0

#else

#define PHD_TEXT_LIBSTDCXX 0
#define PHD_TEXT_LIBCXX 0
#define PHD_TEXT_LIBVCXX 1

#endif

#ifndef PHD_TEXT_ABI_NAMESPACE
#define PHD_TEXT_ABI_NAMESPACE __0
#endif // ABI namespace

namespace phd::text {
	// 4 bits per MAJOR MINOR PATCH
	inline constexpr unsigned long version = 10000L;
} // namespace phd::text

#endif // PHD_TEXT_CHAR8_T_HPP
