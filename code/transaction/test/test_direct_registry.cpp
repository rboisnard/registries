#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "txn/Registry.h"

#include "ExampleServices.h"

class DirectRegistry : public ::testing::Test {
protected:
  txn::Registry _registry;

  void SetUp() override {
    registerServices(_registry);
  }
};

TEST_F(DirectRegistry, standard_payload) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status1 = _registry.invokeStandard("serv1", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceA:methodA:standard_payload:-"));

  txn::Status status2 = _registry.invokeStandard("serv2", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceA:methodB:standard_payload:-"));
}

TEST_F(DirectRegistry, token_payload) {
  txn::TokenPayload payload("token_payload", "token");

  txn::Status status1 = _registry.invokeToken("serv3", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceB:methodA:token_payload:token:-"));

  txn::Status status2 = _registry.invokeToken("serv4", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceB:methodB:token_payload:token:-"));
}

TEST_F(DirectRegistry, empty_token_payload) {
  txn::TokenPayload payload("token_payload");
  EXPECT_THAT(payload.token(), ::testing::StrEq(""));

  payload.setToken("set_token");
  EXPECT_THAT(payload.token(), ::testing::StrEq("set_token"));

  txn::Status status = _registry.invokeToken("serv4", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceB:methodB:token_payload:set_token:-"));
}

TEST_F(DirectRegistry, custom_init_service) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status = _registry.invokeStandard("serv5", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceC:methodA:standard_payload:internal:-"));
}

TEST_F(DirectRegistry, service_not_found) {
  txn::StandardPayload standard_payload("standard_payload");
  txn::Status status1 = _registry.invokeStandard("unknown_service", standard_payload);
  EXPECT_FALSE(status1);

  txn::TokenPayload token_payload("token_payload");
  txn::Status status2 = _registry.invokeToken("unknown_service", token_payload);
  EXPECT_FALSE(status2);
}