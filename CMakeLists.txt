cmake_minimum_required(VERSION 3.22)

project(
  registries
  VERSION 0.1
)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules)
include(OutOfSourceCheck)
check_out_of_source_build()

include(CodeQuality)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(code)