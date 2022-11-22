if (WIN32)
    set(MINI_VERSION 3.15.0)
else()
    set(MINI_VERSION 3.13.0)
endif()

cmake_minimum_required(VERSION ${MINI_VERSION})
project(UdiServer)

# conan
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

# include header
include_directories(${PROJECT_SOURCE_DIR})

# c++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# setup version
if(NOT "$ENV{UDI_SERVICE_VERSION}" STREQUAL "")
    add_compile_definitions(UDI_SERVICE_VERSION="$ENV{UDI_SERVICE_VERSION}")
    message("-- UDI: Version Defined as $ENV{UDI_SERVICE_VERSION}")
else()
    add_compile_definitions(UDI_SERVICE_VERSION="U.0.0.0.0")
endif()

if(NOT "$ENV{GIT_COMMIT_HASH}" STREQUAL "")
    add_compile_definitions(UDI_GIT_HASH="$ENV{GIT_COMMIT_HASH}")
    message("-- UDI: Current HEAD hash: $ENV{GIT_COMMIT_HASH}")
endif()

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug ... FORCE)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("-- UDI: Release Build")
else()
    message("-- UDI: Debug Build")
    add_compile_definitions(UDI_DEBUG)
endif()

if("$ENV{SELF_UPGRADE}" STREQUAL "0")
    add_compile_definitions(SELF_UPGRADE=0)
    message("-- UDI: SELF_UPGRADE=OFF")
endif()

if(WIN32)
    add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    add_definitions(-D_WIN32_WINNT=0x0601)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
    add_definitions(-D_SILENCE_ALL_CXX17_DEPRECATION_WARNINGS)

    add_definitions(-DBOOST_SYSTEM_USE_UTF8) # 使用 UTF-8 编码

    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ignore:4099")
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if (UNIX AND NOT ANDROID)
    add_compile_definitions(JM_XORSTR_DISABLE_AVX_INTRINSICS)
endif()


set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/out)

option(UDI_STATIC_CHECK "Static Check" OFF)

if(UDI_STATIC_CHECK)
    message("-- UDI: enable clang-tidy")
    set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
endif()

option(UDI_BUILD_ALL "Build All Module" OFF)
option(UDI_BUILD_TESTS "Build Unitest" OFF)
option(UDI_BUILD_ASSISTANT "Build Udi Assistant" OFF)
option(UDI_BUILD_TOOLS "Build Udi Tools" OFF)
option(UDI_BUILD_TOOL_GUI "Build UdiUi" OFF)
option(UDI_BUILD_TOOL_CLI "Build UdiCli" OFF)

if(UDI_BUILD_ALL)
    set(UDI_BUILD_TESTS ON)
    set(UDI_BUILD_ASSISTANT ON)
    set(UDI_BUILD_TOOLS ON)
    set(UDI_BUILD_TOOL_GUI ON)
    set(UDI_BUILD_TOOL_CLI ON)
endif()

if(UDI_BUILD_ASSISTANT)
    set(UDI_BUILD_TOOL_GUI ON)
endif()


add_subdirectory(./tests)
# add_subdirectory(./src)

