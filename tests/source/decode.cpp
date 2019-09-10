#include <phd/text/encode.hpp>
#include <phd/text/encoding.hpp>

#include <catch2/catch.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

TEST_CASE("text/decode/core", "basic usages of decode function do not explode") {
	SECTION("char") {
		std::u32string result0 = phd::text::decode(phd::text::tests::ansi_sequence_truth, phd::text::execution{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);
	}
	SECTION("wchar_t") {
		std::u32string result0
		     = phd::text::decode(phd::text::tests::w_ansi_sequence_truth, phd::text::wide_execution{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);

		std::u32string result1
		     = phd::text::decode(phd::text::tests::w_unicode_sequence_truth, phd::text::wide_execution{});
		REQUIRE(result1 == phd::text::tests::u32_unicode_sequence_truth);
	}
	SECTION("char8_t") {
		std::u32string result0 = phd::text::decode(phd::text::tests::u8_ansi_sequence_truth, phd::text::utf8{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);

		std::u32string result1 = phd::text::decode(phd::text::tests::u8_unicode_sequence_truth, phd::text::utf8{});
		REQUIRE(result1 == phd::text::tests::u32_unicode_sequence_truth);
	}
	SECTION("char16_t") {
		std::u32string result0 = phd::text::decode(phd::text::tests::u16_ansi_sequence_truth, phd::text::utf16{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);

		std::u32string result1 = phd::text::decode(phd::text::tests::u16_unicode_sequence_truth, phd::text::utf16{});
		REQUIRE(result1 == phd::text::tests::u32_unicode_sequence_truth);
	}
	SECTION("char32_t") {
		std::u32string result0 = phd::text::decode(phd::text::tests::u32_ansi_sequence_truth, phd::text::utf32{});
		REQUIRE(result0 == phd::text::tests::u32_ansi_sequence_truth);

		std::u32string result1 = phd::text::decode(phd::text::tests::u32_unicode_sequence_truth, phd::text::utf32{});
		REQUIRE(result1 == phd::text::tests::u32_unicode_sequence_truth);
	}
}
