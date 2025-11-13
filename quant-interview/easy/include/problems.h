#pragma once
#include <vector>
#include <string>

// BASIC STATISTICS (10)
double mean(const std::vector<double>& data);
double median(std::vector<double> data);
double variance(const std::vector<double>& data);
double stddev(const std::vector<double>& data);
double covariance(const std::vector<double>& x, const std::vector<double>& y);
double correlation(const std::vector<double>& x, const std::vector<double>& y);
double percentile(std::vector<double> data, double p);
double skewness(const std::vector<double>& data);
double kurtosis(const std::vector<double>& data);
double geometricMean(const std::vector<double>& data);

// RETURNS & PERFORMANCE (10)
double simpleReturn(double start, double end);
double logReturn(double start, double end);
double cumulativeReturn(const std::vector<double>& returns);
double annualizedReturn(double totalReturn, double years);
double annualizedVolatility(const std::vector<double>& returns, int periodsPerYear);
double sharpeRatio(const std::vector<double>& returns, double rf);
double sortinoRatio(const std::vector<double>& returns, double rf);
double calmarRatio(const std::vector<double>& prices);
double informationRatio(const std::vector<double>& returns, const std::vector<double>& benchmark);
double treynorRatio(const std::vector<double>& returns, double beta, double rf);

// BASIC PRICING (10)
double presentValue(double futureValue, double rate, double time);
double futureValue(double presentValue, double rate, double time);
double discountFactor(double rate, double time);
double compoundInterest(double principal, double rate, double time, int n);
double continuousCompounding(double principal, double rate, double time);
double bondPrice(double faceValue, double coupon, double rate, int periods);
double bondYield(double price, double faceValue, double coupon, int periods);
double durationMacaulay(const std::vector<double>& cashflows, const std::vector<double>& times, double yield);
double durationModified(double macaulayDuration, double yield);
double convexity(const std::vector<double>& cashflows, const std::vector<double>& times, double yield);

// OPTION BASICS (10)
double callPayoff(double spot, double strike);
double putPayoff(double spot, double strike);
double callIntrinsicValue(double spot, double strike);
double putIntrinsicValue(double spot, double strike);
double callTimeValue(double optionPrice, double spot, double strike);
double putCallParity(double call, double spot, double strike, double rate, double time);
double forwardPrice(double spot, double rate, double time);
double futuresPrice(double spot, double rate, double dividend, double time);
double optionBreakeven(double strike, double premium, bool isCall);
double maxLoss(double strike, double premium, bool isCall, bool isLong);

// PROBABILITY BASICS (10)
double expectedValue(const std::vector<double>& values, const std::vector<double>& probs);
double probabilityAnd(double p1, double p2);
double probabilityOr(double p1, double p2);
double conditionalProbability(double pAandB, double pB);
double bayesTheorem(double pBA, double pA, double pB);
double binomialProbability(int n, int k, double p);
double poissonProbability(int k, double lambda);
double normalPDF(double x, double mu, double sigma);
double normalCDF(double x, double mu, double sigma);
double lognormalPDF(double x, double mu, double sigma);

// PORTFOLIO BASICS (10)
double portfolioReturn(const std::vector<double>& weights, const std::vector<double>& returns);
double portfolioVolatility(const std::vector<double>& weights, const std::vector<std::vector<double>>& cov);
double equalWeight(int n);
double marketCapWeight(double marketCap, double totalMarketCap);
double betaCoefficient(const std::vector<double>& asset, const std::vector<double>& market);
double alpha(double assetReturn, double beta, double marketReturn, double rf);
double trackingError(const std::vector<double>& portfolio, const std::vector<double>& benchmark);
double activeReturn(double portfolioReturn, double benchmarkReturn);
double rSquared(const std::vector<double>& asset, const std::vector<double>& market);
double systematicRisk(double beta, double marketVol);

// TECHNICAL INDICATORS (10)
double sma(const std::vector<double>& prices, int period);
double ema(const std::vector<double>& prices, int period);
double rsi(const std::vector<double>& prices, int period);
double macd(const std::vector<double>& prices, int fast, int slow);
double bollingerUpper(const std::vector<double>& prices, int period, double k);
double bollingerLower(const std::vector<double>& prices, int period, double k);
double atr(const std::vector<double>& high, const std::vector<double>& low, const std::vector<double>& close, int period);
double stochastic(const std::vector<double>& prices, int period);
double momentum(const std::vector<double>& prices, int period);
double roc(const std::vector<double>& prices, int period);

// RISK METRICS (10)
double downsideDeviation(const std::vector<double>& returns, double threshold);
double semiVariance(const std::vector<double>& returns, double threshold);
double valueAtRisk(const std::vector<double>& returns, double confidence);
double conditionalVaR(const std::vector<double>& returns, double confidence);
double maxDrawdown(const std::vector<double>& prices);
double averageDrawdown(const std::vector<double>& prices);
double ulcerIndex(const std::vector<double>& prices);
double gainLossRatio(const std::vector<double>& returns);
double winRate(const std::vector<double>& returns);
double profitFactor(const std::vector<double>& returns);
