#pragma once

/**
 * TODO: Implement Banking System (OOP Design)
 * 
 * Requirements:
 * - Constructor: BankAccount(id, initial_balance)
 * - deposit(amount) - Add money to balance
 * - withdraw(amount) - Remove money, return false if insufficient funds
 * - getBalance() - Return current balance
 * - getId() - Return account ID
 * 
 * Business rules:
 * - Cannot withdraw more than balance
 * - Balance should never be negative
 */

class BankAccount {
 public:
  BankAccount(int id, double balance);
  void deposit(double amount);
  bool withdraw(double amount);
  double getBalance() const;
  int getId() const;
 private:
  int id_;
  double balance_;
};
