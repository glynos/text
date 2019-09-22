#pragma once
#ifndef PHD_TEXT_DECODE_VIEW_HPP
#define PHD_TEXT_DECODE_VIEW_HPP

#include <phd/text/decode_iterator.hpp>
#include <phd/text/error_handler.hpp>
#include <phd/text/encoding.hpp>
#include <phd/text/code_unit.hpp>

#include <string_view>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Encoding, typename _Range = ::std::basic_string_view<encoding_code_unit_t<_Encoding>>,
		typename _ErrorHandler = default_text_error_handler>
	class decode_view {
	private:
	public:
		using iterator = decode_iterator<_Range, _Encoding, _ErrorHandler>;
		using sentinel = decode_sentinel;
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_DECODE_VIEW_HPP
