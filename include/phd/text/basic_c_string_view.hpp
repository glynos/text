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

#ifndef PHD_TEXT_BASIC_C_STRING_VIEW_HPP
#define PHD_TEXT_BASIC_C_STRING_VIEW_HPP

#include <phd/text/version.hpp>

#include <phd/text/char8_t.hpp>

#include <phd/text/detail/type_traits.hpp>

#include <cassert>
#include <string_view>
#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
#ifdef __cpp_char8_t
#else
		using arr8_t                            = char8_t[1];
		constexpr inline const arr8_t __u8_shim = {};
#endif

		template <typename C>
		constexpr inline decltype(auto) __empty_string() noexcept {
			static_assert(__always_false_v<C>, "unrecognized character type");
			return "";
		}

		template <>
		constexpr inline decltype(auto) __empty_string<char>() noexcept {
			return "";
		}

		template <>
		constexpr inline decltype(auto) __empty_string<wchar_t>() noexcept {
			return L"";
		}

		template <>
		constexpr inline decltype(auto) __empty_string<char8_t>() noexcept {
#ifdef __cpp_char8_t
			return u8"";
#else
			return (__u8_shim);
#endif
		}

		template <>
		constexpr inline decltype(auto) __empty_string<char16_t>() noexcept {
			return u"";
		}

		template <>
		constexpr inline decltype(auto) __empty_string<char32_t>() noexcept {
			return U"";
		}
	} // namespace __detail

	template <typename _CharType, typename _Traits = ::std::char_traits<_CharType>>
	class basic_c_string_view : public ::std::basic_string_view<_CharType, _Traits> {
	private:
		using __base_t = ::std::basic_string_view<_CharType, _Traits>;

		constexpr bool _M_last_element_check() const {
			return ((this->size() > 0) ? *(this->data() + this->size()) == '\0' : true);
		}

	public:
		using const_iterator         = typename __base_t::const_iterator;
		using const_pointer          = typename __base_t::const_pointer;
		using const_reverse_iterator = typename __base_t::const_reverse_iterator;
		using difference_type        = typename __base_t::difference_type;
		using iterator               = typename __base_t::iterator;
		using pointer                = typename __base_t::pointer;
		using reference              = typename __base_t::reference;
		using reverse_iterator       = typename __base_t::reverse_iterator;
		using size_type              = typename __base_t::size_type;
		using traits_type            = typename __base_t::traits_type;
		using value_type             = typename __base_t::value_type;

		constexpr basic_c_string_view()
		: basic_c_string_view(
			  static_cast<const_pointer>(__detail::__empty_string<_CharType>()), static_cast<size_type>(0)) {
		}

		constexpr basic_c_string_view(const_iterator __arg0, const_iterator __arg1)
#if defined(_ITERATOR_DEBUG_LEVEL) && _ITERATOR_DEBUG_LEVEL >= 1
		: __base_t(__arg0 == __arg1 ? __detail::__empty_string<_CharType>() : ::std::addressof(*__arg0),
			  ::std::distance(__arg0, __arg1)) {
#else
		: __base_t(::std::addressof(*__arg0), ::std::distance(__arg0, __arg1)) {
#endif
			assert(this->_M_last_element_check() && "non null-terminated c_string_view!");
		}

		constexpr basic_c_string_view(const_iterator __arg0, size_type __arg1)
#if defined(_ITERATOR_DEBUG_LEVEL) && _ITERATOR_DEBUG_LEVEL >= 1
		: __base_t(__arg0 == __arg1 ? __detail::__empty_string<_CharType>() : ::std::addressof(*__arg0),
			  ::std::distance(__arg0, __arg1)) {
#else
		: __base_t(::std::addressof(*__arg0), ::std::distance(__arg0, __arg1)) {
#endif
			assert(this->_M_last_element_check() && "non null-terminated c_string_view!");
		}

		template <typename _Arg0, typename _Arg1, typename... _Args,
			::std::enable_if_t<!(
			     ::std::disjunction_v<::std::is_same<__detail::__remove_cvref_t<_Arg0>, iterator>,
			          ::std::is_same<__detail::__remove_cvref_t<_Arg0>,
			               const_iterator>> && ::std::disjunction_v<::std::is_same<__detail::__remove_cvref_t<_Arg1>, iterator>, ::std::is_same<__detail::__remove_cvref_t<_Arg1>, const_iterator>>)>* = nullptr>
		constexpr basic_c_string_view(_Arg0&& __arg0, _Arg1&& __arg1, _Args&&... __args_)
		: __base_t(::std::forward<_Arg0>(__arg0), ::std::forward<_Arg1>(__arg1), ::std::forward<_Args>(__args_)...) {
			assert(this->_M_last_element_check() && "non null-terminated c_string_view!");
		}

		template <typename _Arg,
			::std::enable_if_t<!::std::is_same_v<__detail::__remove_cvref_t<_Arg>, basic_c_string_view>>* = nullptr>
		constexpr basic_c_string_view(_Arg&& __arg) : __base_t(::std::forward<_Arg>(__arg)) {
			assert(this->_M_last_element_check() && "non null-terminated c_string_view!");
		}

		constexpr basic_c_string_view(basic_c_string_view&&)      = default;
		constexpr basic_c_string_view(const basic_c_string_view&) = default;
		constexpr basic_c_string_view& operator=(basic_c_string_view&&) = default;
		constexpr basic_c_string_view& operator=(const basic_c_string_view&) = default;

		constexpr const_pointer c_str() const noexcept {
			return this->data();
		}
	};
}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

namespace std {

	template <typename _CharType, typename _Traits>
	struct hash<::phd::text::basic_c_string_view<_CharType, _Traits>> {
		size_t operator()(const ::phd::text::basic_c_string_view<_CharType, _Traits>& __c_string_) const {
			hash<::std::basic_string_view<_CharType, _Traits>> h;
			return h(__c_string_);
		}
	};

} // namespace std

#endif // PHD_TEXT_BASIC_C_STRING_VIEW_HPP
