// Week 1, Day 5: Memory Management + Banking System
// Project Status: Banking System (OOP Design)

#include "bank_account.h"
#include <gtest/gtest.h>

TEST(Day5BankingSystemTest, Deposit) {
  BankAccount acc(1, 100.0);
  acc.deposit(50.0);
  EXPECT_DOUBLE_EQ(acc.getBalance(), 150.0);
}

TEST(Day5BankingSystemTest, Withdraw) {
  BankAccount acc(1, 100.0);
  EXPECT_TRUE(acc.withdraw(50.0));
  EXPECT_DOUBLE_EQ(acc.getBalance(), 50.0);
}

TEST(Day5BankingSystemTest, InsufficientFunds) {
  BankAccount acc(1, 100.0);
  EXPECT_FALSE(acc.withdraw(150.0));
  EXPECT_DOUBLE_EQ(acc.getBalance(), 100.0);
}

int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
