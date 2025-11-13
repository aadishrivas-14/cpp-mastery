#include "../include/problems.h"
#include <gtest/gtest.h>
#include <cmath>

// BASIC STATISTICS TESTS
TEST(Stats, Mean_Simple) {
  EXPECT_NEAR(mean({1,2,3,4,5}), 3.0, 0.01);
}

TEST(Stats, Mean_Decimals) {
  EXPECT_NEAR(mean({1.5, 2.5, 3.5}), 2.5, 0.01);
}

TEST(Stats, Median_Odd) {
  EXPECT_NEAR(median({1,2,3,4,5}), 3.0, 0.01);
}

TEST(Stats, Median_Even) {
  EXPECT_NEAR(median({1,2,3,4}), 2.5, 0.01);
}

TEST(Stats, Variance) {
  EXPECT_NEAR(variance({1,2,3,4,5}), 2.0, 0.01);
}

TEST(Stats, StdDev) {
  EXPECT_NEAR(stddev({1,2,3,4,5}), std::sqrt(2.0), 0.01);
}

TEST(Stats, Covariance_Positive) {
  EXPECT_GT(covariance({1,2,3}, {2,4,6}), 0);
}

TEST(Stats, Correlation_Perfect) {
  EXPECT_NEAR(correlation({1,2,3}, {2,4,6}), 1.0, 0.01);
}

TEST(Stats, Percentile_50) {
  EXPECT_NEAR(percentile({1,2,3,4,5}, 0.5), 3.0, 0.5);
}

TEST(Stats, GeometricMean) {
  EXPECT_NEAR(geometricMean({1,2,4,8}), std::pow(64, 0.25), 0.01);
}

// RETURNS & PERFORMANCE TESTS
TEST(Returns, SimpleReturn_Gain) {
  EXPECT_NEAR(simpleReturn(100, 110), 0.1, 0.01);
}

TEST(Returns, SimpleReturn_Loss) {
  EXPECT_NEAR(simpleReturn(100, 90), -0.1, 0.01);
}

TEST(Returns, LogReturn) {
  EXPECT_NEAR(logReturn(100, 110), std::log(1.1), 0.01);
}

TEST(Returns, CumulativeReturn) {
  EXPECT_NEAR(cumulativeReturn({0.1, 0.2, -0.05}), 0.254, 0.01);
}

TEST(Returns, AnnualizedReturn) {
  EXPECT_NEAR(annualizedReturn(0.21, 2), 0.1, 0.01);
}

TEST(Returns, AnnualizedVolatility) {
  std::vector<double> returns = {0.01, -0.02, 0.03, -0.01};
  EXPECT_GT(annualizedVolatility(returns, 252), 0);
}

TEST(Returns, SharpeRatio_Positive) {
  EXPECT_GT(sharpeRatio({0.01,0.02,0.03}, 0.005), 0);
}

TEST(Returns, SortinoRatio) {
  EXPECT_GT(sortinoRatio({0.01,0.02,-0.01,0.03}, 0.005), 0);
}

TEST(Returns, TreynorRatio) {
  EXPECT_GT(treynorRatio({0.01,0.02,0.03}, 1.2, 0.005), 0);
}

// BASIC PRICING TESTS
TEST(Pricing, PresentValue) {
  EXPECT_NEAR(presentValue(100, 0.05, 1), 95.24, 0.5);
}

TEST(Pricing, FutureValue) {
  EXPECT_NEAR(futureValue(100, 0.05, 1), 105.0, 0.5);
}

TEST(Pricing, DiscountFactor) {
  EXPECT_NEAR(discountFactor(0.05, 1), std::exp(-0.05), 0.01);
}

TEST(Pricing, CompoundInterest_Annual) {
  EXPECT_NEAR(compoundInterest(100, 0.05, 1, 1), 105.0, 0.5);
}

TEST(Pricing, CompoundInterest_Quarterly) {
  EXPECT_NEAR(compoundInterest(100, 0.05, 1, 4), 105.09, 0.5);
}

TEST(Pricing, ContinuousCompounding) {
  EXPECT_NEAR(continuousCompounding(100, 0.05, 1), 100*std::exp(0.05), 0.5);
}

TEST(Pricing, BondPrice) {
  EXPECT_GT(bondPrice(1000, 50, 0.05, 10), 900);
  EXPECT_LT(bondPrice(1000, 50, 0.05, 10), 1100);
}

TEST(Pricing, DurationModified) {
  EXPECT_NEAR(durationModified(5.0, 0.05), 4.76, 0.1);
}

