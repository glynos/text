cmake_minimum_required(VERSION 3.13.0)

# # Project declaration
# informs about the project, gives a description, version and MOST IMPORTANTLY
# the languages the project is going to use. Required.
project(phd VERSION 0.5.0 DESCRIPTION "A spicy text library." LANGUAGES C CXX)

# # Modules
# Include modules useful to the project, whether locally made in our own cmake DIRECTORY
# our from the standard cmake libraries
# Add home-rolled modules path to front of module path list
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" "${CMAKE_MODULE_PATH}")

# # # Top-Level Directories
# Check if this is the top-level project or not
if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
    set(PHD_TEXT_IS_TOP_LEVEL_PROJECT true)
else()
    set(PHD_TEXT_IS_TOP_LEVEL_PROJECT false)
endif()

# Modify bad flags / change defaults if that is the case
if (PHD_TEXT_IS_TOP_LEVEL_PROJECT)
	if (CMAKE_SIZEOF_VOID_P EQUAL 4)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x86/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/lib")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/x64/${CMAKE_BUILD_TYPE}/${CFG_INT_DIR}/bin")
	endif()

	if (MSVC)
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_C_FLAGS ${CMAKE_C_FLAGS})
		string(REGEX REPLACE "/W[0-4]" "" CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS})
	endif()
endif()

# # Include standard modules
include(CMakeDependentOption)
include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

# # Options
option(PHD_TEXT_CI "Whether or not we are in continguous integration mode" OFF)
option(PHD_TEXT_TESTS "Enable build of tests" OFF)
option(PHD_TEXT_EXAMPLES "Enable build of examples" OFF)
option(PHD_TEXT_BENCHMARKS "Enable build of benchmarks" OFF)

# # Dependencies
add_subdirectory(vendor/ooficode)

set(phd.text.sources
	"include/phd/text.hpp"

	"include/phd/text/detail/adl.hpp"
	"include/phd/text/detail/range.hpp"
	"include/phd/text/detail/type_traits.hpp"
	"include/phd/text/detail/unicode.hpp"
	"include/phd/text/detail/windows.hpp"

	"include/phd/text/ascii.hpp"
	"include/phd/text/basic_c_string_view.hpp"
	"include/phd/text/basic_text_view.hpp"
	"include/phd/text/basic_text.hpp"
	"include/phd/text/c_string_view.hpp"
	"include/phd/text/char8_t.hpp"
	"include/phd/text/code_point.hpp"
	"include/phd/text/code_unit.hpp"
	"include/phd/text/decode.hpp"
	"include/phd/text/encode.hpp"
	"include/phd/text/encoding_error.hpp"
	"include/phd/text/encoding.hpp"
	"include/phd/text/error_handler.hpp"
	"include/phd/text/execution.hpp"
	"include/phd/text/is_code_point_replaceable.hpp"
	"include/phd/text/is_code_unit_replaceable.hpp"
	"include/phd/text/is_full_range_representable.hpp"
	"include/phd/text/is_ignorable_error_handler.hpp"
	"include/phd/text/is_transcoding_compatible.hpp"
	"include/phd/text/is_unicode_code_point.hpp"
	"include/phd/text/normalization.hpp"
	"include/phd/text/state.hpp"
	"include/phd/text/forward.hpp"
	"include/phd/text/text_traits.hpp"
	"include/phd/text/text_view.hpp"
	"include/phd/text/unicode_code_point.hpp"
	"include/phd/text/unicode_scalar_value.hpp"
	"include/phd/text/utf8.hpp"
	"include/phd/text/utf16.hpp"
	"include/phd/text/utf32.hpp"
	"include/phd/text/wide_execution.hpp"
)

add_library(phd.text INTERFACE)
add_library(phd::text ALIAS phd.text)
target_link_libraries(phd.text INTERFACE oof::ooficode)
target_include_directories(phd.text INTERFACE 
	$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
	$<INSTALL_INTERFACE:include>
)
if (MSVC)
	target_compile_options(phd.text INTERFACE 
		/std:c++latest
		/permissive-
	)
else()
	target_compile_options(phd.text INTERFACE 
		-std=c++2a
	)
endif()
target_sources(phd.text INTERFACE ${phd.text.sources})
#set_target_properties(phd.text
#	PROPERTIES
#	EXPORT_NAME phd::text
#)

# # Benchmarks, Tests, Examples
if (PHD_TEXT_TESTS OR PHD_TEXT_BENCHMARKS)
	enable_testing()
endif()
if (PHD_TEXT_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif(PHD_TEXT_TESTS)
if (PHD_TEXT_BENCHMARKS)
	add_subdirectory(benchmarks)
endif(PHD_TEXT_BENCHMARKS)
if (PHD_TEXT_EXAMPLES)
	add_subdirectory(examples)
endif(PHD_TEXT_EXAMPLES)

# # Config / Version packaging
# Version configurations
#configure_package_config_file(
#	cmake/phd-config.cmake.in
#	"${CMAKE_CURRENT_BINARY_DIR}/cmake/phd.text/phd.text-config.cmake"
#	INSTALL_DESTINATION lib/cmake/phd.text
#	NO_CHECK_REQUIRED_COMPONENTS_MACRO)

#write_basic_package_version_file(
#	"${CMAKE_CURRENT_BINARY_DIR}/cmake/phd.text/phd.text-config-version.cmake"
#	COMPATIBILITY AnyNewerVersion)

#export(TARGETS phd.text FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/phd.text/phd.text-targets.cmake")
