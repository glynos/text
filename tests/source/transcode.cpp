#include <phd/text/encoding.hpp>
#include <phd/text/transcode.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

#include <catch2/catch.hpp>

TEST_CASE("text/transcode/roundtrip", "transcode can roundtrip") {
	SECTION("char") {
		std::string result = phd::text::transcode(phd::text::tests::ansi_sequence_truth, phd::text::execution{});
		REQUIRE(result == phd::text::tests::ansi_sequence_truth);
	}
	SECTION("wchar_t") {
		std::wstring result0
		     = phd::text::transcode(phd::text::tests::w_ansi_sequence_truth, phd::text::wide_execution{});
		REQUIRE(result0 == phd::text::tests::w_ansi_sequence_truth);

		std::wstring result1
		     = phd::text::transcode(phd::text::tests::w_unicode_sequence_truth, phd::text::wide_execution{});
		REQUIRE(result1 == phd::text::tests::w_unicode_sequence_truth);
	}
	SECTION("char8_t") {
		std::basic_string<char8_t> result0
		     = phd::text::transcode(phd::text::tests::u8_ansi_sequence_truth, phd::text::utf8{});
		REQUIRE(result0 == phd::text::tests::u8_ansi_sequence_truth);

		std::basic_string<char8_t> result1
		     = phd::text::transcode(phd::text::tests::u8_unicode_sequence_truth, phd::text::utf8{});
		REQUIRE(result1 == phd::text::tests::u8_unicode_sequence_truth);
	}
	SECTION("char16_t") {
		std::u16string result0 = phd::text::transcode(phd::text::tests::u16_ansi_sequence_truth, phd::text::utf16{});
		REQUIRE(result0 == phd::text::tests::u16_ansi_sequence_truth);

		std::u16string result1
		     = phd::text::transcode(phd::text::tests::u16_unicode_sequence_truth, phd::text::utf16{});
		REQUIRE(result1 == phd::text::tests::u16_unicode_sequence_truth);
	}
	SECTION("char32_t") {
		std::u32string result0 = phd::text::transcode(phd::text::tests::u32_ansi_sequence_truth, phd::text::utf32{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);

		std::u32string result1
		     = phd::text::transcode(phd::text::tests::u32_unicode_sequence_truth, phd::text::utf32{});
		REQUIRE(result1 == phd::text::tests::u32_unicode_sequence_truth);
	}
}
