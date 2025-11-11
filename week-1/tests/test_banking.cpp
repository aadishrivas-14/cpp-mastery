#include <gtest/gtest.h>
#include <memory>
#include "account.h"
#include "savings_account.h"
#include "checking_account.h"
#include "bank.h"

class BankingTest : public ::testing::Test {
protected:
    void SetUp() override {
        bank = std::make_unique<Bank>();
    }
    
    std::unique_ptr<Bank> bank;
};

// Account basic functionality
TEST_F(BankingTest, CreatesAccountWithInitialBalance) {
    auto account = bank->createAccount("Alice", AccountType::SAVINGS, 1000.0);
    EXPECT_EQ(account->getBalance(), 1000.0);
    EXPECT_EQ(account->getOwner(), "Alice");
}

TEST_F(BankingTest, DepositsMoneyToAccount) {
    auto account = bank->createAccount("Bob", AccountType::CHECKING, 500.0);
    account->deposit(200.0);
    EXPECT_EQ(account->getBalance(), 700.0);
}

TEST_F(BankingTest, WithdrawsMoneyFromAccount) {
    auto account = bank->createAccount("Charlie", AccountType::SAVINGS, 1000.0);
    EXPECT_TRUE(account->withdraw(300.0));
    EXPECT_EQ(account->getBalance(), 700.0);
}

TEST_F(BankingTest, RejectsWithdrawalWhenInsufficientFunds) {
    auto account = bank->createAccount("Dave", AccountType::SAVINGS, 100.0);
    EXPECT_FALSE(account->withdraw(200.0));
    EXPECT_EQ(account->getBalance(), 100.0);
}

TEST_F(BankingTest, RejectsNegativeDeposit) {
    auto account = bank->createAccount("Eve", AccountType::CHECKING, 500.0);
    EXPECT_THROW(account->deposit(-100.0), std::invalid_argument);
}

TEST_F(BankingTest, RejectsNegativeWithdrawal) {
    auto account = bank->createAccount("Frank", AccountType::SAVINGS, 500.0);
    EXPECT_THROW(account->withdraw(-50.0), std::invalid_argument);
}

// Savings account specific tests
TEST_F(BankingTest, SavingsAccountAppliesInterest) {
    auto savings = std::dynamic_pointer_cast<SavingsAccount>(
        bank->createAccount("Grace", AccountType::SAVINGS, 1000.0, 5.0)
    );
    savings->applyInterest();
    EXPECT_EQ(savings->getBalance(), 1050.0);
}

TEST_F(BankingTest, SavingsAccountHasMinimumBalance) {
    auto savings = std::dynamic_pointer_cast<SavingsAccount>(
        bank->createAccount("Henry", AccountType::SAVINGS, 500.0)
    );
    EXPECT_FALSE(savings->withdraw(450.0)); // Would go below minimum
    EXPECT_EQ(savings->getBalance(), 500.0);
}

// Checking account specific tests
TEST_F(BankingTest, CheckingAccountAllowsOverdraft) {
    auto checking = std::dynamic_pointer_cast<CheckingAccount>(
        bank->createAccount("Ivy", AccountType::CHECKING, 100.0, 0.0, 200.0)
    );
    EXPECT_TRUE(checking->withdraw(250.0));
    EXPECT_EQ(checking->getBalance(), -150.0);
}

TEST_F(BankingTest, CheckingAccountChargesOverdraftFee) {
    auto checking = std::dynamic_pointer_cast<CheckingAccount>(
        bank->createAccount("Jack", AccountType::CHECKING, 100.0, 0.0, 200.0)
    );
    checking->withdraw(150.0); // Goes into overdraft
    EXPECT_LT(checking->getBalance(), -50.0); // Should have fee applied
}

// Transfer functionality
TEST_F(BankingTest, TransfersBetweenAccounts) {
    auto account1 = bank->createAccount("Kate", AccountType::CHECKING, 1000.0);
    auto account2 = bank->createAccount("Liam", AccountType::SAVINGS, 500.0);
    
    EXPECT_TRUE(bank->transfer(account1, account2, 200.0));
    EXPECT_EQ(account1->getBalance(), 800.0);
    EXPECT_EQ(account2->getBalance(), 700.0);
}

TEST_F(BankingTest, RejectsTransferWithInsufficientFunds) {
    auto account1 = bank->createAccount("Mia", AccountType::SAVINGS, 100.0);
    auto account2 = bank->createAccount("Noah", AccountType::CHECKING, 500.0);
    
    EXPECT_FALSE(bank->transfer(account1, account2, 200.0));
    EXPECT_EQ(account1->getBalance(), 100.0);
    EXPECT_EQ(account2->getBalance(), 500.0);
}

// Transaction history
TEST_F(BankingTest, RecordsTransactionHistory) {
    auto account = bank->createAccount("Olivia", AccountType::CHECKING, 1000.0);
    account->deposit(200.0);
    account->withdraw(150.0);
    
    auto history = account->getTransactionHistory();
    EXPECT_EQ(history.size(), 3); // Initial deposit + 2 transactions
    EXPECT_EQ(history[1].type, TransactionType::DEPOSIT);
    EXPECT_EQ(history[2].type, TransactionType::WITHDRAWAL);
}

TEST_F(BankingTest, CalculatesCorrectTransactionBalances) {
    auto account = bank->createAccount("Paul", AccountType::SAVINGS, 500.0);
    account->deposit(300.0);
    account->withdraw(100.0);
    
    auto history = account->getTransactionHistory();
    EXPECT_EQ(history[0].balance_after, 500.0);
    EXPECT_EQ(history[1].balance_after, 800.0);
    EXPECT_EQ(history[2].balance_after, 700.0);
}

// Account management
TEST_F(BankingTest, FindsAccountById) {
    auto account = bank->createAccount("Quinn", AccountType::CHECKING, 750.0);
    auto found = bank->findAccount(account->getAccountId());
    EXPECT_NE(found, nullptr);
    EXPECT_EQ(found->getOwner(), "Quinn");
}

TEST_F(BankingTest, ReturnsNullForInvalidAccountId) {
    auto found = bank->findAccount(99999);
    EXPECT_EQ(found, nullptr);
}

TEST_F(BankingTest, ClosesAccount) {
    auto account = bank->createAccount("Rachel", AccountType::SAVINGS, 1000.0);
    int accountId = account->getAccountId();
    
    EXPECT_TRUE(bank->closeAccount(accountId));
    EXPECT_EQ(bank->findAccount(accountId), nullptr);
}

TEST_F(BankingTest, CalculatesTotalBankAssets) {
    bank->createAccount("Sam", AccountType::CHECKING, 1000.0);
    bank->createAccount("Tina", AccountType::SAVINGS, 2000.0);
    bank->createAccount("Uma", AccountType::CHECKING, 1500.0);
    
    EXPECT_EQ(bank->getTotalAssets(), 4500.0);
}
