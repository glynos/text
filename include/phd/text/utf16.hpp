#pragma once

#ifndef PHD_TEXT_UTF16_HPP
#define PHD_TEXT_UTF16_HPP

#include <phd/text/code_point.hpp>
#include <phd/text/code_unit.hpp>
#include <phd/text/empty_state.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/forward.hpp>
#include <phd/text/is_ignorable_error_handler.hpp>

#include <phd/text/detail/range.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <typename _Derived = void, typename _CodeUnit = char16_t, bool surrogates_allowed = false>
		struct __utf16_with {
		private:
			using __self_t = typename std::conditional<std::is_void_v<_Derived>, __utf16_with, _Derived>::type;

		public:
			using state               = __detail::__empty_state;
			using code_unit           = _CodeUnit;
			using code_point          = unicode_code_point;
			using is_decode_injective = std::true_type;
			using is_encode_injective = std::true_type;


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
				if constexpr (__call_error_handler) {
					if (__init == __inlast) {
						// an exhausted sequence is fine
						return __result_t(std::forward<_InputRange>(__input),
							std::forward<_OutputRange>(__output), __s, encoding_errc::ok);
					}
				}
				else {
					(void)__inlast;
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

				char16_t __lead = static_cast<char16_t>(__detail::__dereference(__init));
				__init          = __detail::__next(__init);

				if (!__detail::__is_surrogate(__lead)) {
					__detail::__dereference(__outit) = static_cast<code_point>(__lead);
					__outit                          = __detail::__next(__outit);
					return __result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
						encoding_errc::ok);
				}
				if constexpr (__call_error_handler) {
					if (!__detail::__is_lead_surrogate(__lead)) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_leading_sequence));
					}
				}
				if constexpr (__call_error_handler) {
					if (__init == __inlast) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::incomplete_sequence));
					}
				}

				auto __trail = __detail::__dereference(__init);
				__init       = __detail::__next(__init);
				if constexpr (__call_error_handler) {
					if (!__detail::__is_trail_surrogate(__trail)) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_trailing_sequence));
					}
				}
				__detail::__dereference(__outit) = static_cast<code_point>(
					__detail::__combine_surrogates(static_cast<char16_t>(__lead), static_cast<char16_t>(__trail)));
				__outit = __detail::__next(__outit);

				return __result_t(
					_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s, encoding_errc::ok);
			}

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

				code_point __codepoint = __detail::__dereference(__init);
				__init                 = __detail::__next(__init);

				if constexpr (__call_error_handler) {
					if (__codepoint > __detail::__last_code_point) {
						return __error_handler(__self_t{},
							__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s,
							     encoding_errc::invalid_output));
					}
				}

				if (__codepoint <= __detail::__last_bmp_value) {
					__detail::__dereference(__outit) = static_cast<char16_t>(__codepoint);
					__outit                          = __detail::__next(__outit);
				}
				else {
					auto normal = __codepoint - __detail::__normalizing_value;
					auto lead   = __detail::__first_lead_surrogate
						+ ((normal & __detail::__lead_surrogate_bitmask) >> __detail::__lead_shifted_bits);
					auto trail
						= __detail::__first_trail_surrogate + (normal & __detail::__trail_surrogate_bitmask);

					__detail::__dereference(__outit) = static_cast<char16_t>(lead);
					__outit                          = __detail::__next(__outit);

					if constexpr (__call_error_handler) {
						if (__outit == __outlast) {
							return __error_handler(__self_t{},
								__result_t(_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast),
								     __s, encoding_errc::insufficient_output_space));
						}
					}
					__detail::__dereference(__outit) = static_cast<char16_t>(trail);
					__outit                          = __detail::__next(__outit);
				}

				return __result_t(
					_UInputRange(__init, __inlast), _UOutputRange(__outit, __outlast), __s, encoding_errc::ok);
			}
		};
	} // namespace __detail

	struct utf16 : __detail::__utf16_with<utf16, char16_t> {};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_UTF16_HPP
