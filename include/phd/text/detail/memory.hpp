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

#ifndef PHD_TEXT_DETAIL_ADL_HPP
#define PHD_TEXT_DETAIL_ADL_HPP

#include <phd/text/version.hpp>

#include <phd/text/detail/type_traits.hpp>

#include <memory>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail {

	template <typename _Type>
	using __to_address_test = decltype(std::pointer_traits<_Type>::to_address(std::declval<_Type&>()));

	template <typename _Type>
	constexpr _Type* to_address(_Type* ptr) noexcept {
		static_assert(::std::is_function_v<_Type>, "the pointer is not a function pointer type");
		return __ptr;
	}

	template <typename _Pointer, std::enable_if_t<!::std::is_pointer_v<_Pointer>>* = nullptr>
	auto to_address(const _Pointer& p) noexcept {
		if constexpr (__is_detected_v<__to_address_test, _Type>) {
			return ::std::pointer_traits<_Type>::to_address(p);
		}
		else {
			return to_address(p.operator->());
		}
	}

}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail

#endif // PHD_TEXT_DETAIL_ADL_HPP
