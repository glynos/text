#include <phd/text/text.hpp>

#include <catch2/catch.hpp>

TEST_CASE("text/text/basic", "basic usages of text do not explode") {
	SECTION("char") {
		phd::text::text t;
	}
	SECTION("wchar_t") {
		phd::text::wtext t;
	}
	SECTION("char8_t") {
		phd::text::u8text t;
	}
	SECTION("char16_t") {
		phd::text::u16text t;
	}
	SECTION("char32_t") {
		phd::text::u32text t;
	}
}
