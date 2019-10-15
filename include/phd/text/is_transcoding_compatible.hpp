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

#ifndef PHD_TEXT_IS_TRANSCODING_COMPATIBLE_HPP
#define PHD_TEXT_IS_TRANSCODING_COMPATIBLE_HPP

#include <phd/text/version.hpp>

#include <phd/text/is_unicode_code_point.hpp>
#include <phd/text/code_point.hpp>
#include <phd/text/code_unit.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _To, typename _From>
	struct is_bitwise_transcoding_compatible : ::std::false_type {};

	template <typename _To, typename _From>
	constexpr inline bool is_bitwise_transcoding_compatible_v = is_bitwise_transcoding_compatible<_To, _From>::value;

	template <typename _From, typename _To>
	struct is_transcoding_compatible
	: ::std::integral_constant<bool,
		  is_bitwise_transcoding_compatible_v<_From,
		       _To> || ::std::is_same_v<_To, _From> || ::std::is_same_v<encoding_code_point_t<_To>, encoding_code_point_t<_From>>> {
	};

	template <typename _From, typename _To>
	constexpr bool is_transcoding_compatible_v = is_transcoding_compatible<_To, _From>::value;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_IS_TRANSCODING_COMPATIBLE_HPP
