cmake_minimum_required(VERSION 3.22)

project(
  registries
  VERSION 0.1
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)

# out of source build
include(OutOfSourceCheck)
check_out_of_source_build()

# sanitizers and gcov
include(CodeQuality)

# Google Test
find_package(GTest)
include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(code)