// OPTION BASICS TESTS
TEST(Options, CallPayoff_ITM) {
  EXPECT_EQ(callPayoff(110, 100), 10);
}

TEST(Options, CallPayoff_OTM) {
  EXPECT_EQ(callPayoff(90, 100), 0);
}

TEST(Options, PutPayoff_ITM) {
  EXPECT_EQ(putPayoff(90, 100), 10);
}

TEST(Options, PutPayoff_OTM) {
  EXPECT_EQ(putPayoff(110, 100), 0);
}

TEST(Options, CallIntrinsic) {
  EXPECT_EQ(callIntrinsicValue(110, 100), 10);
}

TEST(Options, PutIntrinsic) {
  EXPECT_EQ(putIntrinsicValue(90, 100), 10);
}

TEST(Options, CallTimeValue) {
  EXPECT_NEAR(callTimeValue(15, 110, 100), 5, 0.01);
}

TEST(Options, PutCallParity) {
  double put = putCallParity(10, 100, 100, 0.05, 1);
  EXPECT_GT(put, 5);
  EXPECT_LT(put, 15);
}

TEST(Options, ForwardPrice) {
  EXPECT_NEAR(forwardPrice(100, 0.05, 1), 100*std::exp(0.05), 0.5);
}

TEST(Options, FuturesPrice) {
  EXPECT_NEAR(futuresPrice(100, 0.05, 0.02, 1), 100*std::exp(0.03), 0.5);
}

TEST(Options, BreakevenCall) {
  EXPECT_EQ(optionBreakeven(100, 5, true), 105);
}

TEST(Options, BreakevenPut) {
  EXPECT_EQ(optionBreakeven(100, 5, false), 95);
}

// PROBABILITY TESTS
TEST(Probability, ExpectedValue) {
  EXPECT_NEAR(expectedValue({1,2,3}, {0.2,0.5,0.3}), 2.1, 0.01);
}

TEST(Probability, ProbabilityAnd) {
  EXPECT_NEAR(probabilityAnd(0.5, 0.4), 0.2, 0.01);
}

TEST(Probability, ProbabilityOr) {
  EXPECT_NEAR(probabilityOr(0.5, 0.4), 0.7, 0.01);
}

TEST(Probability, ConditionalProbability) {
  EXPECT_NEAR(conditionalProbability(0.2, 0.4), 0.5, 0.01);
}

TEST(Probability, BayesTheorem) {
  EXPECT_NEAR(bayesTheorem(0.8, 0.01, 0.1), 0.08, 0.01);
}

TEST(Probability, BinomialProbability) {
  double prob = binomialProbability(10, 5, 0.5);
  EXPECT_GT(prob, 0.2);
  EXPECT_LT(prob, 0.3);
}

TEST(Probability, PoissonProbability) {
  double prob = poissonProbability(3, 2.0);
  EXPECT_GT(prob, 0.15);
  EXPECT_LT(prob, 0.2);
}

TEST(Probability, NormalPDF) {
  double pdf = normalPDF(0, 0, 1);
  EXPECT_NEAR(pdf, 1.0/std::sqrt(2*M_PI), 0.01);
}

TEST(Probability, NormalCDF) {
  EXPECT_NEAR(normalCDF(0, 0, 1), 0.5, 0.01);
}

// PORTFOLIO TESTS
TEST(Portfolio, PortfolioReturn) {
  EXPECT_NEAR(portfolioReturn({0.5,0.5}, {0.1,0.2}), 0.15, 0.01);
}

TEST(Portfolio, PortfolioVolatility) {
  std::vector<std::vector<double>> cov = {{0.04, 0.01}, {0.01, 0.09}};
  double vol = portfolioVolatility({0.5, 0.5}, cov);
  EXPECT_GT(vol, 0.1);
  EXPECT_LT(vol, 0.2);
}

TEST(Portfolio, EqualWeight) {
  EXPECT_NEAR(equalWeight(4), 0.25, 0.01);
}

TEST(Portfolio, MarketCapWeight) {
  EXPECT_NEAR(marketCapWeight(100, 500), 0.2, 0.01);
}

TEST(Portfolio, BetaCoefficient) {
  std::vector<double> asset = {0.01, 0.02, -0.01, 0.03};
  std::vector<double> market = {0.015, 0.025, -0.005, 0.02};
  double beta = betaCoefficient(asset, market);
  EXPECT_GT(beta, 0.5);
  EXPECT_LT(beta, 2.0);
}

