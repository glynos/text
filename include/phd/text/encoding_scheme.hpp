#pragma once

#ifndef PHD_TEXT_ENCODING_SCHEME_HPP
#define PHD_TEXT_ENCODING_SCHEME_HPP

#include <phd/text/version.hpp>

#include <phd/text/state.hpp>
#include <phd/text/code_point.hpp>
#include <phd/text/code_unit.hpp>
#include <phd/text/is_code_point_replaceable.hpp>
#include <phd/text/is_code_unit_replaceable.hpp>
#include <phd/text/is_ignorable_error_handler.hpp>
#include <phd/text/is_bidirectional_encoding.hpp>
#include <phd/text/subrange.hpp>
#include <phd/text/encode_result.hpp>

#include <phd/text/detail/word_iterator.hpp>
#include <phd/text/endian.hpp>

#include <cstddef>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Encoding, endian _Endian = endian::native, typename _Byte = ::std::byte>
	class encoding_scheme {
	private:
		using __unwrapped_encoding = __detail::__remove_cvref_t<__detail::__unwrap_t<_Encoding>>;
		using __base_code_unit     = encoding_code_unit_t<__unwrapped_encoding>;

	public:
		using encoding_type = _Encoding;
		using code_point    = encoding_code_point_t<__unwrapped_encoding>;
		using code_unit     = _Byte;
		using state         = encoding_state_t<__unwrapped_encoding>;

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		constexpr auto decode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_decode_result_t<_UInputRange, _UOutputRange, state>;
			using _InByteIt
				= __detail::__word_iterator<__base_code_unit, __detail::__range_iterator_t<_UInputRange>, _Endian>;
			using _InByteSen
				= __detail::__word_iterator<__base_code_unit, __detail::__range_sentinel_t<_UInputRange>, _Endian>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

			auto __init   = __detail::__adl::__adl_cbegin(__input);
			auto __inlast = __detail::__adl::__adl_cend(__input);
			subrange<_InByteIt, _InByteSen> __inbytes(
				_InByteIt(::std::move(__init)), _InByteSen(::std::move(__inlast)));
			auto __result = this->_M_encoding.decode(__inbytes, ::std::forward<_OutputRange>(__output), __s,
				::std::forward<_ErrorHandler>(__error_handler));
			return __result_t(
				__detail::__reconstruct<_UInputRange>(__result.input.begin().base(), __result.input.end().base()),
				__detail::__reconstruct<_UOutputRange>(::std::move(__result.output)), __s);
		}

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		constexpr auto encode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_encode_result_t<_UInputRange, _UOutputRange, state>;
			using _OutByteIt
				= __detail::__word_iterator<__base_code_unit, __detail::__range_iterator_t<_UOutputRange>, _Endian>;
			using _OutByteSen = __detail::__word_sentinel<__detail::__range_sentinel_t<_UOutputRange>>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

			auto __outit   = __detail::__adl::__adl_begin(__output);
			auto __outlast = __detail::__adl::__adl_end(__output);
			subrange<_OutByteIt, _OutByteSen> __outwords(
				_OutByteIt(::std::move(__outit)), _OutByteSen(::std::move(__outlast)));
			auto __result        = this->_M_encoding.encode(::std::forward<_InputRange>(__input), __outwords, __s,
                    ::std::forward<_ErrorHandler>(__error_handler));
			auto __resultoutit   = __result.output.begin().base();
			auto __resultoutlast = __result.output.end().base();
			return __result_t(__detail::__reconstruct<_UInputRange>(__result.input),
				__detail::__reconstruct<_UOutputRange>(__resultoutit, __resultoutlast), __s);
		}

	private:
		_Encoding _M_encoding;
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_ENCODING_SCHEME_HPP
