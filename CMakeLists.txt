cmake_minimum_required(VERSION 2.8.9)

project (ert)

#find_package(PkgConfig)
#pkg_check_modules(GTEST REQUIRED gtest>=1.7.0)
#pkg_check_modules(GMOCK REQUIRED gmock>=1.7.0)
find_package(GTest REQUIRED)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_build/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/_build/bin)

include_directories(./inc ./test)

file(GLOB LIB_SOURCES "src/*.c")
file(GLOB TEST_SOURCES "test/*.cpp")

add_library(ert STATIC ${LIB_SOURCES})

# Add test cpp file
add_executable(ert_test ${TEST_SOURCES})

add_dependencies(ert_test libgtest)
# Link test executable against gtest & gtest_main
target_link_libraries(ert_test pthread ${GTEST_LIBRARIES} ${CMAKE_BINARY_DIR}/_build/lib/libert.a)

enable_testing()
add_test(ert_test ${CMAKE_BINARY_DIR}/_build/bin/ert_test)
