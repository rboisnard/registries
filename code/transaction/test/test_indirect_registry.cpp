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
    _handle = dlopen("libexampleservices.so", RTLD_NOW);
    if (!_handle) {
      // blocking error
      ASSERT_TRUE(false);
    }
    // reset errors
    dlerror();

    txn::initializer_t initializer = (txn::initializer_t)dlsym(_handle, "registerServices");
    if (dlerror()) {
      dlclose(_handle);
      // blocking error
      ASSERT_TRUE(false);
    }

    bool status = initializer(_registry);
    EXPECT_TRUE(status);
    if (!status) {
      dlclose(_handle);
    }
  }

  void TearDown() override {
    if (_handle) {
      dlclose(_handle);
    }
  }
};

TEST_F(IndirectRegistry, standard_payload) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status1 = _registry.invokeStandard("serv1", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceA:methodA:standard_payload:-"));

  txn::Status status2 = _registry.invokeStandard("serv2", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceA:methodB:standard_payload:-"));
}

TEST_F(IndirectRegistry, token_payload) {
  txn::TokenPayload payload("token_payload", "token");

  txn::Status status1 = _registry.invokeToken("serv3", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceB:methodA:token_payload:token:-"));

  txn::Status status2 = _registry.invokeToken("serv4", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceB:methodB:token_payload:token:-"));
}

TEST_F(IndirectRegistry, empty_token_payload) {
  txn::TokenPayload payload("token_payload");
  EXPECT_THAT(payload.token(), ::testing::StrEq(""));

  payload.setToken("set_token");
  EXPECT_THAT(payload.token(), ::testing::StrEq("set_token"));

  txn::Status status = _registry.invokeToken("serv4", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceB:methodB:token_payload:set_token:-"));
}

TEST_F(IndirectRegistry, custom_init_service) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status = _registry.invokeStandard("serv5", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceC:methodA:standard_payload:internal:-"));
}

TEST_F(IndirectRegistry, service_not_found) {
  txn::StandardPayload standard_payload("standard_payload");
  txn::Status status1 = _registry.invokeStandard("unknown_service", standard_payload);
  EXPECT_FALSE(status1);

  txn::TokenPayload token_payload("token_payload");
  txn::Status status2 = _registry.invokeToken("unknown_service", token_payload);
  EXPECT_FALSE(status2);
}