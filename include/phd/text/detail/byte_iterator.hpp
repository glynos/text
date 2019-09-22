#pragma once

#ifndef PHD_TEXT_BYTE_ITERATOR_HPP
#define PHD_TEXT_BYTE_ITERATOR_HPP

#include <phd/text/version.hpp>

#include <phd/text/endian.hpp>

#include <phd/text/detail/range.hpp>
#include <phd/text/detail/type_traits.hpp>

#include <cstddef>
#include <limits>
#include <climits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	namespace __detail {
		template <typename _Type>
		class __un_mask_type {
		private:
			static_assert(::std::is_integral_v<_Type> || std::is_enum_v<_Type>, "is a integral or enumeration type");

		public:
			using type = _Type;
		};

		template <typename _Type>
		class __mask_type : public __un_mask_type<__remove_cvref_t<_Type>> {};

		template <typename T>
		using __mask_type_t = typename __mask_type<T>::type;

		template <typename _Type, typename _Val>
		_Type __ones_mask_to_right_shift(_Val __val) {
			_Type __shift = 0;
			for (; (__val & 1) == static_cast<_Val>(0); __val >>= 1) {
				++__shift;
			}
			return __shift;
		}

		template <typename _Ref, typename _Byte, typename _Mask = __mask_type_t<_Ref>>
		class __byte_reference {
		private:
			using __base_value_type = _Value;

		public:
			using value_type     = _Byte;
			using mask_type      = _Mask;
			using reference_type = _Ref;

			__byte_reference(reference_type __ref, mask_type __mask) : _M_ref(__ref), _M_mask(__mask) {
			}

			__byte_reference& operator=(value_type __val) {
				const __base_value_type __shift = __ones_mask_to_shift<__base_value_type>(this->_M_mask);
				this->M_ref |= static_cast<__base_value_type>(__val) << __shift;
				return *this;
			}

			value_type value() const {
				const mask_type __shift = __ones_mask_to_shift<mask_type>(this->_M_mask);
				return static_cast<value_type>((this->_M_ref & this->_M_mask) >> __shift);
			}

			operator value_type() const {
				return this->value();
			}

		private:
			reference_type _M_ref;
			mask_type _M_mask;
		};
	} // namespace __detail

	template <typename _It, endian _Endian = endian::native, typename _Byte = std::byte>
	class byte_iterator {
	private:
		using __base_iterator   = _It;
		using __base_sentinel   = _Sen;
		using __base_reference  = __detail::__iterator_reference_t<__base_iterator>;
		using __base_value_type = __detail::__iterator_value_type_t<__base_iterator>;
		using __difference_type = __detail::__iterator_difference_type_t<__base_iterator>;
		using __size_type       = ::std::make_unsigned_t<__difference_type>;
		using __value_type      = _Byte;

		static_assert(sizeof(_Byte) <= sizeof(__base_value_type),
			"the 'byte' type selected for the byte_iterator is not larger than the value_type of the iterator that "
			"it is meant to view");

		static constexpr inline __size_type __max_sizeof       = sizeof(__base_value_type) / sizeof(__value_type);
		static constexpr inline __size_type __max_sizeof_index = __max_sizeof - 1;

	public:
		using iterator_type   = __base_iterator;
		using sentinel_type   = __base_sentinel;
		using difference_type = __difference_type;
		using value_type      = __value_type;
		using reference       = __detail::__byte_reference<__base_reference, __base_value_type>;

		byte_iterator() = default;
		byte_iterator(iterator_type __it) : byte_iterator(::std::move(__it), 0) {
		}
		byte_iterator(iterator_type __it, __size_type __start_at)
		: _M_base_it(::std::move(__it)), _M_progress(__start_at) {
		}

		byte_iterator operator++(int) const {
			auto __copy = *this;
			++__copy;
			return __copy;
		}

		byte_iterator& operator++() {
			++this->_M_progress;
			if (this->_M_progress == __max_sizeof_index) {
				++this->_M_base_it;
				this->_M_progress = static_cast<__size_type>(0);
			}
			return *this;
		}

		byte_iterator operator--(int) const {
			auto __copy = *this;
			--__copy;
			return __copy;
		}

		byte_iterator& operator--() {
			if (this->_M_progress == static_cast<__size_type>(0)) {
				++this->_M_base_it;
				this->_M_progress = __max_sizeof);
			}
			--this->_M_progress;
			return *this;
		}

		byte_iterator operator+(difference_type __by) const {
			auto __copy = *this;
			__copy += __by;
			return __copy;
		}

		byte_iterator& operator+=(difference_type __by) {
			if (__by < static_cast<difference_type>(0)) {
				return this->operator-=(-__by);
			}
			difference_type __n_words = __by % __max_sizeof;
			return *this;
		}

		byte_iterator operator-(difference_type __by) const {
			auto __copy = *this;
			__copy -= __by;
			return __copy;
		}

		byte_iterator& operator-=(difference_type __by) {
			if (__by < static_cast<difference_type>(0)) {
				return this->operator+=(-__by);
			}
			return *this;
		}

		reference operator[](difference_type __index) {
			auto __copy = *this;
			__copy += __index;
			return *__copy;
		}

		reference operator*() const {
			const __base_value_type __shift = this->_M_progress * CHAR_BIT;
			__base_value_type __mask        = static_cast<__base_value_type>(::std::numeric_limits<value_type>())
				<< __shift;
			__base_reference __val = *this->_M_base_it;
			return reference(__val, __mask);
		}

	private:
		iterator_type _M_base_it;
		__size_type _M_progress;
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_BYTE_ITERATOR_HPP
