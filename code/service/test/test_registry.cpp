#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <stdlib.h>

#include "svc/Registry.h"

TEST(Registry, service_not_found) {
  svc::Registry registry;

  txn::StandardPayload standard_payload("standard_payload");
  txn::Status status1 = registry.invoke("unknown_service", standard_payload);
  EXPECT_FALSE(status1);

  txn::TokenPayload token_payload("standard_payload", "token");
  txn::Status status2 = registry.invoke("unknown_service", token_payload);
  EXPECT_FALSE(status2);
}

TEST(Registry, init_close) {
  txn::Registry registry;
  unsetenv("APP_LIBRARY_NAME");
  unsetenv("APP_INITILIZER_NAME");
  unsetenv("APP_FINALIZER_NAME");

  // missing APP_LIBRARY_NAME
  ASSERT_FALSE(initLibrary(registry));

  setenv("APP_LIBRARY_NAME", "lib_does_not_exist.so", 1);
  // missing APP_INITILIZER_NAME
  ASSERT_FALSE(initLibrary(registry));

  setenv("APP_INITILIZER_NAME", "bad_name", 1);
  // wrong APP_LIBRARY_NAME
  ASSERT_FALSE(initLibrary(registry));
  // check when handle is NULL
  ASSERT_TRUE(closeLibrary());

  // good APP_LIBRARY_NAME
  // wrong APP_INITILIZER_NAME
  setenv("APP_LIBRARY_NAME", "libexampleservices_layer2.so", 1);
  ASSERT_FALSE(initLibrary(registry));

  // good APP_INITILIZER_NAME
  setenv("APP_INITILIZER_NAME", "registerSvcServices", 1);
  ASSERT_TRUE(initLibrary(registry));

  // missing APP_FINALIZER_NAME
  ASSERT_FALSE(closeLibrary());

  // reset test
  ASSERT_TRUE(initLibrary(registry));
  // wrong APP_FINALIZER_NAME
  setenv("APP_FINALIZER_NAME", "bad_name_again", 1);
  ASSERT_FALSE(closeLibrary());

  // reset test
  ASSERT_TRUE(initLibrary(registry));
  // good APP_FINALIZER_NAME
  setenv("APP_FINALIZER_NAME", "finalizeServices", 1);
  ASSERT_TRUE(closeLibrary());
}