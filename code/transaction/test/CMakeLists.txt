# test_status
add_executable(test_status)
target_sources(test_status
  PRIVATE
  test_status.cpp
)
target_link_libraries(test_status
  GTest::gtest_main
  transaction
)
add_test(
  NAME test_status
  COMMAND test_status
)

# helper library exampleservices
add_library(exampleservices SHARED)
target_sources(exampleservices
  PRIVATE
  ExampleServices.cpp

  PUBLIC
  ExampleServices.h
)
target_link_libraries(exampleservices
  transaction
)

# test_direct_registry
add_executable(test_direct_registry)
target_sources(test_direct_registry
  PRIVATE
  test_direct_registry.cpp
  ExampleServices.h
)
target_link_libraries(test_direct_registry
  GTest::gtest_main
  transaction
  exampleservices
)
add_test(
  NAME test_direct_registry
  COMMAND test_direct_registry
)

# test_indirect_registry
add_executable(test_indirect_registry)
add_dependencies (test_indirect_registry exampleservices)
target_sources(test_indirect_registry
  PRIVATE
  test_indirect_registry.cpp
  ExampleServices.h
)
target_link_libraries(test_indirect_registry
  GTest::gtest_main
  transaction
)
add_test(
  NAME test_indirect_registry
  COMMAND test_indirect_registry
)

set_property(TEST test_indirect_registry PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/code/transaction/test")