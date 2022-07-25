#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "svc/Registry.h"

#include "ExampleServices.h"

class DirectRegistry : public ::testing::Test {
protected:
  txn::Registry _registry;

  void SetUp() override {
    registerTxnServices(_registry);
  }
};

TEST_F(DirectRegistry, standard_payload) {
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

TEST_F(DirectRegistry, token_payload) {
  txn::TokenPayload payload("token_payload", "token");

  txn::Status status1 = _registry.invokeToken("serv7", payload);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:token:-"));

  txn::Status status2 = _registry.invokeToken("serv8", payload);
  EXPECT_TRUE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("serviceB2:methodB2:token_payload:token:-"));
}

TEST_F(DirectRegistry, empty_token_payload) {
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

TEST_F(DirectRegistry, custom_init_service) {
  txn::StandardPayload payload("standard_payload");

  txn::Status status = _registry.invokeStandard("serv9", payload);
  EXPECT_TRUE(status);
  EXPECT_THAT(status.message(), ::testing::StrEq("serviceC2:methodA2:standard_payload:internal:-"));
}

TEST_F(DirectRegistry, service_not_found) {
  txn::StandardPayload standard_payload("standard_payload");
  txn::Status status1 = _registry.invokeStandard("unknown_service", standard_payload);
  EXPECT_FALSE(status1);

  txn::TokenPayload token_payload("token_payload");
  txn::Status status2 = _registry.invokeToken("unknown_service", token_payload);
  EXPECT_FALSE(status2);
}