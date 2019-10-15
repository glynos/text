// ============================================================================
//
// phd.text
// Copyright © 2019 JeanHeyd "ThePhD" Meneide
// Contact: phdofthehouse@gmail.com
//
// Commercial License Usage
// Licensees holding valid commercial phd.text licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and JeanHeyd "ThePhD" Meneide.
// For licensing terms and conditions see your agreement. For
// further information contact phdofthehouse@gmail.com.
//
// GNU General Public License Usage
// Alternatively, this file may be used under the terms of GNU General
// Public license version 3. The licenses are as published by the Free
// Software Foundation and appearing in the file LICENSE included in the
// packaging of this file. Please review the following information to
// ensure the GNU General Public License requirements will
// be met: https://www.gnu.org/licenses/gpl-3.0.html.
//
// ============================================================================

#pragma once

#ifndef PHD_TEXT_UNBOUNDED_HPP
#define PHD_TEXT_UNBOUNDED_HPP

#include <phd/text/detail/range.hpp>

#include <iterator>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	struct infinity_sentinel_t {
		template <typename _Left>
		friend constexpr bool operator==(const _Left&, const infinity_sentinel_t&) {
			return false;
		}

		template <typename _Right>
		friend constexpr bool operator==(const infinity_sentinel_t&, const _Right&) {
			return false;
		}

		template <typename _Left>
		friend constexpr bool operator!=(const _Left&, const infinity_sentinel_t&) {
			return true;
		}

		template <typename _Right>
		friend constexpr bool operator!=(const infinity_sentinel_t&, const _Right&) {
			return true;
		}
	};

	inline constexpr infinity_sentinel_t infinity_sentinel = {};

	template <typename _It>
	class unbounded_view {
	private:
		_It _M_it;

	public:
		using iterator        = _It;
		using const_iterator  = iterator;
		using sentinel        = infinity_sentinel_t;
		using const_sentinel  = sentinel;
		using pointer         = __detail::__iterator_pointer_t<iterator>;
		using const_pointer   = pointer;
		using reference       = __detail::__iterator_reference_t<iterator>;
		using const_reference = reference;
		using value_type      = __detail::__iterator_value_type_t<iterator>;
		using difference_type = __detail::__iterator_pointer_t<iterator>;

		constexpr unbounded_view() noexcept = default;

		constexpr unbounded_view(iterator __it) noexcept : _M_it(::std::move(__it)) {
		}
		constexpr unbounded_view(iterator __it, sentinel) noexcept : unbounded_view(::std::move(__it)) {
		}

		constexpr iterator begin() const noexcept {
			return this->_M_it;
		}
		constexpr sentinel end() const noexcept {
			return sentinel{};
		}
	};
}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_UNBOUNDED_HPP
