#!/bin/sh

### conf

TARGETS="
  code/transaction:transaction
  code/transaction/test:test_direct_registry
"

### functions

runcheck() {
  error_message=$1
  shift
  eval "$@"
  if [ $? -ne 0 ]; then
    echo "error with ${error_message}\n"
    exit 1
  fi
}

runtest() {
  OLD_PWD=$(pwd)
  cd ${SCRIPT_PATH}/builds/$1
  runcheck "tests for $1" ctest -j6 -C Asan -T test --output-on-failure
  cd ${OLD_PWD}
}

list_coverage_targets() {
  dir_option=""
  for item in $(echo ${TARGETS}); do
    dir_option="${dir_option} $(echo $item | awk -F ":" -v script_path=${SCRIPT_PATH}/builds/$1 '{print "-d "script_path"/"$1"/CMakeFiles/"$2".dir"}')"
  done
  echo ${dir_option}
}

init_coverage() {
  if [ "x$1" = "xGCov" ]; then
    runcheck "coverage init"      \
      lcov -c -i                  \
      -b ${SCRIPT_PATH}           \
      $(list_coverage_targets $1) \
      -o ${SCRIPT_PATH}/builds/$1/gcov.info
  fi
}

capture_coverage() {
  if [ "x$1" = "xGCov" ]; then
    runcheck "coverage capture"   \
      lcov -c                     \
      -b ${SCRIPT_PATH}           \
      $(list_coverage_targets $1) \
      -o ${SCRIPT_PATH}/builds/$1/gcov.info
    
    runcheck "coverage filter"                  \
    lcov                                        \
    --remove ${SCRIPT_PATH}/builds/$1/gcov.info \
    '/usr/include/c++/11/bits/*'                \
    '/usr/include/c++/11/ext/*'                 \
    '/usr/include/c++/11/*'                     \
    '/usr/include/gtest/*'                      \
    '/usr/include/gtest/internal/*'             \
    -o ${SCRIPT_PATH}/builds/$1/gcov.info

    runcheck "coverage report" genhtml -o builds/coverage_report ${SCRIPT_PATH}/builds/$1/gcov.info
    echo "\n==> open report file://${SCRIPT_PATH}/builds/coverage_report/index.html\n"
  fi
}

build_for_type() {
  echo "building for type $1"

  runcheck "cmake configuration for $1"        \
    cmake                                     \
    -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE \
    -DCMAKE_BUILD_TYPE:STRING=$1              \
    -S${SCRIPT_PATH}                          \
    -B${SCRIPT_PATH}/builds/$1                \
    -G "Unix\ Makefiles"

  runcheck "cmake build for $1"                \
    cmake                                     \
    --build ${SCRIPT_PATH}/builds/$1          \
    --config $1                               \
    --target all                              \
    -j 6

  init_coverage $1
  runtest $1
  capture_coverage $1
}

### main

SCRIPT_PATH=$(dirname $(readlink -f $0))

build_for_type Asan
build_for_type Lsan
build_for_type GCov
build_for_type Debug
build_for_type Release