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

# helper library exampledirect
add_library(exampledirect SHARED)
target_sources(exampledirect
  PRIVATE
  ExampleDirect.cpp

  PUBLIC
  ExampleDirect.h
)
target_link_libraries(exampledirect
  exampleservices_layer2
)

# helper library exampleindirect
add_library(exampleindirect SHARED)
target_sources(exampleindirect
  PRIVATE
  ExampleIndirect.cpp

  PUBLIC
  ExampleIndirect.h
)
target_link_libraries(exampleindirect
  transaction
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
  exampledirect
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
add_dependencies (test_indirect_registry_layer2 exampleservices)
target_sources(test_indirect_registry_layer2
  PRIVATE
  test_indirect_registry.cpp
  ExampleServices.h
)
target_link_libraries(test_indirect_registry_layer2
  GTest::gtest_main
  exampleindirect
)
add_test(
  NAME test_indirect_registry_layer2
  COMMAND test_indirect_registry_layer2
)

set_property(TEST test_indirect_registry_layer2
  PROPERTY ENVIRONMENT "LD_LIBRARY_PATH=${CMAKE_BINARY_DIR}/code/service\\$<SEMICOLON>${CMAKE_BINARY_DIR}/code/service/test;APP_LIBRARY_NAME=libexampleservices_layer2.so;APP_INITILIZER_NAME=registerSvcServices;APP_FINALIZER_NAME=finalizeServices"
)