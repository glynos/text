#pragma once

#ifndef PHD_TEXT_EXECUTION_HPP
#define PHD_TEXT_EXECUTION_HPP

#include <phd/text/encode_result.hpp>
#include <phd/text/encoding_error.hpp>
#include <phd/text/unicode_code_point.hpp>

#include <phd/text/detail/type_traits.hpp>
#include <phd/text/detail/range.hpp>

#ifdef _WIN32
#include <phd/text/utf8.hpp>
#include <phd/text/utf16.hpp>
#include <phd/text/detail/windows.hpp>
#endif // Windows specific includes

#include <cuchar>
#include <cwchar>

#include <span>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	class execution {
	public:
		class __state {
		public:
			::std::mbstate_t narrow_state;

			__state() noexcept = default;
		};

		using state               = __state;
		using code_unit           = char;
		using code_point          = unicode_code_point;
		using is_decode_injective = ::std::false_type;
		using is_encode_injective = ::std::false_type;

		static inline constexpr code_unit replacement_code_unit = '?';

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

			code_point codepoint = __detail::__dereference(__init);
			__init               = __detail::__next(__init);
#ifdef WIN32
			if (__detail::windows::__determine_active_code_page() == CP_UTF8) {
				// just go straight to UTF8
				utf8 __u8enc{};
				typename utf8::state __intermediate_s{};
				auto __intermediate_result
					= __u8enc.encode(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output),
					     __intermediate_s, __detail::__pass_through_text_error_handler{});
				if constexpr (__call_error_handler) {
					if (__intermediate_result.error_code != encoding_errc::ok) {
						return __error_handler(execution{},
							__result_t(::std::move(__intermediate_result.input),
							     ::std::move(__intermediate_result.output), __s,
							     __intermediate_result.error_code));
					}
				}
				return __result_t(::std::move(__intermediate_result.input),
					::std::move(__intermediate_result.output), __s, __intermediate_result.error_code);
			}
			else {
				using __u16e               = __detail::__utf16_with<void, wchar_t, false>;
				using __intermediate_state = typename __u16e::state;

				__u16e __u16enc{};
				__intermediate_state __intermediate_s{};
				wchar_t __wide_intermediary[8];
				::std::span<wchar_t> __wide_write_buffer(__wide_intermediary);
				auto __intermediate_result = __u16enc.encode(::std::forward<_InputRange>(__input),
					__wide_write_buffer, __intermediate_s, __detail::__pass_through_text_error_handler{});
				if constexpr (__call_error_handler) {
					if (__intermediate_result.error_code != encoding_errc::ok) {
						return __error_handler(execution{},
							__result_t(::std::move(__intermediate_result.input),
							     ::std::forward<_OutputRange>(__output), __s, __intermediate_result.error_code));
					}
				}
				constexpr const ::std::size_t __state_count_max = 12;
				code_unit __intermediary_output[__state_count_max]{};
				int __used_default_char = false;
				::std::span<const wchar_t> __wide_read_buffer(
					__wide_intermediary, __intermediate_result.output.data());
				int __res = __detail::windows::WideCharToMultiByte(
					__detail::windows::__determine_active_code_page(), WC_ERR_INVALID_CHARS,
					__wide_read_buffer.data(), static_cast<int>(__wide_read_buffer.size()), __intermediary_output,
					__state_count_max, &replacement_code_unit, ::std::addressof(__used_default_char));
				if constexpr (__call_error_handler) {
					if (__res == 0) {
						return __error_handler(execution{},
							__result_t(::std::move(__intermediate_result.input),
							     ::std::forward<_OutputRange>(__output), __s,
							     __detail::windows::GetLastError() == ERROR_INSUFFICIENT_BUFFER
							          ? encoding_errc::insufficient_output_space
							          : encoding_errc::invalid_sequence));
					}
				}
				for (auto __intermediary_it = __intermediary_output; __res-- > 0;) {
					if constexpr (__call_error_handler) {
						if (__outit == __outlast) {
							return __error_handler(execution{},
								__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
								     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
								     encoding_errc::insufficient_output_space));
						}
					}
					__detail::__dereference(__outit) = __detail::__dereference(__intermediary_it);
					__outit                          = __detail::__next(__outit);
				}
				return __result_t(::std::move(__intermediate_result.input),
					__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
					__intermediate_result.error_code);
			}
#else
			code_unit __intermediary_output[MB_LEN_MAX]{};
			::std::size_t __res
				= ::std::c32rtomb(__intermediary_output, codepoint, ::std::addressof(__s.narrow_state));
			if constexpr (__call_error_handler) {
				if (__res == static_cast<::std::size_t>(-1)) {
					return __error_handler(execution{},
						__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
						     encoding_errc::invalid_sequence));
				}
			}
			for (auto __intermediary_it = __intermediary_output; __res-- > 0;) {
				if constexpr (__call_error_handler) {
					if (__outit == __outlast) {
						return __error_handler(execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
							     encoding_errc::insufficient_output_space));
					}
				}
				__detail::__dereference(__outit) = __detail::__dereference(__intermediary_it);
				__outit                          = __detail::__next(__outit);
			}
			return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
				__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
#endif // Windows is hell
		}

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

			if (__outit == __outlast) {
				return __error_handler(execution{},
					__result_t(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output), __s,
					     encoding_errc::insufficient_output_space));
			}

