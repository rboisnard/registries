#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "svc/StandardPayload.h"
#include "svc/TokenPayload.h"

TEST(Payloads, class) {
  svc::StandardPayload standardPayload("standard_payload");
  EXPECT_THAT(standardPayload.data(), ::testing::StrEq("standard_payload"));

  svc::TokenPayload tokenPayload("token_payload");
  EXPECT_THAT(tokenPayload.data(), ::testing::StrEq("token_payload"));

  tokenPayload.setToken("token");
  EXPECT_THAT(tokenPayload.token(), ::testing::StrEq("token"));
}