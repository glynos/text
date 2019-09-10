#pragma once

#ifndef PHD_TEXT_TEXT_HPP
#define PHD_TEXT_TEXT_HPP

#include <phd/text/basic_text.hpp>
#include <phd/text/char8_t.hpp>
#include <phd/text/encoding.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	using text    = basic_text<execution>;
	using wtext   = basic_text<wide_execution>;
	using u8text  = basic_text<utf8>;
	using u16text = basic_text<utf16>;
	using u32text = basic_text<utf32>;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_TEXT_HPP
