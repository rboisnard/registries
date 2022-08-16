# test_status
add_executable(test_status_layer2)
target_sources(test_status_layer2
  PRIVATE
  test_status.cpp
)
target_link_libraries(test_status_layer2
  GTest::gtest_main
  service
)
target_compile_options(test_status_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_status_layer2
  COMMAND test_status_layer2
)

# test_payloads
add_executable(test_payloads_layer2)
target_sources(test_payloads_layer2
  PRIVATE
  test_payloads.cpp
)
target_link_libraries(test_payloads_layer2
  GTest::gtest_main
  service
)
target_compile_options(test_payloads_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_payloads_layer2
  COMMAND test_payloads_layer2
)

# test_adapters
add_executable(test_adapters_layer2)
target_sources(test_adapters_layer2
  PRIVATE
  test_adapters.cpp
  ../include/TxnStandardPayloadAdapter.h
  ../include/TxnStatusAdapter.h
  ../include/TxnTokenPayloadAdapter.h
)
target_link_libraries(test_adapters_layer2
  GTest::gtest_main
  service
)
target_compile_options(test_adapters_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_adapters_layer2
  COMMAND test_adapters_layer2
)

# helper library exampleservices
add_library(exampleservices_layer2 SHARED)
target_sources(exampleservices_layer2
  PRIVATE
  ExampleServices.cpp

  PUBLIC
  ExampleServices.h
)
target_link_libraries(exampleservices_layer2
  service
)
target_compile_options(exampleservices_layer2 PRIVATE
  -Wall -Wextra -Werror
)

# test_direct_registry
add_executable(test_direct_registry_layer2)
target_sources(test_direct_registry_layer2
  PRIVATE
  test_direct_registry.cpp
  ExampleServices.h
)
target_link_libraries(test_direct_registry_layer2
  GTest::gtest_main
  exampleservices_layer2
)
target_compile_options(test_direct_registry_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_direct_registry_layer2
  COMMAND test_direct_registry_layer2
)
set_property(TEST test_direct_registry_layer2
  PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/code/service/test"
)

# test_indirect_registry
add_executable(test_indirect_registry_layer2)
add_dependencies(test_indirect_registry_layer2 exampleservices)
target_sources(test_indirect_registry_layer2
  PRIVATE
  test_indirect_registry.cpp
  ExampleServices.h
)
target_link_libraries(test_indirect_registry_layer2
  GTest::gtest_main
  transaction
)
target_compile_options(test_indirect_registry_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_indirect_registry_layer2
  COMMAND test_indirect_registry_layer2
)
set(env_vars "")
string(JOIN ";" env_vars ${env_vars} "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/code/service:${CMAKE_BINARY_DIR}/code/service/test")
string(JOIN ";" env_vars ${env_vars} "APP_LIBRARY_NAME=libexampleservices_layer2.so")
string(JOIN ";" env_vars ${env_vars} "APP_INITILIZER_NAME=registerSvcServices")
string(JOIN ";" env_vars ${env_vars} "APP_FINALIZER_NAME=finalizeServices")
set_property(TEST test_indirect_registry_layer2
  PROPERTY ENVIRONMENT ${env_vars}
)

# test_registry_layer2
add_executable(test_registry_layer2)
target_sources(test_registry_layer2
  PRIVATE
  test_registry.cpp
)
target_link_libraries(test_registry_layer2
  GTest::gtest_main
  service
)
target_compile_options(test_registry_layer2 PRIVATE
  -Wall -Wextra -Werror
)
add_test(
  NAME test_registry_layer2
  COMMAND test_registry_layer2
)
set_property(TEST test_registry_layer2
  PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/code/service:${CMAKE_BINARY_DIR}/code/service/test"
)