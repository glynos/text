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

#ifndef PHD_TEXT_ASCII_HPP
#define PHD_TEXT_ASCII_HPP

#include <phd/text/code_point.hpp>
#include <phd/text/code_unit.hpp>
#include <phd/text/empty_state.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/is_ignorable_error_handler.hpp>

#include <phd/text/detail/range.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	class ascii {
	public:
		using state                                                   = __detail::__empty_state;
		using code_unit                                               = char;
		using code_point                                              = unicode_code_point;
		using is_decode_injective                                     = ::std::true_type;
		using is_encode_injective                                     = ::std::false_type;
		inline static constexpr const ::std::size_t max_code_units    = 1;
		inline static constexpr const ::std::size_t max_code_points   = 1;
		inline static constexpr const code_unit replacement_code_unit = static_cast<code_unit>('?');

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		static constexpr auto decode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_decode_result_t<_UInputRange, _UOutputRange, state>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

			auto __init   = __detail::__adl::__adl_cbegin(__input);
			auto __inlast = __detail::__adl::__adl_cend(__input);
			if (__init == __inlast) {
				// an exhausted sequence is fine
				return __result_t(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output), __s,
					encoding_errc::ok);
			}

			auto __outit   = __detail::__adl::__adl_begin(__output);
			auto __outlast = __detail::__adl::__adl_end(__output);

			if constexpr (__call_error_handler) {
				if (__outit == __outlast) {
					return __error_handler(ascii{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::insufficient_output_space));
				}
			}
			else {
				(void)__outlast;
			}

			code_unit __unit = __detail::__dereference(__init);
			__init           = __detail::__next(__init);

			if constexpr (__call_error_handler) {
				if (static_cast<signed char>(__unit) < static_cast<signed char>(0)) {
					return __error_handler(ascii{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::invalid_output));
				}
			}

			__detail::__dereference(__outit) = __unit;
			__outit                          = __detail::__next(__outit);

			return __result_t(::std::move(__init), ::std::move(__inlast), ::std::move(__outit),
				::std::move(__outlast), __s, encoding_errc::ok);
		}

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		static constexpr auto encode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_encode_result_t<_UInputRange, _UOutputRange, state>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

			auto __init   = __detail::__adl::__adl_cbegin(__input);
			auto __inlast = __detail::__adl::__adl_cend(__input);
			if (__init == __inlast) {
				// an exhausted sequence is fine
				return __result_t(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output), __s,
					encoding_errc::ok);
			}

			auto __outit   = __detail::__adl::__adl_begin(__output);
			auto __outlast = __detail::__adl::__adl_end(__output);

			if constexpr (__call_error_handler) {
				if (__outit == __outlast) {
					return __error_handler(ascii{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::insufficient_output_space));
				}
			}
			else {
				(void)__outlast;
			}

			code_point __codepoint = __detail::__dereference(__init);
			__init                 = __detail::__next(__init);

			if constexpr (__call_error_handler) {
				if (__codepoint > __detail::__last_ascii_value) {
					return __error_handler(ascii{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::invalid_output));
				}
			}

			__detail::__dereference(__outit) = __codepoint;
			__outit                          = __detail::__next(__outit);

			return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
				__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
		}
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_ASCII_HPP
