#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "svc/StandardPayload.h"
#include "svc/TokenPayload.h"

TEST(Payloads, class) {
  svc::StandardPayload standardPayload("unused");
  standardPayload.setServiceName("standard_service");
  EXPECT_THAT(standardPayload.serviceName(), ::testing::StrEq("standard_service"));

  svc::TokenPayload tokenPayload("unused");
  tokenPayload.setServiceName("token_service");
  EXPECT_THAT(tokenPayload.serviceName(), ::testing::StrEq("token_service"));

  tokenPayload.setToken("token");
  EXPECT_THAT(tokenPayload.token(), ::testing::StrEq("token"));
}