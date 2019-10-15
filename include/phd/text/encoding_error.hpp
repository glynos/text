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

#ifndef PHD_TEXT_ENCODING_ERROR_HPP
#define PHD_TEXT_ENCODING_ERROR_HPP

#include <phd/text/char8_t.hpp>
#include <phd/text/unicode_code_point.hpp>
#include <phd/text/encoding_error.hpp>

#include <cstddef>
#include <system_error>
#include <type_traits>
#include <string>
#include <exception>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	enum class encoding_errc : int {
		// just fine
		ok = 0x00,
		// input contains ill-formed sequences
		invalid_sequence = 0x01,
		// input contains incomplete sequences
		incomplete_sequence = 0x02,
		// input contains overlong encoding sequence (e.g. for utf8)
		overlong_sequence = 0x03,
		// output cannot receive all the completed code units
		insufficient_output_space = 0x04,
		// sequence can be encoded but resulting code point is invalid (e.g., encodes a lone surrogate)
		invalid_output = 0x05,
		// leading code unit is wrong
		invalid_leading_sequence = 0x06,
		// leading code units were correct, trailing code units were wrong
		invalid_trailing_sequence = 0x07
	};

	class encoding_error_category : public ::std::error_category {
	public:
#ifdef _MSC_VER
		encoding_error_category() noexcept : ::std::error_category() {
		}
#else
		constexpr encoding_error_category() noexcept : ::std::error_category() {
		}
#endif

		virtual const char* name() const noexcept override {
			return "encoding_error_category (phd::text)";
		}

		virtual ::std::string message(int condition) const override {
			using namespace ::std::string_literals;

			switch (static_cast<encoding_errc>(condition)) {
			case encoding_errc::ok:
				return "ok"s;
			case encoding_errc::invalid_sequence:
				return "input contains invalid sequence"s;
			case encoding_errc::incomplete_sequence:
				return "input contains incomplete sequence of code points"s;
			case encoding_errc::overlong_sequence:
				return "input contains overlong sequence for single code point"s;
			case encoding_errc::insufficient_output_space:
				return "output does not contain enough space for the operation"s;
			case encoding_errc::invalid_output:
				return "sequence can be encoded but it produces an invalid output"s;
			case encoding_errc::invalid_leading_sequence:
				return "sequence starts with an invalid code unit"s;
			case encoding_errc::invalid_trailing_sequence:
				return "sequence follows valid leading code units with illegal code units"s;
			default:
				// ::std::unreachable();
				::std::terminate();
			}
		}
	};

#if 0
	namespace __detail {
		constexpr const encoding_error_category __encoding_error_category = encoding_error_category{};
	}
#endif

#if 0
	inline constexpr const ::std::error_category& encoding_category() {
		return __detail::__encoding_error_category;
	}
#else
	inline const ::std::error_category& encoding_category() {
		static const encoding_error_category __val = encoding_error_category{};
		return __val;
	}
#endif

	inline ::std::error_condition make_error_condition(encoding_errc e) noexcept {
		return ::std::error_condition(static_cast<int>(e), encoding_error_category());
	}
}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

namespace std {
	template <>
	struct is_error_condition_enum<::phd::text::encoding_errc> : ::std::true_type {};
} // namespace std

#endif // PHD_TEXT_ENCODING_ERROR_HPP
