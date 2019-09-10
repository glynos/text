#pragma once

#ifndef PHD_TEXT_SUBRANGE_HPP
#define PHD_TEXT_SUBRANGE_HPP

#include <phd/text/detail/range.hpp>

#include <iterator>
#include <utility>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE {

	enum class subrange_kind : bool { unsized, sized };

	template <typename _It, typename _Sen,
		subrange_kind _Kind = __detail::__is_iterator_concept_or_better_v<::std::random_access_iterator_tag,
		                           _It>&& ::std::is_same_v<_It, _Sen>
		     ? subrange_kind::sized
		     : subrange_kind::unsized>
	class subrange {
	public:
		using iterator        = _It;
		using const_iterator  = iterator;
		using sentinel        = _Sen;
		using const_sentinel  = sentinel;
		using pointer         = __detail::__iterator_pointer_t<iterator>;
		using const_pointer   = pointer;
		using reference       = __detail::__iterator_reference_t<iterator>;
		using const_reference = reference;
		using value_type      = __detail::__iterator_value_type_t<iterator>;
		using difference_type = __detail::__iterator_pointer_t<iterator>;
		using size_type       = ::std::make_unsigned_t<difference_type>;

		constexpr subrange() noexcept = default;

		template <typename _Range,
			::std::enable_if_t<!::std::is_same_v<::std::remove_cvref_t<_Range>, subrange>>* = nullptr>
		constexpr subrange(_Range&& __range) noexcept
		: subrange(__detail::__adl::__adl_begin(__range), __detail::__adl::__adl_end(__range)) {
		}

		constexpr subrange(iterator __it, sentinel __sen) noexcept
		: _M_it(::std::move(__it)), _M_sen(::std::move(__sen)) {
		}

		constexpr iterator begin() const noexcept {
			return this->_M_it;
		}

		constexpr sentinel end() const noexcept {
			return this->_M_sen;
		}

		constexpr bool empty() const noexcept {
			return this->_M_it == this->_M_sen;
		}

		template <subrange_kind _Dummy = _Kind, ::std::enable_if_t<_Dummy == subrange_kind::sized>* = nullptr>
		constexpr size_type size() const noexcept {
			return ::std::distance(this->_M_it, this->_M_sen);
		}

	private:
		iterator _M_it;
		sentinel _M_sen;
	};

	namespace __detail {
		template <typename _It, typename _Sen>
		using __subrange_for_t = subrange<_It, _Sen>;

		template <typename _Range>
		using __range_subrange_for_t
			= __subrange_for_t<__detail::__range_iterator_t<_Range>, __detail::__range_sentinel_t<_Range>>;
	} // namespace __detail

	template <typename _Range>
	constexpr auto make_subrange(_Range&& __range) noexcept(
		::std::is_nothrow_constructible_v<__detail::__range_subrange_for_t<_Range>,
		     __detail::__range_iterator_t<_Range>, __detail::__range_sentinel_t<_Range>>) {
		using __sub_t = __detail::__range_subrange_for_t<_Range>;
		return __sub_t(__detail::__adl::__adl_begin(__range), __detail::__adl::__adl_end(__range));
	}

	namespace __detail {
		template <typename _Range, typename _First, typename _Last>
		constexpr decltype(auto) __reconstruct(_First&& __first, _Last&& __last) noexcept(
			!::std::is_constructible_v<_Range, _First, _Last>
			     ? (!::std::is_constructible_v<_Range, __detail::__subrange_for_t<_First, _Last>>
			                 ? noexcept(make_subrange(std::forward<_First>(__first), ::std::forward<_Last>(__last)))
			                 : ::std::is_nothrow_constructible_v<_Range, __detail::__subrange_for_t<_First, _Last>>)
			     : ::std::is_nothrow_constructible_v<_Range, _First, _Last>) {
			if constexpr (std::is_constructible_v<_Range, _First, _Last>) {
				return _Range(std::forward<_First>(__first), ::std::forward<_Last>(__last));
			}
			else {
				decltype(auto) __sub = make_subrange(std::forward<_First>(__first), ::std::forward<_Last>(__last));
				using __sub_t        = decltype(__sub);
				if constexpr (std::is_constructible_v<_Range, __sub_t>) {
					return _Range(::std::forward<__sub_t>(__sub));
				}
				else {
					return ::std::forward<__sub_t>(__sub);
				}
			}
		}
	} // namespace __detail

}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_TEXT_TRAITS_HPP