#ifdef _WIN32
			if (__detail::windows::__determine_active_code_page() == CP_UTF8) {
				// just use utf8 directly
				// just go straight to UTF8
				utf8 __u8enc{};
				typename utf8::state __intermediate_s{};
				auto __intermediate_result
					= __u8enc.decode(::std::forward<_InputRange>(__input), ::std::forward<_OutputRange>(__output),
					     __intermediate_s, __detail::__pass_through_text_error_handler{});
				if constexpr (__call_error_handler) {
					if (__intermediate_result.error_code != encoding_errc::ok) {
						return __error_handler(execution{},
							__result_t(::std::move(__intermediate_result.input),
							     ::std::move(__intermediate_result.output), __s,
							     __intermediate_result.error_code));
					}
				}
				return __result_t(::std::move(__intermediate_result.input),
					::std::move(__intermediate_result.output), __s, __intermediate_result.error_code);
			}
#endif
			constexpr const ::std::size_t __state_count_max   = 12;
			code_unit __intermediary_input[__state_count_max] = { __detail::__dereference(__init), {} };
			__init                                            = __detail::__next(__init);
			::std::size_t __state_count                       = 1;
			::std::size_t __state_offset                      = 0;
			for (; __state_count < __state_count_max; ++__state_count) {
				char32_t __intermediary_output{};
#ifdef _WIN32
				using __u16e                                 = __detail::__utf16_with<void, wchar_t, false>;
				using __intermediate_state                   = typename __u16e::state;
				constexpr const int __wide_intermediary_size = 4;
				wchar_t __wide_intermediary[__wide_intermediary_size]{};
				int __res = __detail::windows::MultiByteToWideChar(
					__detail::windows::__determine_active_code_page(), MB_ERR_INVALID_CHARS, __intermediary_input,
					static_cast<int>(__state_count), __wide_intermediary, __wide_intermediary_size);
				if (__res == 0) {
					if (__detail::windows::GetLastError() == ERROR_NO_UNICODE_TRANSLATION) {
						// loopback; we might just not have enough code units
						if constexpr (__call_error_handler) {
							if (__init == __inlast) {
								return __error_handler(execution{},
									__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
									     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
									     encoding_errc::incomplete_sequence));
							}
						}
						__intermediary_input[__state_count] = __detail::__dereference(__init);
						__init                              = __detail::__next(__init);
						continue;
					}
					if constexpr (__call_error_handler) {
						return __error_handler(execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
							     encoding_errc::invalid_sequence));
					}
				}

				__u16e __u16enc{};
				__intermediate_state __intermediate_s{};
				auto __intermediate_result
					= __u16enc.decode(c_wstring_view(__wide_intermediary, static_cast<::std::size_t>(__res)),
					     ::std::forward<_OutputRange>(__output), __intermediate_s,
					     __detail::__pass_through_text_error_handler{});
				if constexpr (__call_error_handler) {
					if (__intermediate_result.error_code != encoding_errc::ok) {
						return __error_handler(execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     ::std::move(__intermediate_result.output), __s,
							     __intermediate_result.error_code));
					}
				}
				return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
					::std::move(__intermediate_result.output), __s, __intermediate_result.error_code);
#else
				::std::size_t __res = ::std::mbrtoc32(::std::addressof(__intermediary_output),
					::std::addressof(__intermediary_input[__state_offset]), __state_count,
					::std::addressof(__s.narrow_state));

				switch (__res) {
				case static_cast<::std::size_t>(-2):
					// cycle around and continue
					__init = __detail::__next(__init);
					if constexpr (__call_error_handler) {
						if (__init == __inlast) {
							return __error_handler(execution{},
								__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
								     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
								     encoding_errc::incomplete_sequence));
						}
					}
					__intermediary_input[__state_count] = __detail::__dereference(__init);
					break;
				case static_cast<::std::size_t>(-3):
					__detail::__dereference(__outit) = __intermediary_output;
					__state_offset                   = __state_count;
					__outit                          = __detail::__next(__outit);
					return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
				case static_cast<::std::size_t>(-1):
					if constexpr (__call_error_handler) {
						// OH GOD PANIC AAAAAAH
						// seriously we're out of spec here:
						// everything has gone to shit
						// even the narrow_state is unspecified ;;
						return __error_handler(execution{},
							__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
							     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
							     encoding_errc::invalid_sequence));
					}
					else {
						break;
					}
				case static_cast<::std::size_t>(0):
					__init = __detail::__next(__init);
					return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
				default:
					// 0 means null character; ok
					__detail::__dereference(__outit) = __intermediary_output;
					__outit                          = __detail::__next(__outit);
					__init                           = __detail::__next(__init);
					return __result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
						__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
				}
#endif
			}
			if constexpr (__call_error_handler) {
				// if it was invalid, we would have caught it before
				// this is for incomplete sequences only
				return __error_handler(execution{},
					__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
					     __detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s,
					     encoding_errc::incomplete_sequence));
			}
			else {
				// ... I mean.
				// You asked for it???
				__result_t(__detail::__reconstruct<_UInputRange>(__init, __inlast),
					__detail::__reconstruct<_UOutputRange>(__outit, __outlast), __s, encoding_errc::ok);
			}
		}
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_EXECUTION_HPP
