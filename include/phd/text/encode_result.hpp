#pragma once

#ifndef PHD_TEXT_ENCODING_RESULT_HPP
#define PHD_TEXT_ENCODING_RESULT_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>
#include <phd/text/unicode_code_point.hpp>
#include <phd/text/encoding_error.hpp>

#include <phd/text/subrange.hpp>

#include <cstddef>
#include <array>
#include <utility>
#include <system_error>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Input, typename _Output, typename _State>
	struct encode_result {
		_Input input;
		_Output output;
		_State& state;
		encoding_errc error_code;
		bool handled_error;

		template <typename _InRange, typename _OutRange, typename _EncodingState>
		constexpr encode_result(_InRange&& __input, _OutRange&& __output, _EncodingState&& __state,
			encoding_errc __error_code = encoding_errc::ok)
		: encode_result(::std::forward<_InRange>(__input), ::std::forward<_OutRange>(__output),
			  ::std::forward<_EncodingState>(__state), __error_code, __error_code != encoding_errc::ok) {
		}

		template <typename _InRange, typename _OutRange, typename _EncodingState>
		constexpr encode_result(_InRange&& __input, _OutRange&& __output, _EncodingState&& __state,
			encoding_errc __error_code, bool __handled_error)
		: input(::std::forward<_InRange>(__input))
		, output(::std::forward<_OutRange>(__output))
		, state(::std::forward<_EncodingState>(__state))
		, error_code(__error_code)
		, handled_error(__handled_error) {
		}

		// TODO: when the standard catches up
		/* constexpr */ ::std::error_condition error() const {
			return make_error_condition(error_code);
		}
	};

	template <typename _Input, typename _Output, typename _State>
	struct decode_result {
		_Input input;
		_Output output;
		_State& state;
		encoding_errc error_code;
		bool handled_error;

		template <typename _InRange, typename _OutRange, typename _EncodingState>
		constexpr decode_result(_InRange&& __input, _OutRange&& __output, _EncodingState&& __state,
			encoding_errc __error_code = encoding_errc::ok)
		: decode_result(::std::forward<_InRange>(__input), ::std::forward<_OutRange>(__output),
			  ::std::forward<_EncodingState>(__state), __error_code, __error_code != encoding_errc::ok) {
		}

		template <typename _InRange, typename _OutRange, typename _EncodingState>
		constexpr decode_result(_InRange&& __input, _OutRange&& __output, _EncodingState&& __state,
			encoding_errc __error_code, bool __handled_error)
		: input(::std::forward<_InRange>(__input))
		, output(::std::forward<_OutRange>(__output))
		, state(::std::forward<_EncodingState>(__state))
		, error_code(__error_code)
		, handled_error(__handled_error) {
		}

		// TODO: when the standard catches up
		/* constexpr */ ::std::error_condition error() const {
			return make_error_condition(error_code);
		}
	};

	namespace __detail {
		template <typename _InputRange, typename _OutputRange, typename _State>
		using __reconstruct_encode_result_t
			= encode_result<__reconstruct_t<_InputRange>, __reconstruct_t<_OutputRange>, _State>;

		template <typename _InputRange, typename _OutputRange, typename _State>
		using __reconstruct_decode_result_t
			= decode_result<__reconstruct_t<_InputRange>, __reconstruct_t<_OutputRange>, _State>;

		template <typename _InputRange, typename _OutputRange, typename _InFirst, typename _InLast,
			typename _OutFirst, typename _OutLast, typename _State>
		constexpr decltype(auto) __reconstruct_encode_result(_InFirst&& __in_first, _InLast&& __in_last,
			_OutFirst&& __out_first, _OutLast&& __out_last, _State& __state, encoding_errc __error_code,
			bool __handled_error) {
			decltype(auto) __in_range = __reconstruct<_InputRange>(
				::std::forward<_InFirst>(__in_first), ::std::forward<_InLast>(__in_last));
			decltype(auto) __out_range = __reconstruct<_OutputRange>(
				::std::forward<_OutFirst>(__out_first), ::std::forward<_OutLast>(__out_last));
			return encode_result<_InputRange, _OutputRange, _State>(::std::forward<decltype(__in_range)>(__in_range),
				::std::forward<decltype(__out_range)>(__out_range), __state, __error_code, __handled_error);
		}

		template <typename _InputRange, typename _OutputRange, typename _InFirst, typename _InLast,
			typename _OutFirst, typename _OutLast, typename _State>
		constexpr decltype(auto) __reconstruct_encode_result(_InFirst&& __in_first, _InLast&& __in_last,
			_OutFirst&& __out_first, _OutLast&& __out_last, _State& __state,
			encoding_errc __error_code = encoding_errc::ok) {
			return __reconstruct_encode_result_t<_InputRange, _OutputRange>(::std::forward<_InFirst>(__in_first),
				::std::forward<_InLast>(__in_last), ::std::forward<_OutFirst>(__out_first),
				::std::forward<_OutLast>(__out_last), __state, __error_code, __error_code != encoding_errc::ok);
		}

		template <typename _InputRange, typename _OutputRange, typename _InFirst, typename _InLast,
			typename _OutFirst, typename _OutLast, typename _State>
		constexpr decltype(auto) __reconstruct_decode_result(_InFirst&& __in_first, _InLast&& __in_last,
			_OutFirst&& __out_first, _OutLast&& __out_last, _State& __state, encoding_errc __error_code,
			bool __handled_error) {
			decltype(auto) __in_range = __reconstruct<_InputRange>(
				::std::forward<_InFirst>(__in_first), ::std::forward<_InLast>(__in_last));
			decltype(auto) __out_range = __reconstruct<_OutputRange>(
				::std::forward<_OutFirst>(__out_first), ::std::forward<_OutLast>(__out_last));
			return decode_result<_InputRange, _OutputRange, _State>(::std::forward<decltype(__in_range)>(__in_range),
				::std::forward<decltype(__out_range)>(__out_range), __state, __error_code, __handled_error);
		}

		template <typename _InputRange, typename _OutputRange, typename _InFirst, typename _InLast,
			typename _OutFirst, typename _OutLast, typename _State>
		constexpr decltype(auto) __reconstruct_decode_result(_InFirst&& __in_first, _InLast&& __in_last,
			_OutFirst&& __out_first, _OutLast&& __out_last, _State& __state,
			encoding_errc __error_code = encoding_errc::ok) {
			return __reconstruct_decode_result_t<_InputRange, _OutputRange>(::std::forward<_InFirst>(__in_first),
				::std::forward<_InLast>(__in_last), ::std::forward<_OutFirst>(__out_first),
				::std::forward<_OutLast>(__out_last), __state, __error_code, __error_code != encoding_errc::ok);
		}
	} // namespace __detail

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_ENCODING_RESULT_HPP
