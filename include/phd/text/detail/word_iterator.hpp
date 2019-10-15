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

#ifndef PHD_TEXT_WORD_ITERATOR_HPP
#define PHD_TEXT_WORD_ITERATOR_HPP

#include <phd/text/version.hpp>

#include <phd/text/endian.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>
#include <phd/text/detail/memory.hpp>

#include <cstddef>
#include <limits>
#include <climits>
#include <cstring>
#include <memory>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail {

	template <typename _It, typename _Word, endian _Endian>
	class __word_reference {
	private:
		using __base_iterator   = _It;
		using __void_value_type = __detail::__iterator_value_type_t<__base_iterator>;
		using __base_value_type
			= ::std::conditional_t<::std::is_void_v<__void_value_type>, ::std::byte, __void_value_type>;

	public:
		using value_type = _Word;

		__word_reference(__base_iterator __it) : _M_base_it(::std::move(__it)) {
		}

		__word_reference& operator=(value_type __val) {
			if constexpr (_Endian == endian::native) {
				__base_value_type __storage[sizeof(value_type) / sizeof(__base_value_type)];
				::std::memcpy(__storage, ::std::addressof(__val), sizeof(value_type));
				::std::copy_n(__storage, __adl::__adl_size(__storage), this->_M_base_it);
				return *this;
			}
			else if (_Endian == endian::little) {
				__base_value_type __storage[sizeof(value_type) / sizeof(__base_value_type)];
				::std::memcpy(__storage, ::std::addressof(__val), sizeof(value_type));
				::std::copy_n(__storage, __adl::__adl_size(__storage), this->_M_base_it);
				return *this;
			}
			else {
				__base_value_type __storage[sizeof(value_type) / sizeof(__base_value_type)];
				::std::memcpy(__storage, ::std::addressof(__val), sizeof(value_type));
				::std::copy_n(__storage, __adl::__adl_size(__storage), this->_M_base_it);
				return *this;
			}
		}

		value_type value() const {
			__base_value_type __storage[sizeof(value_type) / sizeof(__base_value_type)];
			value_type __val;
			if constexpr (_Endian == endian::native
				&& (endian::native != endian::big && endian::native != endian::little)) {
				static_assert(__always_false_constant_v<endian, _Endian>,
					"read value from byte stream to native endianness that is neither little nor big (byte "
					"order is impossible to infer from the standard)");
			}
			else if (_Endian == endian::little) {
				::std::copy_n(this->_M_base_it, __adl::__adl_size(__storage), __storage);
				::std::memcpy(::std::addressof(__val), ::std::addressof(__storage), __adl::__adl_size(__storage));
			}
			else if (_Endian == endian::big) {
				::std::reverse_copy(
					this->_M_base_it, ::std::next(this->_M_base_it, __adl::__adl_size(__storage)), __storage);
				::std::memcpy(::std::addressof(__val), ::std::addressof(__storage), __adl::__adl_size(__storage));
				return __val;
			}
			return __val;
		}

		operator value_type() const {
			return this->value();
		}

	private:
		__base_iterator _M_base_it;
	};

	template <typename _It>
	class __word_sentinel {
	public:
		using sentinel_type = _It;

		__word_sentinel() = default;
		__word_sentinel(sentinel_type __sen) : _M_base_sen(::std::move(__sen)) {
		}

		sentinel_type& base() & {
			return this->_M_base_sen;
		}

		const sentinel_type& base() const& {
			return this->_M_base_sen;
		}

		sentinel_type&& base() && {
			return ::std::move(this->_M_base_sen);
		}

	private:
		sentinel_type _M_base_sen;
	};

	template <typename _Derived, typename _Word, typename _It, endian _Endian, typename = void>
	class __category_word_iterator {
	private:
		using __base_iterator   = _It;
		using __sentinel        = __word_sentinel<_It>;
		using __base_reference  = __detail::__iterator_reference_t<__base_iterator>;
		using __base_value_type = __detail::__iterator_value_type_t<__base_iterator>;
		using __difference_type = __detail::__iterator_difference_type_t<__base_iterator>;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = _Word;

		static_assert(sizeof(__value_type) >= sizeof(__base_value_type),
			"the 'byte' type selected for the word_iterator must not be larger than the value_type of the "
			"iterator "
			"that "
			"it is meant to view");

		static constexpr inline __size_type __base_values_per_word = sizeof(__value_type) / sizeof(__base_value_type);

	public:
		using iterator_type     = __base_iterator;
		using iterator_category = __iterator_category_t<__base_iterator>;
		using difference_type   = __difference_type;
		using pointer           = _Word*;
		using value_type        = __value_type;
		using reference         = __word_reference<__base_iterator, _Word, _Endian>;

		__category_word_iterator() = default;
		__category_word_iterator(iterator_type __it) : _M_base_it(::std::move(__it)) {
		}

		iterator_type& base() & {
			return this->_M_base_it;
		}

		const iterator_type& base() const& {
			return this->_M_base_it;
		}

		iterator_type&& base() && {
			return ::std::move(this->_M_base_it);
		}

		_Derived operator++(int) const {
			auto __copy = this->_M_this();
			++__copy;
			return __copy;
		}

		_Derived& operator++() {
			this->_M_base_it += __base_values_per_word;
			return this->_M_this();
		}

		_Derived operator--(int) const {
			auto __copy = this->_M_this();
			--__copy;
			return __copy;
		}

		_Derived& operator--() {
			this->_M_base_it -= __base_values_per_word;
			return this->_M_this();
		}

		_Derived operator+(difference_type __by) const {
			auto __copy = this->_M_this();
			__copy += __by;
			return __copy;
		}

		_Derived& operator+=(difference_type __by) {
			if (__by < static_cast<difference_type>(0)) {
				return this->operator+=(-__by);
			}
			this->_M_base_it += __base_values_per_word * __by;
			return this->_M_this();
		}

		_Derived operator-(difference_type __by) const {
			auto __copy = this->_M_this();
			__copy -= __by;
			return __copy;
		}

		_Derived& operator-=(difference_type __by) {
			if (__by < static_cast<difference_type>(0)) {
				return this->operator+=(-__by);
			}
			this->_M_base_it -= __base_values_per_word * __by;
			return this->_M_this();
		}

		reference operator[](difference_type __index) {
			auto __copy = this->_M_this();
			__copy += __index;
			return *__copy;
		}

		reference operator*() const {
			return reference(this->_M_base_it);
		}

		friend bool operator==(const __category_word_iterator& __left, const __category_word_iterator& __right) {
			return __left._M_base_it == __right._M_base_it;
		}

		friend bool operator!=(const __category_word_iterator& __left, const __category_word_iterator& __right) {
			return __left._M_base_it != __right._M_base_it;
		}

	private:
		_Derived& _M_this() {
			return static_cast<_Derived&>(*this);
		}

		const _Derived& _M_this() const {
			return static_cast<const _Derived&>(*this);
		}

		iterator_type _M_base_it;
	};

	template <typename _Derived, typename _Word, typename _It, endian _Endian>
	class __category_word_iterator<_Derived, _Word, _It, _Endian,
		::std::enable_if_t<::std::is_same_v<__iterator_category_t<_It>, ::std::output_iterator_tag>>> {
	private:
		using __base_iterator   = _It;
		using __base_reference  = ::std::byte;
		using __base_value_type = ::std::byte;
		using __difference_type = ::std::ptrdiff_t;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = _Word;

		static_assert(sizeof(__value_type) >= sizeof(__base_value_type),
			"the 'byte' type selected for the word_iterator must not be larger than the value_type of the "
			"iterator "
			"that "
			"it is meant to view");

		static constexpr inline __size_type __base_values_per_word = sizeof(__value_type) / sizeof(__base_value_type);

	public:
		using iterator_type     = __base_iterator;
		using iterator_category = __iterator_category_t<__base_iterator>;
		using difference_type   = __difference_type;
		using pointer           = _Word*;
		using value_type        = __value_type;
		using reference         = __word_reference<__base_iterator, _Word, _Endian>;

		__category_word_iterator() = default;
		__category_word_iterator(iterator_type __it) : _M_base_it(::std::move(__it)) {
		}

		iterator_type& base() & {
			return this->_M_base_it;
		}

		const iterator_type& base() const& {
			return this->_M_base_it;
		}

		iterator_type&& base() && {
			return ::std::move(this->_M_base_it);
		}

		_Derived operator++(int) const {
			auto __copy = this->_M_this();
			++__copy;
			return __copy;
		}

		_Derived& operator++() {
			__detail::__next(this->_M_base_it, __base_values_per_word);
			return this->_M_this();
		}

		reference operator*() const {
			return reference(this->_M_base_it);
		}

		friend bool operator==(const __category_word_iterator& __left, const __category_word_iterator& __right) {
			return __left._M_base_it == __right._M_base_it;
		}

		friend bool operator!=(const __category_word_iterator& __left, const __category_word_iterator& __right) {
			return __left._M_base_it != __right._M_base_it;
		}

	private:
		iterator_type _M_base_it;

		_Derived& _M_this() {
			return static_cast<_Derived&>(*this);
		}

		const _Derived& _M_this() const {
			return static_cast<const _Derived&>(*this);
		}
	};

	template <typename _LeftDerived, typename _LeftWord, typename _LeftIt, endian _LeftEndian, typename _RightIt>
	bool operator==(const __category_word_iterator<_LeftDerived, _LeftWord, _LeftIt, _LeftEndian>& __left,
		const __word_sentinel<_RightIt>& __right) {
		return __left.base() == __right.base();
	}

	template <typename _LeftDerived, typename _LeftWord, typename _LeftIt, endian _LeftEndian, typename _RightIt>
	bool operator!=(const __category_word_iterator<_LeftDerived, _LeftWord, _LeftIt, _LeftEndian>& __left,
		const __word_sentinel<_RightIt>& __right) {
		return __left.base() != __right.base();
	}

	template <typename _Word, typename _It, endian _Endian = endian::native>
	class __word_iterator
	: public __detail::__category_word_iterator<__word_iterator<_Word, _It, _Endian>, _Word, _It, _Endian> {
	private:
		using __base_t
			= __detail::__category_word_iterator<__word_iterator<_Word, _It, _Endian>, _Word, _It, _Endian>;

	public:
		using __base_t::__base_t;
	};
}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail

#endif // PHD_TEXT_WORD_ITERATOR_HPP
