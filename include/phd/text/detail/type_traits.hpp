#pragma once

#ifndef PHD_TEXT_DETAIL_TYPE_TRAITS_HPP
#define PHD_TEXT_DETAIL_TYPE_TRAITS_HPP

#include <phd/text/version.hpp>

#include <type_traits>

namespace phd::text { inline namespace PHD_TEXT_ABI_NAMESPACE { namespace __detail {

	template <typename>
	class __always_false : public ::std::integral_constant<bool, false> {};

	template <typename _Type, _Type>
	class __always_false_constant : public __always_false<_Type> {};

	template <typename _Type, _Type _Val>
	constexpr inline bool __always_false_constant_v = __always_false_constant<_Type, _Val>::value;

	template <::std::size_t _Val>
	using always_false_index = __always_false_constant<::std::size_t, _Val>;

	template <::std::size_t _Val>
	constexpr inline bool __always_false_index_v = __always_false_index<_Val>::value;

	template <typename _Type>
	constexpr inline bool __always_false_v = __always_false<_Type>::value;

	template <typename>
	using __always_true = ::std::integral_constant<bool, true>;

	template <typename _Type>
	constexpr inline bool __always_true_v = __always_true<_Type>::value;

	template <typename _Type>
	using __remove_cvref = ::std::remove_cv<::std::remove_reference_t<_Type>>;

	template <typename _Type>
	using __remove_cvref_t = typename __remove_cvref<_Type>::type;

	template <typename _Type>
	using __is_character = ::std::integral_constant<bool,
		::std::is_same_v<_Type, char> || ::std::is_same_v<_Type, wchar_t> ||
#if defined(__cpp_char8_t)
			::std::is_same_v<_Type, char8_t> ||
#endif
			::std::is_same_v<_Type,
			     unsigned char> || ::std::is_same_v<_Type, signed char> || ::std::is_same_v<_Type, char16_t> || ::std::is_same_v<_Type, char32_t>>;

	template <typename _Type>
	constexpr inline bool __is_character_v = __is_character<_Type>::value;

	template <typename _Default, typename _Void, template <typename...> typename _Op, typename... _Args>
	class __detector {
	public:
		using value_t = ::std::false_type;
		using type    = _Default;
	};

	template <typename _Default, template <typename...> typename _Op, typename... _Args>
	class __detector<_Default, ::std::void_t<_Op<_Args...>>, _Op, _Args...> {
	public:
		using value_t = ::std::true_type;
		using type    = _Op<_Args...>;
	};

	class __nonesuch {
	public:
		~__nonesuch()                 = delete;
		__nonesuch(__nonesuch const&) = delete;
		__nonesuch& operator=(__nonesuch const&) = delete;
	};

	template <template <typename...> typename _Op, typename... _Args>
	using __is_detected = typename __detector<__nonesuch, void, _Op, _Args...>::value_t;

	template <template <typename...> typename _Op, typename... _Args>
	inline constexpr bool __is_detected_v = __is_detected<_Op, _Args...>::value;

	template <template <typename...> typename _Op, typename... _Args>
	using __detected_t = typename __detector<__nonesuch, void, _Op, _Args...>::type;

	template <typename _Default, template <typename...> typename _Op, typename... _Args>
	using __detected_or = __detector<_Default, void, _Op, _Args...>;

}}} // namespace phd::text::PHD_TEXT_ABI_NAMESPACE::__detail

#endif // PHD_TEXT_DETAIL_TYPE_TRAITS_HPP
