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

#ifndef PHD_TEXT_TRANSCODE_HPP
#define PHD_TEXT_TRANSCODE_HPP

#include <phd/text/code_point.hpp>
#include <phd/text/code_unit.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/state.hpp>
#include <phd/text/default_encoding.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>
#include <phd/text/unbounded.hpp>

#include <span>

namespace phd::text {

	template <typename _Input, typename _Output, typename _EncodingFrom, typename _EncodingTo, typename _StateFrom,
	     typename _StateTo, typename _ErrorHandlerFrom, typename _ErrorHandlerTo>
	constexpr void transcode_into(_Input&& __input, _Output&& __output, _EncodingFrom&& __encoding_from,
	     _EncodingTo&& __encoding_to, _StateFrom& __s_from, _StateTo& __s_to, _ErrorHandlerFrom&& __error_handler_from,
	     _ErrorHandlerTo&& __error_handler_to) {
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

		using _UEncodingFrom            = __detail::__remove_cvref_t<_EncodingFrom>;
		using __intermediate_code_point = encoding_code_point_t<_UEncodingFrom>;

		_WorkingInput __working_input(::std::forward<_Input>(__input));
		_WorkingOutput __working_output(::std::forward<_Output>(__output));

		__intermediate_code_point __intermediary_storage[8 + 1];
		::std::span<__intermediate_code_point> __scratch_space(__intermediary_storage, 8);
		for (;;) {
			auto __decode_result
			     = __encoding_from.decode(__working_input, __scratch_space, __s_from, __error_handler_from);
			if (__decode_result.error_code != encoding_errc::ok) {
				break;
			}
			::std::span<__intermediate_code_point> __intermediary_storage_used(
			     __intermediary_storage, __decode_result.output.data());
			auto __encode_result
			     = __encoding_to.encode(__intermediary_storage_used, __working_output, __s_to, __error_handler_to);
			if (__encode_result.error_code != encoding_errc::ok) {
				break;
			}
			if (__detail::__adl::__adl_empty(__decode_result.input)) {
				break;
			}
			__working_input  = ::std::move(__decode_result.input);
			__working_output = ::std::move(__encode_result.output);
		}
	}

	template <typename _Input, typename _EncodingFrom, typename _EncodingTo, typename _StateFrom, typename _StateTo>
	constexpr auto transcode(_Input&& __input, _EncodingFrom&& __encoding_from, _EncodingTo&& __encoding_to,
	     _StateFrom& __s_from, _StateTo& __s_to) {
		using _UToEncoding = __detail::__remove_cvref_t<_EncodingTo>;
		using __code_unit  = encoding_code_unit_t<_UToEncoding>;

		::std::basic_string<__code_unit> __output{};
		if constexpr (__detail::__is_detected_v<__detail::__detect_adl_size, _Input>) {
			// NOTE: any ol' estimate will do
			__output.reserve(__detail::__adl::__adl_size(__input) / 2);
		}

		transcode_into(::std::forward<_Input>(__input), phd::text::unbounded_view(::std::back_inserter(__output)),
		     ::std::forward<_EncodingFrom>(__encoding_from), ::std::forward<_EncodingTo>(__encoding_to), __s_from,
		     __s_to, phd::text::default_text_error_handler{}, phd::text::default_text_error_handler{});
		return __output;
	}

	template <typename _Input, typename _EncodingFrom, typename _EncodingTo>
	constexpr auto transcode(_Input&& __input, _EncodingFrom&& __encoding_from, _EncodingTo&& __encoding_to) {
		using _UEncodingFrom = __detail::__remove_cvref_t<_EncodingFrom>;
		using _UEncodingTo   = __detail::__remove_cvref_t<_EncodingTo>;
		using _StateFrom     = encoding_state_t<_UEncodingFrom>;
		using _StateTo       = encoding_state_t<_UEncodingTo>;

		_StateFrom __s_from{};
		_StateTo __s_to{};

		return transcode(::std::forward<_Input>(__input), ::std::forward<_EncodingFrom>(__encoding_from),
		     ::std::forward<_EncodingTo>(__encoding_to), __s_from, __s_to);
	}

	template <typename _Input, typename _EncodingTo>
	constexpr auto transcode(_Input&& __input, _EncodingTo&& __encoding_to) {
		using _uInput        = __detail::__remove_cvref_t<_Input>;
		using _UEncodingFrom = default_encoding_t<__detail::__range_value_type_t<_uInput>>;
		using _UEncodingTo   = __detail::__remove_cvref_t<_EncodingTo>;
		using _StateFrom     = encoding_state_t<_UEncodingFrom>;
		using _StateTo       = encoding_state_t<_UEncodingTo>;

		_StateFrom __s_from{};
		_StateTo __s_to{};

		return transcode(::std::forward<_Input>(__input), _UEncodingFrom{},
		     ::std::forward<_EncodingTo>(__encoding_to), __s_from, __s_to);
	}

} // namespace phd::text

#endif // PHD_TEXT_TRANSCODE_HPP
