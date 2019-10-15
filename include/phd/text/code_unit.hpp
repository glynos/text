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