TEST(Portfolio, Alpha) {
  EXPECT_NEAR(alpha(0.12, 1.2, 0.10, 0.02), 0.004, 0.01);
}

TEST(Portfolio, ActiveReturn) {
  EXPECT_EQ(activeReturn(0.12, 0.10), 0.02);
}

// TECHNICAL INDICATORS TESTS
TEST(Technical, SMA) {
  EXPECT_NEAR(sma({100,101,102,103,104}, 3), 103.0, 0.01);
}

TEST(Technical, EMA) {
  double ema_val = ema({100,101,102,103,104}, 3);
  EXPECT_GT(ema_val, 100);
  EXPECT_LT(ema_val, 105);
}

TEST(Technical, RSI) {
  std::vector<double> prices = {100,102,101,103,105,104,106};
  double rsi_val = rsi(prices, 5);
  EXPECT_GT(rsi_val, 40);
  EXPECT_LT(rsi_val, 80);
}

TEST(Technical, MACD) {
  std::vector<double> prices(50, 100);
  for (int i = 25; i < 50; ++i) prices[i] = 100 + (i-25);
  double macd_val = macd(prices, 12, 26);
  EXPECT_NE(macd_val, 0);
}

TEST(Technical, BollingerUpper) {
  std::vector<double> prices = {100,101,99,102,98,103,97};
  double upper = bollingerUpper(prices, 5, 2.0);
  EXPECT_GT(upper, 100);
}

TEST(Technical, BollingerLower) {
  std::vector<double> prices = {100,101,99,102,98,103,97};
  double lower = bollingerLower(prices, 5, 2.0);
  EXPECT_LT(lower, 100);
}

TEST(Technical, Stochastic) {
  std::vector<double> prices = {100,102,98,105,103};
  double stoch = stochastic(prices, 5);
  EXPECT_GE(stoch, 0);
  EXPECT_LE(stoch, 100);
}

TEST(Technical, Momentum) {
  std::vector<double> prices = {100,101,102,103,104,105};
  EXPECT_EQ(momentum(prices, 3), 2);
}

TEST(Technical, ROC) {
  std::vector<double> prices = {100,101,102,103,104,105};
  EXPECT_NEAR(roc(prices, 5), 5.0, 0.1);
}

// RISK METRICS TESTS
TEST(Risk, DownsideDeviation) {
  std::vector<double> returns = {0.01, -0.02, 0.03, -0.01, 0.02};
  double dd = downsideDeviation(returns, 0);
  EXPECT_GT(dd, 0);
}

TEST(Risk, SemiVariance) {
  std::vector<double> returns = {0.01, -0.02, 0.03, -0.01, 0.02};
  double sv = semiVariance(returns, 0);
  EXPECT_GT(sv, 0);
}

TEST(Risk, VaR) {
  std::vector<double> returns = {0.01, -0.02, 0.03, -0.01, 0.02, -0.03, 0.01};
  double var = valueAtRisk(returns, 0.95);
  EXPECT_GT(var, 0);
}

TEST(Risk, CVaR) {
  std::vector<double> returns = {0.01, -0.02, 0.03, -0.01, 0.02, -0.03, 0.01};
  double cvar = conditionalVaR(returns, 0.95);
  EXPECT_GT(cvar, 0);
}

TEST(Risk, MaxDrawdown) {
  std::vector<double> prices = {100,110,105,120,90,95};
  double mdd = maxDrawdown(prices);
  EXPECT_NEAR(mdd, 0.25, 0.01); // 25% drawdown from 120 to 90
}

TEST(Risk, AverageDrawdown) {
  std::vector<double> prices = {100,110,105,120,90,95};
  double add = averageDrawdown(prices);
  EXPECT_GT(add, 0);
}

TEST(Risk, UlcerIndex) {
  std::vector<double> prices = {100,110,105,120,90,95};
  double ui = ulcerIndex(prices);
  EXPECT_GT(ui, 0);
}

TEST(Risk, GainLossRatio) {
  std::vector<double> returns = {0.02, -0.01, 0.03, -0.02, 0.01};
  double glr = gainLossRatio(returns);
  EXPECT_GT(glr, 1.5);
}

TEST(Risk, WinRate) {
  std::vector<double> returns = {0.02, -0.01, 0.03, -0.02, 0.01};
  EXPECT_NEAR(winRate(returns), 0.6, 0.01);
}

TEST(Risk, ProfitFactor) {
  std::vector<double> returns = {0.02, -0.01, 0.03, -0.02, 0.01};
  double pf = profitFactor(returns);
  EXPECT_GT(pf, 1.5);
}
