#pragma once

#ifndef PHD_TEXT_DETAIL_TYPE_TRAITS_HPP
#define PHD_TEXT_DETAIL_TYPE_TRAITS_HPP

#include <type_traits>

namespace phd::text::detail {
	template <typename T>
	using remove_cv_ref = std::remove_cv<std::remove_reference_t<T>>;

	template <typename T>
	using remove_cv_ref_t = typename remove_cv_ref<T>::type;

	template <typename T>
	using is_character = std::integral_constant<bool, std::is_same_v<T, char> || std::is_same_v<T, wchar_t> ||
#if defined(__cpp_char8_t)
			std::is_same_v<T, char8_t> ||
#endif
			std::is_same_v<T, unsigned char> || std::is_same_v<T, signed char> || std::is_same_v<T, char16_t> || std::is_same_v<T, char32_t>>;

	template <typename T>
	constexpr inline bool is_character_v = is_character<T>::value;

} // namespace phd::text::detail

#endif // PHD_TEXT_DETAIL_TYPE_TRAITS_HPP
