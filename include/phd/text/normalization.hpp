#pragma once

#ifndef PHD_TEXT_NORMALIZATION_HPP
#define PHD_TEXT_NORMALIZATION_HPP

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <bool __is_compatibility>
	struct __nfc;
	template <bool __is_compatibility>
	struct __nfkd;

	struct nfc;
	struct nfd;
	struct nfkc;
	struct nfkd;

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_NORMALIZATION_HPP
