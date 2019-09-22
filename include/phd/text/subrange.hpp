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
		using iterator          = _It;
		using const_iterator    = iterator;
		using sentinel          = _Sen;
		using const_sentinel    = sentinel;
		using iterator_category = __detail::__iterator_category_t<iterator>;
		using iterator_concept  = __detail::__iterator_concept_t<iterator>;
		using pointer           = __detail::__iterator_pointer_t<iterator>;
		using const_pointer     = pointer;
		using reference         = __detail::__iterator_reference_t<iterator>;
		using const_reference   = reference;
		using value_type        = __detail::__iterator_value_type_t<iterator>;
		using difference_type   = ::std::conditional_t<::std::is_same_v<iterator_concept, ::std::output_iterator_tag>,
               ptrdiff_t, __detail::__iterator_difference_type_t<iterator>>;
		using size_type         = ::std::make_unsigned_t<difference_type>;

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

		template <typename _Dummy = _It,
			::std::enable_if_t<
			     __detail::__is_iterator_concept_or_better_v<contiguous_iterator_tag, _Dummy>>* = nullptr>
		constexpr pointer data() const noexcept {
			return &*begin();
		}

	private:
		iterator _M_it;
		sentinel _M_sen;
	};

	namespace __detail {
		template <typename _Range>
		using __subrange_for_t = subrange<__detail::__range_iterator_t<_Range>, __detail::__range_sentinel_t<_Range>>;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		using __is_reconstructible_range = ::std::is_constructible<_Range, subrange<_First, _Last>>;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		inline constexpr bool __is_reconstructible_range_v = __is_reconstructible_range<_Range, _First, _Last>::value;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		using __is_nothrow_reconstructible_range = ::std::is_nothrow_constructible<_Range, subrange<_First, _Last>>;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		inline constexpr bool __is_nothrow_reconstructible_range_v
			= __is_nothrow_reconstructible_range<_Range, _First, _Last>::value;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		using __is_pair_reconstructible_range = ::std::is_constructible<_Range, _First, _Last>;

		template <typename _Range, typename _First = __detail::__range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		inline constexpr bool __is_pair_reconstructible_range_v
			= __is_pair_reconstructible_range<_Range, _First, _Last>::value;

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		using __is_nothrow_pair_reconstructible_range = ::std::is_nothrow_constructible<_Range, _First, _Last>;

		template <typename _Range, typename _First = __detail::__range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		inline constexpr bool __is_nothrow_pair_reconstructible_range_v
			= __is_nothrow_pair_reconstructible_range<_Range, _First, _Last>::value;
	} // namespace __detail

	template <typename _Range>
	constexpr __detail::__subrange_for_t<_Range> make_subrange(_Range&& __range) noexcept(
		::std::is_nothrow_constructible_v<_Range, __detail::__subrange_for_t<_Range>>) {
		return { __detail::__adl::__adl_begin(__range), __detail::__adl::__adl_end(__range) };
	}

	template <typename _It, typename _Sen>
	constexpr subrange<_It, _Sen> make_subrange(_It&& __it, _Sen&& __sen) noexcept(
		::std::is_nothrow_constructible_v<subrange<_It, _Sen>, _It, _Sen>) {
		return { ::std::forward<_It>(__it), ::std::forward<_Sen>(__sen) };
	}

	namespace __detail {

		template <typename _Range, typename _First = __range_iterator_t<_Range>,
			typename _Last = __range_sentinel_t<_Range>>
		using __reconstruct_t = ::std::conditional_t<!__is_pair_reconstructible_range_v<_Range, _First, _Last>,
			::std::conditional_t<!__is_reconstructible_range_v<_Range, _First, _Last>, subrange<_First, _Last>,
			     _Range>,
			_Range>;

		template <typename _Range, typename _First, typename _Last>
		constexpr decltype(auto) __reconstruct(_First&& __first, _Last&& __last) noexcept(
			!__is_pair_reconstructible_range_v<_Range, _First, _Last>
			     ? (!__is_reconstructible_range_v<_Range, _First, _Last>
			                 ? noexcept(
			                        make_subrange(::std::forward<_First>(__first), ::std::forward<_Last>(__last)))
			                 : __is_nothrow_reconstructible_range_v<_Range, _First, _Last>)
			     : __is_nothrow_pair_reconstructible_range_v<_Range, _First, _Last>) {
			if constexpr (__is_pair_reconstructible_range_v<_Range, _First, _Last>) {
				return _Range(::std::forward<_First>(__first), ::std::forward<_Last>(__last));
			}
			else if constexpr (
				!__is_reconstructible_range_v<_Range, _First,
				     _Last> && __is_iterator_concept_or_better_v<::std::random_access_iterator_tag, _First> && ::std::is_constructible_v<_Range, _First, ::std::make_signed_t<__iterator_difference_type_t<_First>>>) {
				using __diff_type  = __iterator_difference_type_t<_First>;
				using __size_type  = ::std::make_unsigned_t<__diff_type>;
				__diff_type __dist = __last - __first;
				return _Range(::std::forward<_First>(__first), static_cast<__size_type>(__dist));
			}
			else {
				decltype(auto) __sub
					= make_subrange(::std::forward<_First>(__first), ::std::forward<_Last>(__last));
				using __sub_t = decltype(__sub);
				if constexpr (__is_reconstructible_range_v<_Range, _First, _Last>) {
					return _Range(::std::forward<__sub_t>(__sub));
				}
				else {
					return ::std::forward<__sub_t>(__sub);
				}
			}
		}

		template <typename _Range, typename _InRange>
		constexpr decltype(auto) __reconstruct(_InRange&& __range) noexcept(noexcept(
			__reconstruct<__remove_cvref_t<_Range>>(__adl::__adl_begin(__range), __adl::__adl_end(__range)))) {
			return __reconstruct<__remove_cvref_t<_Range>>(__adl::__adl_begin(__range), __adl::__adl_end(__range));
		}
	} // namespace __detail
}}     // namespace phd::text::PHD_TEXT_ABI_NAMESPACE

#endif // PHD_TEXT_TEXT_TRAITS_HPP
