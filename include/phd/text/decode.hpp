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

#ifndef PHD_TEXT_DECODE_HPP
#define PHD_TEXT_DECODE_HPP

#include <phd/text/c_string_view.hpp>
#include <phd/text/code_point.hpp>
#include <phd/text/default_encoding.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/state.hpp>
#include <phd/text/unbounded.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <span>
#include <string>

namespace phd::text {

	template <typename _Input, typename _Output, typename _Encoding, typename _State, typename _ErrorHandler>
	constexpr void decode_into(_Input&& __input, _Output&& __output, _Encoding&& __encoding, _State& __state,
	     _ErrorHandler&& __error_handler) {
		using _UInput         = __detail::__remove_cvref_t<_Input>;
		using _UOutput        = __detail::__remove_cvref_t<_Output>;
		using _InputValueType = __detail::__range_value_type_t<_UInput>;
		// using _OutputValueType = __detail::__range_value_type_t<_UOutput>;
		using _WorkingInput  = ::std::conditional_t<::std::is_array_v<_UInput>,
               ::std::conditional_t<__detail::__is_character_v<_InputValueType>, basic_c_string_view<_InputValueType>,
                    ::std::span<_InputValueType>>,
               _UInput>;
		using _WorkingOutput = _UOutput; /*::std::conditional_t<::std::is_array_v<_UOutput>,
		                                      ::std::span<_OutputValueType>, _UOutput>;*/

		_WorkingInput __working_input(::std::forward<_Input>(__input));
		_WorkingOutput __working_output(::std::forward<_Output>(__output));

		for (;;) {
			auto __result = __encoding.decode(__working_input, __working_output, __state, __error_handler);
			if (__result.error_code != encoding_errc::ok) {
				break;
			}
			if (__detail::__adl::__adl_empty(__result.input)) {
				break;
			}
			__working_input  = ::std::move(__result.input);
			__working_output = ::std::move(__result.output);
		}
	}

	template <typename _Input, typename _Encoding, typename _State, typename _ErrorHandler>
	auto decode(_Input&& __input, _Encoding&& __encoding, _State& __state, _ErrorHandler&& __error_handler) {
		using _UEncoding   = __detail::__remove_cvref_t<_Encoding>;
		using __code_point = encoding_code_point_t<_UEncoding>;

		::std::basic_string<__code_point> __output{};
		if constexpr (__detail::__is_detected_v<__detail::__detect_adl_size, _Input>) {
			// NOTE: any ol' estimate will do
			__output.reserve(__detail::__adl::__adl_size(__input) / 2);
		}
		decode_into(::std::forward<_Input>(__input), phd::text::unbounded_view(::std::back_inserter(__output)),
		     ::std::forward<_Encoding>(__encoding), __state, ::std::forward<_ErrorHandler>(__error_handler));
		return __output;
	}

	template <typename _Input, typename _Encoding, typename _ErrorHandler>
	auto decode(_Input&& __input, _Encoding&& __encoding, _ErrorHandler&& __error_handler) {
		using _UEncoding = __detail::__remove_cvref_t<_Encoding>;
		using _State     = encoding_state_t<_UEncoding>;

		_State __s{};
		return decode(::std::forward<_Input>(__input), ::std::forward<_Encoding>(__encoding), __s,
		     ::std::forward<_ErrorHandler>(__error_handler));
	}

	template <typename _Input, typename _Encoding>
	auto decode(_Input&& __input, _Encoding&& __encoding) {
		return decode(
		     ::std::forward<_Input>(__input), ::std::forward<_Encoding>(__encoding), default_text_error_handler{});
	}

	template <typename _Input>
	auto decode(_Input&& __input) {
		using _UInput   = __detail::__remove_cvref_t<_Input>;
		using _Encoding = default_encoding_t<__detail::__range_value_type_t<_UInput>>;
		return decode(::std::forward<_Input>(__input), _Encoding{});
	}

} // namespace phd::text

#endif // PHD_TEXT_DECODE_HPP
