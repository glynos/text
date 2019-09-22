#pragma once

#ifndef PHD_TEXT_TESTS_BASIC_UNICODE_STRINGS_HPP
#define PHD_TEXT_TESTS_BASIC_UNICODE_STRINGS_HPP

#include <span>
#include <phd/text/c_string_view.hpp>

namespace phd::text::tests {

	template <typename Container>
	inline std::span<const std::byte> as_bytes(Container& c) {
		return std::as_bytes(std::span<std::remove_pointer_t<decltype(c.data())>>(c.data(), c.size()));
	}

	template <typename Container>
	inline std::span<const std::byte> as_writable_bytes(Container& c) {
		return std::as_writable_bytes(std::span<std::remove_pointer_t<decltype(c.data())>>(c.data(), c.size()));
	}

	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_unicode_sequence_truth
	     = U"z♥䕦🍷私はガラスを食べられます。それは私を傷つけません。𐌼𐌰𐌲 𐌲𐌻𐌴𐍃 𐌹̈𐍄𐌰𐌽, 𐌽𐌹 𐌼𐌹𐍃 𐍅𐌿 𐌽𐌳𐌰𐌽 𐌱𐍂𐌹𐌲𐌲𐌹𐌸.யாமறிந்த "
	       U"மொழிகளிலே தமிழ்மொழி போல் இனிதாவது எங்கும் காணோம்,На берегу пустынных волн € أنا قادر على أكل الزجاج و هذا لا "
	       U"يؤلمني."
	       U"On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and "
	       U"demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the "
	       U"pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty "
	       U"through weakness of will, which is the same as saying through shrinking from toil and pain. These cases "
	       U"are perfectly simple and easy to distinguish. In a free hour, when our power of choice is untrammelled "
	       U"and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and "
	       U"every pain avoided. But in certain circumstances and owing to the claims of duty or the obligations of "
	       U"business it will frequently occur that pleasures have to be repudiated and annoyances accepted. The wise "
	       U"man therefore always holds in these matters to this principle of selection: he rejects pleasures to "
	       U"secure other greater pleasures, or else he endures pains to avoid worse pains."
	       U"오늘이 오늘이소서 매일이 오늘이소서 저물지도 새지도 말으시고 새려면 늘 언제나 오늘이소서.";
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_unicode_sequence_truth
	     = u"z♥䕦🍷私はガラスを食べられます。それは私を傷つけません。𐌼𐌰𐌲 𐌲𐌻𐌴𐍃 𐌹̈𐍄𐌰𐌽, 𐌽𐌹 𐌼𐌹𐍃 𐍅𐌿 𐌽𐌳𐌰𐌽 𐌱𐍂𐌹𐌲𐌲𐌹𐌸.யாமறிந்த "
	       u"மொழிகளிலே தமிழ்மொழி போல் இனிதாவது எங்கும் காணோம்,На берегу пустынных волн € أنا قادر على أكل الزجاج و هذا لا "
	       u"يؤلمني."
	       u"On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and "
	       u"demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the "
	       u"pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty "
	       u"through weakness of will, which is the same as saying through shrinking from toil and pain. These cases "
	       u"are perfectly simple and easy to distinguish. In a free hour, when our power of choice is untrammelled "
	       u"and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and "
	       u"every pain avoided. But in certain circumstances and owing to the claims of duty or the obligations of "
	       u"business it will frequently occur that pleasures have to be repudiated and annoyances accepted. The wise "
	       u"man therefore always holds in these matters to this principle of selection: he rejects pleasures to "
	       u"secure other greater pleasures, or else he endures pains to avoid worse pains."
	       u"오늘이 오늘이소서 매일이 오늘이소서 저물지도 새지도 말으시고 새려면 늘 언제나 오늘이소서.";
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_unicode_sequence_truth
	     = u8"z♥䕦🍷私はガラスを食べられます。それは私を傷つけません。𐌼𐌰𐌲 𐌲𐌻𐌴𐍃 𐌹̈𐍄𐌰𐌽, 𐌽𐌹 𐌼𐌹𐍃 𐍅𐌿 𐌽𐌳𐌰𐌽 𐌱𐍂𐌹𐌲𐌲𐌹𐌸.யாமறிந்த "
	       u8"மொழிகளிலே தமிழ்மொழி போல் இனிதாவது எங்கும் காணோம்,На берегу пустынных волн € أنا قادر على أكل الزجاج و هذا لا "
	       u8"يؤلمني."
	       u8"On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and "
	       u8"demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the "
	       u8"pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty "
	       u8"through weakness of will, which is the same as saying through shrinking from toil and pain. These cases "
	       u8"are perfectly simple and easy to distinguish. In a free hour, when our power of choice is untrammelled "
	       u8"and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and "
	       u8"every pain avoided. But in certain circumstances and owing to the claims of duty or the obligations of "
	       u8"business it will frequently occur that pleasures have to be repudiated and annoyances accepted. The "
	       u8"wise "
	       u8"man therefore always holds in these matters to this principle of selection: he rejects pleasures to "
	       u8"secure other greater pleasures, or else he endures pains to avoid worse pains."
	       u8"오늘이 오늘이소서 매일이 오늘이소서 저물지도 새지도 말으시고 새려면 늘 언제나 오늘이소서.";
	inline constexpr const phd::text::basic_c_string_view<wchar_t> w_unicode_sequence_truth
	     = L"z♥䕦🍷私はガラスを食べられます。それは私を傷つけません。𐌼𐌰𐌲 𐌲𐌻𐌴𐍃 𐌹̈𐍄𐌰𐌽, 𐌽𐌹 𐌼𐌹𐍃 𐍅𐌿 𐌽𐌳𐌰𐌽 𐌱𐍂𐌹𐌲𐌲𐌹𐌸.யாமறிந்த "
	       L"மொழிகளிலே தமிழ்மொழி போல் இனிதாவது எங்கும் காணோம்,На берегу пустынных волн € أنا قادر على أكل الزجاج و هذا لا "
	       L"يؤلمني."
	       L"On the other hand, we denounce with righteous indignation and dislike men who are so beguiled and "
	       L"demoralized by the charms of pleasure of the moment, so blinded by desire, that they cannot foresee the "
	       L"pain and trouble that are bound to ensue; and equal blame belongs to those who fail in their duty "
	       L"through weakness of will, which is the same as saying through shrinking from toil and pain. These cases "
	       L"are perfectly simple and easy to distinguish. In a free hour, when our power of choice is untrammelled "
	       L"and when nothing prevents our being able to do what we like best, every pleasure is to be welcomed and "
	       L"every pain avoided. But in certain circumstances and owing to the claims of duty or the obligations of "
	       L"business it will frequently occur that pleasures have to be repudiated and annoyances accepted. The wise "
	       L"man therefore always holds in these matters to this principle of selection: he rejects pleasures to "
	       L"secure other greater pleasures, or else he endures pains to avoid worse pains."
	       L"오늘이 오늘이소서 매일이 오늘이소서 저물지도 새지도 말으시고 새려면 늘 언제나 오늘이소서.";

	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_ansi_sequence_truth = U"zá:iï";
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_ansi_sequence_truth = u"zá:iï";
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_ansi_sequence_truth   = u8"zá:iï";
	inline constexpr const phd::text::basic_c_string_view<wchar_t> w_ansi_sequence_truth    = L"zá:iï";
	inline constexpr const phd::text::basic_c_string_view<char> ansi_sequence_truth         = "zá:iï";

	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_unicode_single_truth = U"♥";
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_unicode_single_truth = u"♥";
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_unicode_single_truth   = u8"♥";
	inline constexpr const phd::text::basic_c_string_view<wchar_t> w_unicode_single_truth    = L"♥";

	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_ansi_single_truth = U"á";
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_ansi_single_truth = u"á";
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_ansi_single_truth   = u8"á";
	inline constexpr const phd::text::basic_c_string_view<wchar_t> w_ansi_single_truth    = L"á";
	inline constexpr const phd::text::basic_c_string_view<char> ansi_single_truth         = "á";

