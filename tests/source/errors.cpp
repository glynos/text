#include <phd/text/encoding.hpp>

#include <catch2/catch.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

#include <iostream>
#include <span>

TEST_CASE("text/encoding/errors", "invalid characters are handled") {
	constexpr const std::size_t encode_output_max = 16;
	constexpr const std::size_t decode_output_max = 2;

	SECTION("replacement characters") {
		SECTION("decode") {
			SECTION("char8_t") {
				phd::text::utf8 enc;

				phd::text::unicode_code_point output0[decode_output_max]{};
				std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
				phd::text::utf8::state s0{};
				auto result0 = enc.decode(phd::text::c_u8string_view(phd::text::tests::u8_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_replacement_truth);
			}
			SECTION("char16_t") {
				phd::text::utf16 enc;

				phd::text::unicode_code_point output0[decode_output_max]{};
				std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
				phd::text::utf16::state s0{};
				auto result0 = enc.decode(phd::text::c_u16string_view(phd::text::tests::u16_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_replacement_truth);
			}
			SECTION("char32_t") {
				phd::text::utf32 enc;

				char32_t output0[decode_output_max]{};
				std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
				phd::text::utf32::state s0{};
				auto result0 = enc.decode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_replacement_truth);
			}
		}
		SECTION("encode") {
			SECTION("char8_t") {
				phd::text::utf8 enc;

				char8_t output0[encode_output_max]{};
				std::span<char8_t> output_buffer0(output0, encode_output_max);
				phd::text::utf8::state s0{};
				auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u8string_view(output0) == phd::text::tests::u8_unicode_replacement_truth);
			}
			SECTION("char16_t") {
				phd::text::utf16 enc;

				char16_t output0[encode_output_max]{};
				std::span<char16_t> output_buffer0(output0, encode_output_max);
				phd::text::utf16::state s0{};
				auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u16string_view(output0) == phd::text::tests::u16_unicode_replacement_truth);
			}
			SECTION("char32_t") {
				phd::text::utf32 enc;

				char32_t output0[encode_output_max]{};
				std::span<char32_t> output_buffer0(output0, encode_output_max);
				phd::text::utf32::state s0{};
				auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_invalid_input),
				     output_buffer0, s0, phd::text::default_text_error_handler{});
				REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
				REQUIRE_FALSE(result0.error());
				REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_replacement_truth);
			}
		}
	}
}
