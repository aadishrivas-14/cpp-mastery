#pragma once

#include <string>
#include <map>

/**
 * TODO: Implement a Simple Trading Engine
 * 
 * Requirements:
 * - Order struct: id, symbol, type (BUY/SELL), price, quantity
 * - OrderBook class: manages orders
 * - TradingEngine class: processes orders, matches trades
 * 
 * Features:
 * - Submit order
 * - Cancel order
 * - Match orders (simple price-time priority)
 * - Get order book state
 */

enum class OrderType { BUY, SELL };

struct Order {
  int id;
  std::string symbol;
  OrderType type;
  double price;
  int quantity;
};

// TODO: Implement OrderBook and TradingEngine classes
