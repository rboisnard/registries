get_property(isMultiConfig GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)

if(isMultiConfig)
if(NOT "Asan" IN_LIST CMAKE_CONFIGURATION_TYPES)
  list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
endif()
if(NOT "Lsan" IN_LIST CMAKE_CONFIGURATION_TYPES)
  list(APPEND CMAKE_CONFIGURATION_TYPES Asan)
endif()
  if(NOT "GCov" IN_LIST CMAKE_CONFIGURATION_TYPES)
    list(APPEND CMAKE_CONFIGURATION_TYPES GCov)
  endif()
else()
  set(allowedBuildTypes Asan Lsan GCov Debug Release)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "${allowedBuildTypes}")

  if(CMAKE_BUILD_TYPE AND NOT CMAKE_BUILD_TYPE IN_LIST allowedBuildTypes)
    message(FATAL_ERROR "Invalid build type: ${CMAKE_BUILD_TYPE}")
  endif()
endif()

# Address sanitizer
set(CMAKE_C_FLAGS_ASAN
  "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C compiler for Asan build type or configuration." FORCE)

set(CMAKE_CXX_FLAGS_ASAN
  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C++ compiler for Asan build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_ASAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
  "Linker flags to be used to create executables for Asan build type." FORCE)

set(CMAKE_SHARED_LINKER_FLAGS_ASAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=address" CACHE STRING
  "Linker lags to be used to create shared libraries for Asan build type." FORCE)

# Leak sanitizer
set(CMAKE_C_FLAGS_LSAN
  "${CMAKE_C_FLAGS_DEBUG} -fsanitize=leak -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C compiler for Lsan build type or configuration." FORCE)

set(CMAKE_CXX_FLAGS_LSAN
  "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=leak -fno-omit-frame-pointer" CACHE STRING
  "Flags used by the C++ compiler for Lsan build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_LSAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=leak" CACHE STRING
  "Linker flags to be used to create executables for Lsan build type." FORCE)

set(CMAKE_SHARED_LINKER_FLAGS_LSAN
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fsanitize=leak" CACHE STRING
  "Linker lags to be used to create shared libraries for Lsan build type." FORCE)

# GCov
set(CMAKE_C_FLAGS_GCOV
  "${CMAKE_C_FLAGS_DEBUG} -g -O0 -fprofile-arcs -ftest-coverage" CACHE STRING
  "Flags used by the C compiler for GCov build type or configuration." FORCE)

set(CMAKE_CXX_FLAGS_GCOV
  "${CMAKE_CXX_FLAGS_DEBUG} -g -O0 -fprofile-arcs -ftest-coverage" CACHE STRING
  "Flags used by the C++ compiler for GCov build type or configuration." FORCE)

set(CMAKE_EXE_LINKER_FLAGS_GCOV
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" CACHE STRING
  "Linker flags to be used to create executables for GCov build type." FORCE)

set(CMAKE_SHARED_LINKER_FLAGS_GCOV
  "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" CACHE STRING
  "Linker lags to be used to create shared libraries for GCov build type." FORCE)