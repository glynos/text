#pragma once

#ifndef PHD_TEXT_VERSION_HPP
#define PHD_TEXT_VERSION_HPP

#include <cstddef>
#include <cstdint>

#define phd_text_text_iterator 201912L
#define phd_text_encodings 201912L
#define phd_text_text_view 201912L
#define phd_text_text 201912L

#if defined(_GLIBCXX__)

#define PHD_TEXT_LIBSTDCXX 1
#define PHD_TEXT_LIBCXX 0
#define PHD_TEXT_LIBVCXX 0

#elif defined(_LIBCPP_VERSION)

#define PHD_TEXT_LIBSTDCXX 0
#define PHD_TEXT_LIBCXX 1
#define PHD_TEXT_LIBVCXX 0

#else

#define PHD_TEXT_LIBSTDCXX 0
#define PHD_TEXT_LIBCXX 0
#define PHD_TEXT_LIBVCXX 1

#endif

#ifndef PHD_TEXT_ABI_NAMESPACE
#define PHD_TEXT_ABI_NAMESPACE __0
#endif // ABI namespace

namespace phd::text {
	// 4 bits per MAJOR MINOR PATCH
	inline constexpr unsigned long version = 10000L;
} // namespace phd::text

#endif // PHD_TEXT_CHAR8_T_HPP
