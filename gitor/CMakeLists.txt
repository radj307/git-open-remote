# git-open-remote/gitor
cmake_minimum_required(VERSION 3.20)

file(GLOB HEADERS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"*.h*"
)
file(GLOB SRCS
	RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}"
	CONFIGURE_DEPENDS
	"*.c*"
)

file(MAKE_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/rc")
MAKE_VERSION_HEADER("${CMAKE_CURRENT_SOURCE_DIR}/rc/version.h" "gitor" "${gitopenremote_VERSION}")

add_executable (gitor "${SRCS}" "${CMAKE_CURRENT_SOURCE_DIR}/rc/version.h")

set_property(TARGET gitor PROPERTY CXX_STANDARD 20)
set_property(TARGET gitor PROPERTY CXX_STANDARD_REQUIRED ON)

if (MSVC)
	target_compile_options(gitor PRIVATE "/Zc:__cplusplus" "/Zc:preprocessor")
endif()

target_sources(gitor PRIVATE "${HEADERS}")

target_link_libraries(gitor PRIVATE TermAPI optlib filelib)

