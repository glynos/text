# ============================================================================
#
# phd.text
# Copyright © 2019 JeanHeyd "ThePhD" Meneide
# Contact: phdofthehouse@gmail.com
#
# Commercial License Usage
# Licensees holding valid commercial phd.text licenses may use this file in
# accordance with the commercial license agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and JeanHeyd "ThePhD" Meneide.
# For licensing terms and conditions see your agreement. For
# further information contact phdofthehouse@gmail.com.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of GNU General
# Public license version 3. The licenses are as published by the Free
# Software Foundation and appearing in the file LICENSE included in the
# packaging of this file. Please review the following information to
# ensure the GNU General Public License requirements will
# be met: https://www.gnu.org/licenses/gpl-3.0.html.
#
# ============================================================================

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
