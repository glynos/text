# # Dependencies (test-specific)
add_subdirectory(../vendor/Catch2 "phd.text/tests/vendor/Catch2")

# # Tests
set(phd.text.test.sources
	"source/decode.cpp"
	"source/decode_view.cpp"

	"source/encode.cpp"
	"source/encode_view.cpp"

	"source/transcode.cpp"
	"source/transcode_view.cpp"
	"source/errors.cpp"

	"source/encoding_scheme.decode.cpp"
	"source/encoding_scheme.encode.cpp"

	"source/encoding.cpp"

	"source/text.cpp"
	"source/text_view.cpp"

	"source/main.cpp"
)

add_executable(phd.text.test ${phd.text.test.sources})
if (MSVC)
	target_compile_options(phd.text.test
		PRIVATE /std:c++latest /utf-8 /permissive- /experimental:preprocessor)
else()
	target_compile_options(phd.text.test
		PRIVATE -std=c++2a -Wall-Werror -Wpedantic)
endif()
target_include_directories(phd.text.test
	PRIVATE 
	"${CMAKE_CURRENT_SOURCE_DIR}/include")
target_link_libraries(phd.text.test 
	PRIVATE
	phd::text
	Catch2::Catch2
	${CMAKE_DL_LIBS}
)
add_test(NAME phd.text.test COMMAND phd.text.test)
