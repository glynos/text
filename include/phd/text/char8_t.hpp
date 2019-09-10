#pragma once

#ifndef PHD_TEXT_CHAR8_T_HPP
#define PHD_TEXT_CHAR8_T_HPP

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	using uchar8_t = unsigned char;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#if !defined(PHD_TEXT_CHAR8_T_TYPE) || !(PHD_TEXT_CHAR8_T_TYPE)
#if !defined(__cpp_char8_t)
using char8_t = ::phd::text::uchar8_t;
#endif // char8_t
#endif // Allow someone to define their own char8_t

#endif // PHD_TEXT_CHAR8_T_HPP
