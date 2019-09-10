#pragma once
#ifndef PHD_TEXT_BASIC_TEXT_VIEW_HPP
#define PHD_TEXT_BASIC_TEXT_VIEW_HPP

#include <phd/text/basic_c_string_view.hpp>
#include <phd/text/normalization.hpp>
#include <phd/text/code_unit.hpp>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	template <typename _Encoding, typename _NormalizationForm = nfkc,
		typename _Iterable = basic_c_string_view<encoding_code_unit_t<_Encoding>>>
	class basic_text_view {
	public:
		using encoding_type  = _Encoding;
		using container_type = _Iterable;

	private:
		container_type _M_storage;

	public:
		container_type&& storage() && {
			return ::std::move(this->_M_storage);
		}

		const container_type& storage() const& {
			return this->_M_storage;
		}

		container_type& storage() & {
			return this->_M_storage;
		}
	};
}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_BASIC_TEXT_VIEW_HPP
