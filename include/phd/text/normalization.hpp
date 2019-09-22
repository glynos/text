#pragma once

#ifndef PHD_TEXT_NORMALIZATION_HPP
#define PHD_TEXT_NORMALIZATION_HPP

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <bool __is_compatibility>
		struct __nfc {};
		template <bool __is_compatibility>
		struct __nfd {};
	} // namespace __detail

	class nfc : public __detail::__nfc<false> {};
	class nfd : public __detail::__nfd<false> {};
	class nfkc : public __detail::__nfc<true> {};
	class nfkd : public __detail::__nfd<true> {};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_NORMALIZATION_HPP
