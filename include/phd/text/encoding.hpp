#pragma once

#ifndef PHD_TEXT_ENCODING_HPP
#define PHD_TEXT_ENCODING_HPP

#include <phd/text/execution.hpp>
#include <phd/text/wide_execution.hpp>
#include <phd/text/ascii.hpp>
#include <phd/text/utf8.hpp>
#include <phd/text/utf16.hpp>
#include <phd/text/utf32.hpp>

#include <phd/text/is_transcoding_compatible.hpp>

namespace phd::text {

	template <>
	struct is_bitwise_transcoding_compatible<ascii, utf8> : ::std::true_type {};

} // namespace phd::text

#endif // PHD_TEXT_ENCODING_HPP
