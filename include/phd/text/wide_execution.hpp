#pragma once

#ifndef PHD_TEXT_WIDE_EXECUTION_HPP
#define PHD_TEXT_WIDE_EXECUTION_HPP

#include <phd/text/c_string_view.hpp>
#include <phd/text/detail/windows.hpp>
#include <phd/text/empty_state.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/execution.hpp>
#include <phd/text/unicode_code_point.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <cuchar>
#include <cwchar>
#include <span>
#ifdef _MSC_VER
#include <wchar.h>
#endif
#include <iterator>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	class wide_execution {
	public:
#ifdef _WIN32
		using __wide_state = __detail::__empty_state;
#else
		class __wide_state {
		public:
			::std::mbstate_t wide_state;
			execution::state narrow_state;

			__state() = default;
		};
#endif // Windows

		// UTF32 on Linux; is fully injective
		// UTF16 on Windows; is fully injective
		using state               = __wide_state;
		using code_unit           = wchar_t;
		using code_point          = unicode_code_point;
		using is_decode_injective = ::std::true_type;
		using is_encode_injective = ::std::true_type;
#ifdef _WIN32
		inline static constexpr const ::std::size_t max_code_units  = 1;
		inline static constexpr const ::std::size_t max_code_points = 1;
#else
		inline static constexpr const ::std::size_t max_code_units  = 4;
		inline static constexpr const ::std::size_t max_code_points = 1;
#endif

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		static constexpr auto encode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_encode_result_t<_UInputRange, _UOutputRange, state>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;
#ifdef _WIN32
			using __u16e               = __detail::__utf16_with<void, wchar_t, false>;
			using __intermediate_state = typename __u16e::state;

			__u16e __u16enc{};
			__intermediate_state __intermediate_s{};
			auto __result
				= __u16enc.encode(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output),
				     __intermediate_s, __detail::__pass_through_text_error_handler_with<!__call_error_handler>{});
			if (__result.error_code != encoding_errc::ok) {
				return __error_handler(wide_execution{},
					__result_t(
					     ::std::move(__result.input), ::std::move(__result.output), __s, __result.error_code));
			}
			return __result_t(::std::move(__result.input), ::std::move(__result.output), __s, __result.error_code);
#else
			auto __init   = __detail::__adl::__adl_cbegin(__input);
			auto __inlast = __detail::__adl::__adl_cend(__input);

			if (__init == __inlast) {
				// an exhausted sequence is fine
				return __result_t(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output), __s,
					encoding_errc::ok);
			}

			auto __outit   = __detail::__adl::__adl_begin(__output);
			auto __outlast = __detail::__adl::__adl_end(__output);

			constexpr const ::std::size_t __state_max = 32;
			char __pray_for_state[__state_max + 1];
			char* __pray_start = &__pray_for_state[0];

			execution __exec{};
			auto __result
				= __exec.encode(::std::forward<_InputRange>(__input), ::std::span(__pray_start, __state_max),
				     __s.narrow_state, __detail::__pass_through_text_error_handler_with<!__call_error_handler>{});
			if constexpr (__call_error_handler) {
				if (__result.error_code != encoding_errc::ok) {
					return __error_handler(wide_execution{},
						__result_t(::std::move(__result.input),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     __result.error_code));
				}
			}

			auto __current_input = ::std::span(__pray_start, ::std::distance(__pray_start, __result.output.data()));
			code_unit __unit;
			::std::size_t __res = ::std::mbrtowc(
				&__unit, __current_input.data(), __current_input.size(), ::std::addressof(__s.wide_state));
			if (__res == static_cast<::std::size_t>(-1)) {
				// error: cry about it
				if constexpr (__call_error_handler) {
					return __error_handler(wide_execution{},
						__result_t(::std::move(__result.input),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::invalid_sequence));
				}
			}
			else if (static_cast<::std::size_t>(-2)) {
				// incomplete sequence
				if constexpr (__call_error_handler) {
					return __error_handler(wide_execution{},
						__result_t(::std::move(__result.input),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::incomplete_sequence));
				}
			}
			__detail::__dereference(__outit) = __unit;
			__outit                          = __detail::__next(__outit);

			return __result_t(::std::move(__result.input),
				__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, __result.error_code);
