#include "bank_account.h"

BankAccount::BankAccount(int id, double balance) : id_(id), balance_(balance) {}

void BankAccount::deposit(double amount) {
  // TODO: Add amount to balance
}

bool BankAccount::withdraw(double amount) {
  // TODO: Check if sufficient funds, then subtract
  // Return false if insufficient funds
  return false;
}

double BankAccount::getBalance() const {
  // TODO: Return current balance
  return 0.0;
}

int BankAccount::getId() const {
  // TODO: Return account ID
  return 0;
}
