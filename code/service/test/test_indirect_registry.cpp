#include <dlfcn.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "txn/Registry.h"

class IndirectRegistry : public ::testing::Test {
protected:
  txn::Registry _registry;
  void* _handle;

  IndirectRegistry() {}

  void SetUp() override {
    _handle = dlopen("libservice.so", RTLD_NOW);
    if (!_handle) {
      // blocking error
      ASSERT_TRUE(false);
    }
    // reset errors
    dlerror();

    txn::initializer_t initializer = (txn::initializer_t)dlsym(_handle, "initLibrary");
    if (dlerror()) {
      dlclose(_handle);
      // blocking error
      ASSERT_TRUE(false);
    }

    bool status = initializer(_registry);
    if (!status) {
      dlclose(_handle);
    }
    // blocking error
    ASSERT_TRUE(status);
  }

  void TearDown() override {
    if (_handle) {
      txn::finalizer_t finalizer = (txn::finalizer_t)dlsym(_handle, "closeLibrary");
      if (dlerror()) {
        dlclose(_handle);
        // blocking error
        ASSERT_TRUE(false);
      }

      bool status = finalizer();
      dlclose(_handle);
      // blocking error
      ASSERT_TRUE(status);
    }
  }
};

TEST_F(IndirectRegistry, standard_payload) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status1 = _registry.invokeStandard("serv1", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceA2:methodA2:standard_payload:-"));

  txn::Status status2 = _registry.invokeStandard("serv2", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceA2:methodA2:standard_payload:-"));

  txn::Status status3 = _registry.invokeStandard("serv3", payload);
  EXPECT_TRUE(status3);
  EXPECT_THAT(status3.message(), ::testing::StrEq("serviceA2:methodB2:standard_payload:-"));

  txn::Status status4 = _registry.invokeStandard("serv4", payload);
  EXPECT_TRUE(status4);
  EXPECT_THAT(status4.message(), ::testing::StrEq("serviceA2:methodB2:standard_payload:-"));

  txn::Status status5 = _registry.invokeStandard("serv5", payload);
  EXPECT_TRUE(status5);
  EXPECT_THAT(status5.message(), ::testing::StrEq("serviceB2:methodA2:standard_payload:-"));

  txn::Status status6 = _registry.invokeStandard("serv6", payload);
  EXPECT_TRUE(status6);
  EXPECT_THAT(status6.message(), ::testing::StrEq("serviceB2:methodA2:standard_payload:-"));
}

TEST_F(IndirectRegistry, token_payload) {
  txn::TokenPayload payload("token_payload", "token");

  txn::Status status1 = _registry.invokeToken("serv7", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:token:-"));

  txn::Status status2 = _registry.invokeToken("serv8", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:token:-"));
}

TEST_F(IndirectRegistry, empty_token_payload) {
  txn::TokenPayload payload("token_payload");
  EXPECT_THAT(payload.token(), ::testing::StrEq(""));

  payload.setToken("set_token");
  EXPECT_THAT(payload.token(), ::testing::StrEq("set_token"));

  txn::Status status1 = _registry.invokeToken("serv7", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:set_token:-"));

  txn::Status status2 = _registry.invokeToken("serv8", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:set_token:-"));
}

TEST_F(IndirectRegistry, custom_init_service) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status = _registry.invokeStandard("serv9", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceC2:methodA2:standard_payload:internal:-"));
}

TEST_F(IndirectRegistry, service_not_found) {
  txn::StandardPayload standard_payload("standard_payload");
  txn::Status status1 = _registry.invokeStandard("unknown_service", standard_payload);
  EXPECT_FALSE(status1);

  txn::TokenPayload token_payload("token_payload");
  txn::Status status2 = _registry.invokeToken("unknown_service", token_payload);
  EXPECT_FALSE(status2);
}