#endif // Windows shit
		}

		template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
		static constexpr auto decode(
			_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
			using _UInputRange   = __detail::__remove_cvref_t<_InputRange>;
			using _UOutputRange  = __detail::__remove_cvref_t<_OutputRange>;
			using _UErrorHandler = __detail::__remove_cvref_t<_ErrorHandler>;
			using __result_t     = __detail::__reconstruct_decode_result_t<_UInputRange, _UOutputRange, state>;
			constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;
#ifdef _WIN32
			using __u16e               = __detail::__utf16_with<void, wchar_t, false>;
			using __intermediate_state = typename __u16e::state;

			__u16e __u16enc{};
			__intermediate_state __intermediate_s{};
			auto __result
				= __u16enc.decode(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output),
				     __intermediate_s, __detail::__pass_through_text_error_handler_with<!__call_error_handler>{});
			if constexpr (__call_error_handler) {
				if (__result.error_code != encoding_errc::ok) {
					return __error_handler(wide_execution{},
						__result_t(::std::move(__result.input), ::std::move(__result.output), __s,
						     __result.error_code));
				}
			}
			return __result_t(::std::move(__result.input), ::std::move(__result.output), __s, __result.error_code,
				__result.handled_error);
#else

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
					return __error_handler(wide_execution{},
						__result_t(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output),
						     __s, encoding_errc::insufficient_output_space));
				}
			}

			constexpr const ::std::size_t __state_max = 32;
			char __pray_for_state[__state_max + 1]{};
			::std::size_t __state_count = 0;
			for (; __state_count < __state_max;) {
				code_unit __unit = __detail::__dereference(__init);
				__init           = __detail::__next(__init);
#ifdef _MSC_VER
				::std::size_t __res;
				errno_t __err = wcrtomb_s(::std::addressof(__res), __pray_for_state, __state_max, __unit,
					::std::addressof(__s.wide_state));
				if constexpr (__call_error_handler) {
					if (__err != 0) {
						// error: cry about it
						return __error_handler(wide_execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
							     encoding_errc::invalid_sequence));
					}
				}
				else {
					(void)__err;
				}
#else
				::std::size_t __res = ::std::wcrtomb(__pray_for_state, __unit, ::std::addressof(__s.wide_state));
#endif

				if (__res == static_cast<::std::size_t>(-1)) {
					if constexpr (__call_error_handler) {
						// error: cry about it
						return __error_handler(wide_execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
							     encoding_errc::invalid_sequence));
					}
				}
				else if (__res == 0 && ::std::mbsinit(::std::addressof(__s.wide_state)) == 0) {
					// mixed conversion potential?!
					// technically, not standard behavior, but I don't really care?
					// Mr. Steve Downey points out I'm slightly right
					// about my assumption here: C has an open DR for this
					// (DR 488, http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2059.htm#dr_488)
					// Another DR, DR 499 (http://www.open-std.org/jtc1/sc22/wg14/www/docs/n2059.htm#dr_498)
					// addresses thread safety issues, both should be
					// solved is this is to be anywhere near usable
					if constexpr (__call_error_handler) {
						if (__init == __inlast) {
							return __error_handler(wide_execution{},
								__result_t(::std::forward<_InputRange>(__input),
								     ::std::forward<_OutputRange>(__output), __s,
								     encoding_errc::incomplete_sequence));
						}
					}
					continue;
				}

				__state_count += __res;
				break;
			}

			execution __exec{};
			auto __result = __exec.decode(c_string_view(__pray_for_state, __state_count),
				::std::forward<_OutputRange>(__output), __s.narrow_state,
				__detail::__pass_through_text_error_handler_with<!__call_error_handler>{});
			if constexpr (__call_error_handler) {
				if (__result.error_code != encoding_errc::ok) {
					return __error_handler(wide_execution{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     ::std::move(__result.output), __s, __result.error_code));
				}
			}
			return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast), ::std::move(__result.output),
				__s, __result.error_code);
#endif
		}
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_WIDE_EXECUTION_HPP