	inline constexpr const char32_t u32_unicode_invalid_input_arr[] = { 0xFFFFFFFF, 0 };
	inline constexpr const char16_t u16_unicode_invalid_input_arr[] = { 0xD800, 0 };
	inline constexpr const char8_t u8_unicode_invalid_input_arr[]   = { 0xC0, 0 };
	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_unicode_invalid_input
	     = u32_unicode_invalid_input_arr;
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_unicode_invalid_input
	     = u16_unicode_invalid_input_arr;
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_unicode_invalid_input
	     = u8_unicode_invalid_input_arr;

	inline constexpr const phd::text::basic_c_string_view<char32_t> u32_unicode_replacement_truth = U"\uFFFD";
	inline constexpr const phd::text::basic_c_string_view<char16_t> u16_unicode_replacement_truth = u"\uFFFD";
	inline constexpr const phd::text::basic_c_string_view<char8_t> u8_unicode_replacement_truth   = u8"\uFFFD";


	inline static const std::span<const std::byte> u32_unicode_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u32_unicode_sequence_truth);
	inline static const std::span<const std::byte> u16_unicode_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u16_unicode_sequence_truth);
	inline static const std::span<const std::byte> u8_unicode_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u8_unicode_sequence_truth);
	inline static const std::span<const std::byte> w_unicode_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::w_unicode_sequence_truth);

	inline static const std::span<const std::byte> u32_ansi_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u32_ansi_sequence_truth);
	inline static const std::span<const std::byte> u16_ansi_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u16_ansi_sequence_truth);
	inline static const std::span<const std::byte> u8_ansi_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::u8_ansi_sequence_truth);
	inline static const std::span<const std::byte> w_ansi_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::w_ansi_sequence_truth);
	inline static const std::span<const std::byte> ansi_sequence_bytes_truth
	     = phd::text::tests::as_bytes(phd::text::tests::ansi_sequence_truth);

} // namespace phd::text::tests

#endif // PHD_TEXT_TESTS_BASIC_UNICODE_STRINGS_HPP
