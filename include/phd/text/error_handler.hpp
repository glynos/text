#pragma once

#ifndef PHD_TEXT_ERROR_HANDLER_HPP
#define PHD_TEXT_ERROR_HANDLER_HPP

#include <phd/text/version.hpp>

#include <phd/text/c_string_view.hpp>
#include <phd/text/code_point.hpp>
#include <phd/text/detail/unicode.hpp>
#include <phd/text/encode_result.hpp>
#include <phd/text/encoding_error.hpp>
#include <phd/text/is_code_point_replaceable.hpp>
#include <phd/text/is_code_unit_replaceable.hpp>
#include <phd/text/is_unicode_code_point.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <climits>
#include <cstddef>
#include <exception>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {

		template <bool __assume_validity = false>
		struct __pass_through_text_error_handler_with {
			using assume_valid = ::std::integral_constant<bool, __assume_validity>;

			template <typename _Encoding, typename Result>
			constexpr auto operator()(const _Encoding&, Result __result) const {
				return __result;
			}
		};

		using __pass_through_text_error_handler = __pass_through_text_error_handler_with<false>;

	} // namespace __detail

	struct assume_valid_text_error_handler : __detail::__pass_through_text_error_handler_with<true> {};

	struct replacement_text_error_handler {
		template <typename _Encoding, typename _InputRange, typename _OutputRange, typename _State>
		constexpr auto operator()(
			const _Encoding& enc, encode_result<_InputRange, _OutputRange, _State> __result) const noexcept {
			using _UOutputRange = __detail::__remove_cvref_t<_OutputRange>;

			if (__result.error_code == encoding_errc::insufficient_output_space) {
				// BAIL
				return __result;
			}
			auto __outit   = __detail::__adl::__adl_begin(__result.output);
			auto __outlast = __detail::__adl::__adl_end(__result.output);
			if (__outit == __outlast) {
				// BAIL
				return __result;
			}

			if constexpr (is_code_unit_replaceable_v<_Encoding>) {
				(*__outit)      = _Encoding::replacement_code_unit;
				__outit         = __detail::__next(__outit);
				__result.output = __detail::__reconstruct<_UOutputRange>(::std::move(__outit), ::std::move(__outlast));
			}
			else {
				using __input_code_point = encoding_code_point_t<_Encoding>;
				__input_code_point __wut[2];
				if constexpr (is_code_point_replaceable_v<_Encoding>) {
					__wut[0] = static_cast<__input_code_point>(_Encoding::replacement_code_point);
				}
				else {
					__wut[0] = static_cast<__input_code_point>(is_unicode_code_point_v<__input_code_point>
						     ? __detail::__replacement
						     : __detail::__ascii_replacement);
				}
				__wut[1] = static_cast<__input_code_point>(0);
				const basic_c_string_view<__input_code_point> __wut_range(__wut, 1);

				_State __fresh_state{};
				auto __encresult = enc.encode(
					__wut_range, ::std::move(__result.output), __fresh_state, assume_valid_text_error_handler{});
				__result.output = ::std::move(__encresult.output);
			}

			__result.error_code = encoding_errc::ok;

			return __result;
		}

		template <typename _Encoding, typename _InputRange, typename _OutputRange, typename _State>
		constexpr auto operator()(const _Encoding&, decode_result<_InputRange, _OutputRange, _State> __result) const
			noexcept {
			using __output_code_point = encoding_code_point_t<_Encoding>;
			using _UOutputRange       = __detail::__remove_cvref_t<_OutputRange>;

			if (__result.error_code == encoding_errc::insufficient_output_space) {
				return __result;
			}

			auto __outit   = __detail::__adl::__adl_begin(__result.output);
			auto __outlast = __detail::__adl::__adl_end(__result.output);
			if (__outit == __outlast) {
				// BAIL
				return __result;
			}

			if constexpr (is_code_point_replaceable_v<_Encoding>) {
				(*__outit) = _Encoding::replacement_code_point;
			}
			else {
				if constexpr (is_unicode_code_point_v<__output_code_point>) {
					(*__outit) = static_cast<__output_code_point>(__detail::__replacement);
				}
				else {
					(*__outit) = static_cast<__output_code_point>(__detail::__ascii_replacement);
				}
			}
			__outit = __detail::__next(__outit);

			__result.output     = __detail::__reconstruct<_UOutputRange>(__outit, __outlast);
			__result.error_code = encoding_errc::ok;

			return __result;
		}
	};

	class throw_text_error_handler {
		template <typename _Encoding, typename _InputRange, typename _OutputRange, typename _State>
		constexpr auto operator()(
			const _Encoding& enc, encode_result<_InputRange, _OutputRange, _State> __result) const noexcept(false) {
			// create error condition and throw
			throw __result.error();
		}
	};

	class default_text_error_handler : public replacement_text_error_handler {};
}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE


#endif // PHD_TEXT_ERROR_HANDLER_HPP
