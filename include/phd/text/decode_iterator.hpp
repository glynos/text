#pragma once
#ifndef PHD_TEXT_DECODE_ITERATOR_HPP
#define PHD_TEXT_DECODE_ITERATOR_HPP

#include <phd/text/version.hpp>

#include <phd/text/error_handler.hpp>
#include <phd/text/state.hpp>
#include <phd/text/detail/range.hpp>

#include <string_view>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	class decode_sentinel {};

	template <typename _Range, typename _Encoding, typename _ErrorHandler>
	class decode_iterator {
	private:
		using __unwrapped_range_type    = __detail::__remove_cvref_t<__detail::__unwrap_t<_Range>>;
		using __unwrapped_encoding_type = __detail::__remove_cvref_t<__detail::__unwrap_t<_Encoding>>;
		using __base_iterator           = __detail::__range_iterator_t<__unwrapped_range_type>;

	public:
		using range_type          = _Range;
		using iterator_type       = __base_iterator;
		using encoding_type       = _Encoding;
		using error_handler_type  = _ErrorHandler;
		using encoding_state_type = encoding_state_t<__unwrapped_encoding_type>;
		using iterator_category   = ::std::conditional_t<
               __detail::__is_iterator_concept_or_better_v<::std::bidirectional_iterator_tag, __base_iterator>,
               ::std::bidirectional_iterator_tag, __detail::__iterator_category_t<__base_iterator>>;
		using iterator_concept = ::std::conditional_t<
			__detail::__is_iterator_concept_or_better_v<::std::bidirectional_iterator_tag, __base_iterator>,
			::std::bidirectional_iterator_tag, __detail::__iterator_concept_t<__base_iterator>>;
		using value_type = encoding_code_point_t<_Encoding>;
		// TODO: is there such a thing?
		// using pointer         = ;
		using reference       = value_type;
		using difference_type = __detail::__iterator_difference_type_t<__base_iterator>;

		// constructors
		decode_iterator()                       = delete;

		decode_iterator(const decode_iterator&) = default;

		decode_iterator(decode_iterator&&)      = default;

		decode_iterator(range_type __range)
		: decode_iterator(::std::move(__range), encoding_type{}, error_handler_type{}) {
		}

		decode_iterator(range_type __range, encoding_type __encoding)
		: decode_iterator(::std::move(__range), encoding_type{}, error_handler_type{}) {
		}

		decode_iterator(range_type __range, error_handler_type __error_handler)
		: decode_iterator(::std::move(__range), encoding_type{}, error_handler_type{}) {
		}

		decode_iterator(range_type __range, encoding_type __encoding, error_handler_type __error_handler)
		: _M_base(::std::move(__range))
		, _M_encoding(::std::move(__encoding))
		, _M_handler(::std::move(__error_handler)) {
		}

		// assignment
		decode_iterator& operator=(const decode_iterator&) = default;
		decode_iterator& operator=(decode_iterator&&) = default;

		// observers
		const encoding_type& encoding() const {
			return this->_M_encoding;
		}
		
		encoding_type& encoding() {
			return this->_M_encoding;
		}

		const encoding_state_type& state() const {
			return this->_M_state;
		}

		encoding_state_type& state() {
			return this->_M_state;
		}

		const error_handler_type& state() const {
			return this->_M_handler;
		}

		error_handler_type& state() {
			return this->_M_handler;
		}

		range_type base() const & {
			return this->_M_state;
		}

		range_type&& base() && {
			return ::std::move(this->_M_state);
		}

		// modifiers
		decode_iterator operator++(int) {
			decode_iterator __copy = *this;
			++__copy;
			return __copy;
		}

		decode_iterator& operator++() {
			return *this;
		}

		friend constexpr bool operator==(const decode_iterator& __it, const decode_sentinel&) {
			return ::std::empty(__it._M_base);
		}

		friend constexpr bool operator==(const decode_sentinel&, const decode_iterator& __it) {
			return ::std::empty(__it._M_base);
		}

		friend constexpr bool operator!=(const decode_iterator& __it, const decode_sentinel& __sen) {
			return !(__it == __sen);
		}

		friend constexpr bool operator!=(const decode_sentinel& __sen, const decode_iterator& __it) {
			return !(__sen == __it);
		}

	private:
		range_type _M_base;
		encoding_type _M_encoding;
		error_handler_type _M_handler;
		encoding_state_type _M_state;
	};

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_DECODE_ITERATOR_HPP
