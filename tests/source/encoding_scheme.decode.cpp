#include <phd/text/encoding_scheme.hpp>
#include <phd/text/decode.hpp>

#include <catch2/catch.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

#include <algorithm>

TEST_CASE("text/decode/encoding_scheme", "decode from byte arrays with specific endianness") {
	SECTION("endian::native") {
		SECTION("execution") {
			phd::text::encoding_scheme<phd::text::execution, phd::text::endian::native> encoding{};
			std::u32string result0 = phd::text::decode(phd::text::tests::ansi_sequence_bytes_truth, encoding);
			bool is_equal0         = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_truth.begin(), phd::text::tests::u32_ansi_sequence_truth.end());
			REQUIRE(is_equal0);
		}
		SECTION("wide_execution") {
			phd::text::encoding_scheme<phd::text::wide_execution, phd::text::endian::native> encoding{};
			std::u32string result0 = phd::text::decode(phd::text::tests::w_ansi_sequence_bytes_truth, encoding);
			bool is_equal0         = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_truth.begin(), phd::text::tests::u32_ansi_sequence_truth.end());
			REQUIRE(is_equal0);

			std::u32string result1 = phd::text::decode(phd::text::tests::w_unicode_sequence_bytes_truth, encoding);
			bool is_equal1
			     = std::equal(result1.cbegin(), result1.cend(), phd::text::tests::u32_unicode_sequence_truth.begin(),
			          phd::text::tests::u32_unicode_sequence_truth.end());
			REQUIRE(is_equal1);
		}
		SECTION("utf8") {
			phd::text::encoding_scheme<phd::text::utf8, phd::text::endian::native> encoding{};
			std::u32string result0 = phd::text::decode(phd::text::tests::u8_ansi_sequence_bytes_truth, encoding);
			bool is_equal0         = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_truth.begin(), phd::text::tests::u32_ansi_sequence_truth.end());
			REQUIRE(is_equal0);

			std::u32string result1 = phd::text::decode(phd::text::tests::u8_unicode_sequence_bytes_truth, encoding);
			bool is_equal1
			     = std::equal(result1.cbegin(), result1.cend(), phd::text::tests::u32_unicode_sequence_truth.begin(),
			          phd::text::tests::u32_unicode_sequence_truth.end());
			REQUIRE(is_equal1);
		}
		SECTION("utf16") {
			phd::text::encoding_scheme<phd::text::utf16, phd::text::endian::native> encoding{};
			std::u32string result0 = phd::text::decode(phd::text::tests::u16_ansi_sequence_bytes_truth, encoding);
			bool is_equal0         = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_truth.begin(), phd::text::tests::u32_ansi_sequence_truth.end());
			REQUIRE(is_equal0);

			std::u32string result1 = phd::text::decode(phd::text::tests::u16_unicode_sequence_bytes_truth, encoding);
			bool is_equal1
			     = std::equal(result1.cbegin(), result1.cend(), phd::text::tests::u32_unicode_sequence_truth.begin(),
			          phd::text::tests::u32_unicode_sequence_truth.end());
			REQUIRE(is_equal1);
		}
		SECTION("utf32") {
			phd::text::encoding_scheme<phd::text::utf32, phd::text::endian::native> encoding{};
			std::u32string result0 = phd::text::decode(phd::text::tests::u32_ansi_sequence_bytes_truth, encoding);
			bool is_equal0         = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_truth.begin(), phd::text::tests::u32_ansi_sequence_truth.end());
			REQUIRE(is_equal0);

			std::u32string result1 = phd::text::decode(phd::text::tests::u32_unicode_sequence_bytes_truth, encoding);
			bool is_equal1
			     = std::equal(result1.cbegin(), result1.cend(), phd::text::tests::u32_unicode_sequence_truth.begin(),
			          phd::text::tests::u32_unicode_sequence_truth.end());
			REQUIRE(is_equal1);
		}
	}
}
