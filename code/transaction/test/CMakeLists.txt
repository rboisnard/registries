add_executable(test_direct_registry
  test_direct_registry.cpp
)
target_link_libraries(test_direct_registry
  GTest::gtest_main
  transaction
)

add_test(
  NAME test_direct_registry
  COMMAND test_direct_registry
)