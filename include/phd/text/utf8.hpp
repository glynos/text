#pragma once

#ifndef PHD_TEXT_UTF8_HPP
#define PHD_TEXT_UTF8_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>
#include <phd/text/detail/unicode.hpp>
#include <phd/text/empty_state.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/is_ignorable_error_handler.hpp>
#include <phd/text/unicode_code_point.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <array>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {
	namespace __detail {
		template <typename _Derived = void, typename _CodeUnit = char8_t, bool __overlong_allowed = false,
			bool __surrogates_allowed = false, bool __use_overlong_null_only = false>
		struct __utf8_with {
		private:
			using __self_t = typename std::conditional<std::is_void_v<_Derived>, __utf8_with, _Derived>::type;

		public:
			using state               = __detail::__empty_state;
			using code_unit           = _CodeUnit;
			using code_point          = unicode_code_point;
			using is_decode_injective = std::true_type;
			using is_encode_injective = std::true_type;

			template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
			static constexpr auto encode(
				_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
				using _UInputRange                 = __detail::__remove_cvref_t<_InputRange>;
				using _UOutputRange                = __detail::__remove_cvref_t<_OutputRange>;
				using _UErrorHandler               = __detail::__remove_cvref_t<_ErrorHandler>;
				using __result_t                    = encode_result<_UInputRange, _UOutputRange, state>;
				constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

				auto __init   = __detail::__adl::__adl_cbegin(__input);
				auto __inlast = __detail::__adl::__adl_cend(__input);

				if (__init == __inlast) {
					// an exhausted sequence is fine
					return __result_t(std::forward<_InputRange>(__input), std::forward<_OutputRange>(__output),
						__s, encoding_errc::ok);
				}

				auto __outit   = __detail::__adl::__adl_begin(__output);
				auto __outlast = __detail::__adl::__adl_end(__output);

				code_point __codepoint = __detail::__dereference(__init);
				__init                 = __detail::__next(__init);

				if constexpr (__call_error_handler) {
					if (__codepoint > __detail::__last_code_point) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_output));
					}
					if constexpr (!__surrogates_allowed) {
						if (__detail::__is_surrogate(__codepoint)) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::invalid_output));
						}
					}
				}

				if constexpr (__use_overlong_null_only) {
					if (__codepoint == 0) {
						// overlong MUTF-8
						constexpr char8_t payload[] = { 0b11000000u, 0b10000000u };
						for (std::size_t i = 0; i < static_cast<std::size_t>(2); ++i) {
							if constexpr (__call_error_handler) {
								if (__outit == __outlast) {
									return __error_handler(__self_t{},
										__result_t(_UInputRange(__init, __inlast),
										     _UOutputRange(__outit, __outlast), __s,
										     encoding_errc::insufficient_output_space));
								}
							}
							__detail::__dereference(__outit) = static_cast<code_unit>(payload[i]);
							__outit                          = __detail::__next(__outit);
						}
					}
				}

				if constexpr (__call_error_handler) {
					if (__outit == __outlast) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::insufficient_output_space));
					}
				}

				constexpr char8_t __first_mask_continuation_values[][2] = {
					{ 0b01111111, __detail::__start_1byte_continuation },
					{ 0b00011111, __detail::__start_2byte_continuation },
					{ 0b00001111, __detail::__start_3byte_continuation },
					{ 0b00000111, __detail::__start_4byte_continuation },
					{ 0b00000011, __detail::__start_5byte_continuation },
					{ 0b00000001, __detail::__start_6byte_continuation },
				};

				int __length                          = __detail::__decode_length<__overlong_allowed>(__codepoint);
				int __lengthindex                     = __length - 1;
				const auto& __first_mask_continuation = __first_mask_continuation_values[__lengthindex];
				const char8_t& __first_mask           = __first_mask_continuation[0];
				const char8_t& __first_continuation   = __first_mask_continuation[1];
				int __current_shift                   = 6 * __lengthindex;

				__detail::__dereference(__outit) = static_cast<code_unit>(
					__first_continuation | static_cast<char8_t>((__codepoint >> __current_shift) & __first_mask));
				__outit = __detail::__next(__outit);

				if (__lengthindex > 0) {
					__current_shift -= 6;
					for (; __current_shift >= 0; __current_shift -= 6) {
						if constexpr (__call_error_handler) {
							if (__outit == __outlast) {
								return __error_handler(__self_t{},
									__result_t(_UInputRange(__init, __inlast),
									     _UOutputRange(__outit, __outlast), __s,
									     encoding_errc::insufficient_output_space));
							}
						}

						__detail::__dereference(__outit)
							= static_cast<code_unit>(__detail::__continuation_signature
							     | static_cast<char8_t>(
							            (__codepoint >> __current_shift) & __detail::__continuation_mask_value));
						__outit = __detail::__next(__outit);
					}
				}

				return __result_t(
					_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s, encoding_errc::ok);
			}

			template <typename _InputRange, typename _OutputRange, typename _ErrorHandler>
			static constexpr auto decode(
				_InputRange&& __input, _OutputRange&& __output, state& __s, _ErrorHandler&& __error_handler) {
				using _UInputRange                 = __detail::__remove_cvref_t<_InputRange>;
				using _UOutputRange                = __detail::__remove_cvref_t<_OutputRange>;
				using _UErrorHandler               = __detail::__remove_cvref_t<_ErrorHandler>;
				using __result_t                    = decode_result<_UInputRange, _UOutputRange, state>;
				constexpr bool __call_error_handler = !is_ignorable_error_handler_v<_UErrorHandler>;

				auto __init   = __detail::__adl::__adl_cbegin(__input);
				auto __inlast = __detail::__adl::__adl_cend(__input);

				if (__init == __inlast) {
					// the empty sequence is an OK sequence
					return __result_t(std::forward<_InputRange>(__input), std::forward<_OutputRange>(__output),
						__s, encoding_errc::ok);
				}

				auto __outit   = __detail::__adl::__adl_begin(__output);
				auto __outlast = __detail::__adl::__adl_end(__output);
				if constexpr (__call_error_handler) {
					if (__outit == __outlast) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::insufficient_output_space));
					}
				}
				else {
					(void)__outlast;
				}

				code_unit __b0     = __detail::__dereference(__init);
				__init             = __detail::__next(__init);
				std::size_t length = __detail::__sequence_length(static_cast<char8_t>(__b0));

				if constexpr (!__overlong_allowed) {
					if constexpr (__call_error_handler) {
						if (length > 4) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::overlong_sequence));
						}
					}
				}

				if (length == 1) {
					__detail::__dereference(__outit) = static_cast<code_point>(__b0);
					__outit                          = __detail::__next(__outit);
					return __result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s);
				}

				if constexpr (__call_error_handler) {
					const bool __is_invalid_cu = __detail::__is_invalid(static_cast<unsigned char>(__b0));
					if (__is_invalid_cu || __detail::__is_continuation(static_cast<unsigned char>(__b0))) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     __is_invalid_cu ? encoding_errc::invalid_sequence
							                     : encoding_errc::invalid_leading_sequence));
					}
				}

				std::array<unsigned char, 6> b{};
				b[0] = __b0;
				for (std::size_t i = 1; i < length; ++i) {
					if constexpr (__call_error_handler) {
						if (__init == __inlast) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::incomplete_sequence));
						}
					}
					b[i]   = __detail::__dereference(__init);
					__init = __detail::__next(__init);
					if (!__detail::__is_continuation(b[i])) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_trailing_sequence));
					}
				}

				code_point __decoded;
				switch (length) {
				case 2:
					__decoded = __detail::__decode(b[0], b[1]);
					break;
				case 3:
					__decoded = __detail::__decode(b[0], b[1], b[2]);
					break;
				case 4:
				default:
					__decoded = __detail::__decode(b[0], b[1], b[2], b[3]);
					break;
				}

				if constexpr (__call_error_handler) {
					if constexpr (!__overlong_allowed) {
						if (__detail::__is_overlong(__decoded, length)) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::overlong_sequence));
						}
					}
					if constexpr (!__surrogates_allowed) {
						if (__detail::__is_surrogate(__decoded)) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::invalid_output));
						}
					}
					if (__decoded > __detail::__last_code_point) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_output));
					}
				}
				// then everything is fine
				__detail::__dereference(__outit) = __decoded;
				__outit                          = __detail::__next(__outit);
				return __result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s);
			}
		};
	} // namespace __detail

	struct utf8 : __detail::__utf8_with<utf8, char8_t> {};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_UTF8_HPP
