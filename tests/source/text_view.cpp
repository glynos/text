#include <phd/text/text_view.hpp>

#include <catch2/catch.hpp>

TEST_CASE("text/text_view/basic", "basic usages of text_view do not explode") {
	SECTION("char") {
		phd::text::text_view t;
	}
	SECTION("wchar_t") {
		phd::text::wtext_view t;
	}
	SECTION("char8_t") {
		phd::text::u8text_view t;
	}
	SECTION("char16_t") {
		phd::text::u16text_view t;
	}
	SECTION("char32_t") {
		phd::text::u32text_view t;
	}
}
