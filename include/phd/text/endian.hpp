
#pragma once

#ifndef PHD_TEXT_ENDIAN_HPP
#define PHD_TEXT_ENDIAN_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/windows.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	enum class endian {
#ifdef _WIN32
		little = 0,
		big    = 1,
#if defined(REG_DWORD) && (REG_DWORD == REG_DWORD_LITTLE_ENDIAN)
		native = little
#else
		native = big
#endif
#else
		little = __ORDER_LITTLE_ENDIAN__,
		big    = __ORDER_BIG_ENDIAN__,
		native = __BYTE_ORDER__
#endif
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_ENDIAN_HPP
