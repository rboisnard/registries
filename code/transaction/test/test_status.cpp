#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>

#include "txn/Status.h"

TEST(Status, class) {
  txn::Status status1(0);
  EXPECT_TRUE(status1);
  EXPECT_THAT(status1.message(), ::testing::StrEq(""));
  EXPECT_EQ(status1.code(), 0);

  status1.setMessage("message1");
  EXPECT_THAT(status1.message(), ::testing::StrEq("message1"));

  std::stringstream stream;
  stream << "message2";
  status1.setMessage(stream);
  EXPECT_THAT(status1.message(), ::testing::StrEq("message2"));

  txn::Status status2(1, "message3");
  EXPECT_FALSE(status2);
  EXPECT_THAT(status2.message(), ::testing::StrEq("message3"));
  EXPECT_EQ(status2.code(), 1);

  stream << status2;
  EXPECT_THAT(stream.str(), ::testing::StrEq("message2message3"));
}

