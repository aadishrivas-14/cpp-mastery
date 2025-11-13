#include "../include/problems.h"
#include <gtest/gtest.h>

TEST(BlackScholes, Call) { EXPECT_GT(blackScholesCall(100,100,0.05,0.2,1), 5); }
TEST(BlackScholes, Put) { EXPECT_GT(blackScholesPut(100,100,0.05,0.2,1), 3); }
TEST(Greeks, Delta) { EXPECT_GT(callDelta(100,100,0.05,0.2,1), 0.4); }
TEST(Greeks, Gamma) { EXPECT_GT(gamma(100,100,0.05,0.2,1), 0); }
TEST(Greeks, Vega) { EXPECT_GT(vega(100,100,0.05,0.2,1), 0); }
TEST(MonteCarlo, European) { EXPECT_GT(monteCarloEuropean(100,100,0.05,0.2,1,1000,true), 5); }
TEST(Volatility, Historical) { EXPECT_GT(historicalVolatility({100,101,99,102,98}, 5), 0); }
TEST(InterestRate, Vasicek) { EXPECT_GT(vasicekRate(0.05,0.1,0.05,0.01,1,100), 0); }
TEST(Exotic, Asian) { EXPECT_GT(asianOption(100,100,0.05,0.2,1,10,true), 0); }
TEST(Credit, Survival) { EXPECT_LT(survivalProbability(0.01,1), 1); }
