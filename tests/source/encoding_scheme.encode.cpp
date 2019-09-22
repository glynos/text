#include <phd/text/encoding_scheme.hpp>
#include <phd/text/encode.hpp>

#include <catch2/catch.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

#include <algorithm>

TEST_CASE("text/encode/encoding_scheme", "encode to byte arrays with specific endianness") {
	SECTION("endian::native") {
		SECTION("execution") {
			phd::text::encoding_scheme<phd::text::execution, phd::text::endian::native> encoding{};
			std::vector<std::byte> result0 = phd::text::encode(phd::text::tests::u32_ansi_sequence_truth, encoding);
			bool is_equal0
			     = std::equal(result0.cbegin(), result0.cend(), phd::text::tests::ansi_sequence_bytes_truth.cbegin(),
			          phd::text::tests::ansi_sequence_bytes_truth.cend());
			REQUIRE(is_equal0);
		}
		SECTION("wide_execution") {
			phd::text::encoding_scheme<phd::text::wide_execution, phd::text::endian::native> encoding{};
			std::vector<std::byte> result0 = phd::text::encode(phd::text::tests::u32_ansi_sequence_truth, encoding);
			bool is_equal0                 = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::w_ansi_sequence_bytes_truth.cbegin(),
                    phd::text::tests::w_ansi_sequence_bytes_truth.cend());
			REQUIRE(is_equal0);

			std::vector<std::byte> result1
			     = phd::text::encode(phd::text::tests::u32_unicode_sequence_truth, encoding);
			bool is_equal1 = std::equal(result1.cbegin(), result1.cend(),
			     phd::text::tests::w_unicode_sequence_bytes_truth.cbegin(),
			     phd::text::tests::w_unicode_sequence_bytes_truth.cend());
			REQUIRE(is_equal1);
		}
		SECTION("utf8") {
			phd::text::encoding_scheme<phd::text::utf8, phd::text::endian::native> encoding{};
			std::vector<std::byte> result0 = phd::text::encode(phd::text::tests::u32_ansi_sequence_truth, encoding);
			bool is_equal0                 = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u8_ansi_sequence_bytes_truth.cbegin(),
                    phd::text::tests::u8_ansi_sequence_bytes_truth.cend());
			REQUIRE(is_equal0);

			std::vector<std::byte> result1
			     = phd::text::encode(phd::text::tests::u32_unicode_sequence_truth, encoding);
			bool is_equal1 = std::equal(result1.cbegin(), result1.cend(),
			     phd::text::tests::u8_unicode_sequence_bytes_truth.cbegin(),
			     phd::text::tests::u8_unicode_sequence_bytes_truth.cend());
			REQUIRE(is_equal1);
		}
		SECTION("utf16") {
			phd::text::encoding_scheme<phd::text::utf16, phd::text::endian::native> encoding{};
			std::vector<std::byte> result0 = phd::text::encode(phd::text::tests::u32_ansi_sequence_truth, encoding);
			bool is_equal0                 = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u16_ansi_sequence_bytes_truth.cbegin(),
                    phd::text::tests::u16_ansi_sequence_bytes_truth.cend());
			REQUIRE(is_equal0);

			std::vector<std::byte> result1
			     = phd::text::encode(phd::text::tests::u32_unicode_sequence_truth, encoding);
			bool is_equal1 = std::equal(result1.cbegin(), result1.cend(),
			     phd::text::tests::u16_unicode_sequence_bytes_truth.cbegin(),
			     phd::text::tests::u16_unicode_sequence_bytes_truth.cend());
			REQUIRE(is_equal1);
		}
		SECTION("utf32") {
			phd::text::encoding_scheme<phd::text::utf32, phd::text::endian::native> encoding{};
			std::vector<std::byte> result0 = phd::text::encode(phd::text::tests::u32_ansi_sequence_truth, encoding);
			bool is_equal0                 = std::equal(result0.cbegin(), result0.cend(),
                    phd::text::tests::u32_ansi_sequence_bytes_truth.cbegin(),
                    phd::text::tests::u32_ansi_sequence_bytes_truth.cend());
			REQUIRE(is_equal0);

			std::vector<std::byte> result1
			     = phd::text::encode(phd::text::tests::u32_unicode_sequence_truth, encoding);
			bool is_equal1 = std::equal(result1.cbegin(), result1.cend(),
			     phd::text::tests::u32_unicode_sequence_bytes_truth.cbegin(),
			     phd::text::tests::u32_unicode_sequence_bytes_truth.cend());
			REQUIRE(is_equal1);
		}
	}
}
