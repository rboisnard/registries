#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "TxnStandardPayloadAdapter.h"
#include "TxnStatusAdapter.h"
#include "TxnTokenPayloadAdapter.h"

TEST(Adapters, status) {
  svc::TxnStatusAdapter status1(0);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq(""));
  EXPECT_EQ(status1.code(), 0);

  status1.setMessage("message1");
  EXPECT_THAT(status1.message(), ::testing::StrEq("message1"));

  std::stringstream stream;
  stream << "message2";
  status1.setMessage(stream);
  EXPECT_THAT(status1.message(), ::testing::StrEq("message2"));

  svc::TxnStatusAdapter status2(1, "message3");
  EXPECT_FALSE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("message3"));
  EXPECT_EQ(status2.code(), 1);

  stream << status2;
  EXPECT_THAT(stream.str(), ::testing::StrEq("message2message3"));
}

TEST(Adapters, standard) {
  svc::StandardPayload svcPayload("standard_payload");
  svcPayload.setServiceName("standard_service");

  svc::TxnStandardPayloadAdapter adaptedPayload(svcPayload);
  EXPECT_THAT(adaptedPayload.data(), ::testing::StrEq("standard_payload"));
  EXPECT_THAT(adaptedPayload.serviceName(), ::testing::StrEq("standard_service"));

  EXPECT_THAT(adaptedPayload.asTxnStandardPayload().data(), ::testing::StrEq("standard_payload"));
  EXPECT_THAT(adaptedPayload.asTxnStandardPayload().serviceName(), ::testing::StrEq("standard_service"));
}

TEST(Adapters, token) {
  svc::TokenPayload svcPayload("token_payload", "token");
  svcPayload.setServiceName("token_service");

  svc::TxnTokenPayloadAdapter adaptedPayload(svcPayload);
  EXPECT_THAT(adaptedPayload.data(), ::testing::StrEq("token_payload"));
  EXPECT_THAT(adaptedPayload.token(), ::testing::StrEq("token"));
  EXPECT_THAT(adaptedPayload.serviceName(), ::testing::StrEq("token_service"));

  EXPECT_THAT(adaptedPayload.asTxnTokenPayload().data(), ::testing::StrEq("token_payload"));
  EXPECT_THAT(adaptedPayload.asTxnTokenPayload().token(), ::testing::StrEq("token"));
  EXPECT_THAT(adaptedPayload.asTxnTokenPayload().serviceName(), ::testing::StrEq("token_service"));
}