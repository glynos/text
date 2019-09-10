#include <phd/text/encoding.hpp>

#include <catch2/catch.hpp>

#include <phd/text/tests/basic_unicode_strings.hpp>

#include <span>

TEST_CASE("text/encoding/core", "basic usages of encoding do not explode") {
	constexpr const std::size_t encode_output_max = 16;
	constexpr const std::size_t decode_output_max = 2;

	SECTION("decode") {
		SECTION("char") {
			phd::text::execution enc;

			phd::text::unicode_code_point output0[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
			phd::text::execution::state s{};
			auto result0 = enc.decode(phd::text::c_string_view(phd::text::tests::ansi_single_truth),
			     std::span<phd::text::unicode_code_point>(output0, 1), s, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_ansi_single_truth);
		}
		SECTION("wchar_t") {
			phd::text::wide_execution enc;

			phd::text::unicode_code_point output0[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
			phd::text::wide_execution::state s0{};
			auto result0 = enc.decode(phd::text::c_wstring_view(phd::text::tests::w_ansi_single_truth),
			     std::span<phd::text::unicode_code_point>(output0, 1), s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_ansi_single_truth);

			phd::text::unicode_code_point output1[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer1(output1, 1);
			phd::text::wide_execution::state s1{};
			auto result1 = enc.decode(phd::text::c_wstring_view(phd::text::tests::w_unicode_single_truth),
			     std::span<phd::text::unicode_code_point>(output1, 1), s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u32string_view(output1) == phd::text::tests::u32_unicode_single_truth);
		}
		SECTION("char8_t") {
			phd::text::utf8 enc;

			phd::text::unicode_code_point output0[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
			phd::text::utf8::state s0{};
			auto result0 = enc.decode(phd::text::c_u8string_view(phd::text::tests::u8_ansi_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_ansi_single_truth);

			phd::text::unicode_code_point output1[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer1(output1, 1);
			phd::text::utf8::state s1{};
			auto result1 = enc.decode(phd::text::c_u8string_view(phd::text::tests::u8_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u32string_view(output1) == phd::text::tests::u32_unicode_single_truth);
		}
		SECTION("char16_t") {
			phd::text::utf16 enc;

			phd::text::unicode_code_point output0[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
			phd::text::utf16::state s0{};
			auto result0 = enc.decode(phd::text::c_u16string_view(phd::text::tests::u16_ansi_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_ansi_single_truth);

			phd::text::unicode_code_point output1[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer1(output1, 1);
			phd::text::utf16::state s1{};
			auto result1 = enc.decode(phd::text::c_u16string_view(phd::text::tests::u16_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u32string_view(output1) == phd::text::tests::u32_unicode_single_truth);
		}
		SECTION("char32_t") {
			phd::text::utf32 enc;

			phd::text::unicode_code_point output0[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer0(output0, 1);
			phd::text::utf32::state s0{};
			auto result0 = enc.decode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_single_truth);

			phd::text::unicode_code_point output1[decode_output_max]{};
			std::span<phd::text::unicode_code_point> output_buffer1(output1, 1);
			phd::text::utf32::state s1{};
			auto result1 = enc.decode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_single_truth);
		}
	}
	SECTION("encode") {
		SECTION("char") {
			phd::text::execution enc;

			char output0[encode_output_max]{};
			std::span<char> output_buffer0(output0, encode_output_max);
			phd::text::execution::state s0{};
			auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_ansi_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_string_view(output0) == phd::text::tests::ansi_single_truth);
		}
		SECTION("wchar_t") {
			phd::text::wide_execution enc;

			wchar_t output0[encode_output_max]{};
			std::span<wchar_t> output_buffer0(output0, encode_output_max);
			phd::text::wide_execution::state s0{};
			auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_ansi_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_wstring_view(output0) == phd::text::tests::w_ansi_single_truth);

			wchar_t output1[encode_output_max]{};
			std::span<wchar_t> output_buffer1(output1, encode_output_max);
			phd::text::wide_execution::state s1{};
			auto result1 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_wstring_view(output1) == phd::text::tests::w_unicode_single_truth);
		}
		SECTION("char8_t") {
			phd::text::utf8 enc;

			char8_t output0[encode_output_max]{};
			std::span<char8_t> output_buffer0(output0, encode_output_max);
			phd::text::utf8::state s0{};
			auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_ansi_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u8string_view(output0) == phd::text::tests::u8_ansi_single_truth);

			char8_t output1[encode_output_max]{};
			std::span<char8_t> output_buffer1(output1, encode_output_max);
			phd::text::utf8::state s1{};
			auto result1 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u8string_view(output1) == phd::text::tests::u8_unicode_single_truth);
		}
		SECTION("char16_t") {
			phd::text::utf16 enc;

			char16_t output0[encode_output_max]{};
			std::span<char16_t> output_buffer0(output0, encode_output_max);
			phd::text::utf16::state s0{};
			auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u16string_view(output0) == phd::text::tests::u16_unicode_single_truth);

			char16_t output1[encode_output_max]{};
			std::span<char16_t> output_buffer1(output1, encode_output_max);
			phd::text::utf16::state s1{};
			auto result1 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u16string_view(output1) == phd::text::tests::u16_unicode_single_truth);
		}
		SECTION("char32_t") {
			phd::text::utf32 enc;

			char32_t output0[encode_output_max]{};
			std::span<char32_t> output_buffer0(output0, encode_output_max);
			phd::text::utf32::state s0{};
			auto result0 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer0, s0, phd::text::default_text_error_handler{});
			REQUIRE(result0.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result0.error());
			REQUIRE(phd::text::c_u32string_view(output0) == phd::text::tests::u32_unicode_single_truth);

			char32_t output1[encode_output_max]{};
			std::span<char32_t> output_buffer1(output1, encode_output_max);
			phd::text::utf32::state s1{};
			auto result1 = enc.encode(phd::text::c_u32string_view(phd::text::tests::u32_unicode_single_truth),
			     output_buffer1, s1, phd::text::default_text_error_handler{});
			REQUIRE(result1.error_code == phd::text::encoding_errc::ok);
			REQUIRE_FALSE(result1.error());
			REQUIRE(phd::text::c_u32string_view(output1) == phd::text::tests::u32_unicode_single_truth);
		}
	}
}
