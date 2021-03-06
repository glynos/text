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

#ifndef PHD_TEXT_BASIC_TEXT_VIEW_HPP
#define PHD_TEXT_BASIC_TEXT_VIEW_HPP

#include <phd/text/version.hpp>

#include <phd/text/code_unit.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/normalization.hpp>

#include <string_view>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Encoding, typename _NormalizationForm = nfkc,
		typename _Range        = ::std::basic_string_view<encoding_code_unit_t<_Encoding>>,
		typename _ErrorHandler = default_text_error_handler>
	class basic_text_view {
	public:
		using container_type     = _Range;
		using encoding_type      = _Encoding;
		using normalization_type = _NormalizationForm;
		using error_handler_type = _ErrorHandler;

	private:
		container_type _M_storage;
		encoding_type _M_encoding;
		normalization_type _M_normalization;
		error_handler_type _M_error_handler;

	public:
		container_type&& storage() && {
			return ::std::move(this->_M_storage);
		}

		const container_type& storage() const& {
			return this->_M_storage;
		}

		container_type& storage() & {
			return this->_M_storage;
		}
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_BASIC_TEXT_VIEW_HPP
