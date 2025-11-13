#pragma once
#include <vector>
#include <string>
#include <map>

// BLACK-SCHOLES & GREEKS (10)
double blackScholesCall(double S, double K, double r, double sigma, double T);
double blackScholesPut(double S, double K, double r, double sigma, double T);
double callDelta(double S, double K, double r, double sigma, double T);
double putDelta(double S, double K, double r, double sigma, double T);
double gamma(double S, double K, double r, double sigma, double T);
double vega(double S, double K, double r, double sigma, double T);
double theta(double S, double K, double r, double sigma, double T, bool isCall);
double rho(double S, double K, double r, double sigma, double T, bool isCall);
double impliedVolatility(double marketPrice, double S, double K, double r, double T, bool isCall);
double digitalOption(double S, double K, double r, double sigma, double T, bool isCall);

// MONTE CARLO METHODS (10)
double monteCarloEuropean(double S, double K, double r, double sigma, double T, int sims, bool isCall);
double monteCarloAsian(double S, double K, double r, double sigma, double T, int steps, int sims);
double monteCarloBarrier(double S, double K, double barrier, double r, double sigma, double T, int steps, int sims);
double monteCarloLookback(double S, double K, double r, double sigma, double T, int steps, int sims);
std::vector<double> monteCarloPath(double S, double r, double sigma, double T, int steps);
double varianceReduction(double S, double K, double r, double sigma, double T, int sims);
double quasiMonteCarloSobol(double S, double K, double r, double sigma, double T, int sims);
double importanceSampling(double S, double K, double r, double sigma, double T, int sims);
double controlVariates(double S, double K, double r, double sigma, double T, int sims);
double antitheticVariates(double S, double K, double r, double sigma, double T, int sims);

// BINOMIAL/TRINOMIAL TREES (10)
double binomialEuropean(double S, double K, double r, double sigma, double T, int steps, bool isCall);
double binomialAmerican(double S, double K, double r, double sigma, double T, int steps, bool isCall);
double trinomialTree(double S, double K, double r, double sigma, double T, int steps, bool isCall);
double crrModel(double S, double K, double r, double sigma, double T, int steps);
double jrModel(double S, double K, double r, double sigma, double T, int steps);
double impliedBinomialTree(const std::vector<double>& prices, double S, double T, int steps);
double bermudanOption(double S, double K, double r, double sigma, double T, const std::vector<double>& exerciseTimes, int steps);
double compoundOption(double S, double K1, double K2, double r, double sigma, double T1, double T2, int steps);
double chooserOption(double S, double K, double r, double sigma, double T, double chooseTime, int steps);
double rainbowOption(double S1, double S2, double K, double r, double sigma1, double sigma2, double rho, double T, int steps);

// FINITE DIFFERENCE METHODS (10)
std::vector<double> explicitFDM(double S, double K, double r, double sigma, double T, int sSteps, int tSteps);
std::vector<double> implicitFDM(double S, double K, double r, double sigma, double T, int sSteps, int tSteps);
std::vector<double> crankNicolson(double S, double K, double r, double sigma, double T, int sSteps, int tSteps);
std::vector<double> americanFDM(double S, double K, double r, double sigma, double T, int sSteps, int tSteps, bool isCall);
std::vector<double> barrierFDM(double S, double K, double barrier, double r, double sigma, double T, int sSteps, int tSteps);
std::vector<double> twoFactorFDM(double S, double V, double K, double r, double kappa, double theta, double sigma, double T, int steps);
std::vector<double> jumpDiffusionFDM(double S, double K, double r, double sigma, double lambda, double muJ, double sigmaJ, double T, int steps);
std::vector<double> localVolFDM(double S, double K, double r, const std::vector<std::vector<double>>& localVol, double T, int steps);
std::vector<double> stochasticVolFDM(double S, double V, double K, double r, double kappa, double theta, double sigma, double rho, double T, int steps);
std::vector<double> pdeGreeks(const std::vector<double>& prices, double dS, double dt);

// VOLATILITY MODELS (10)
double historicalVolatility(const std::vector<double>& prices, int window);
double ewmaVolatility(const std::vector<double>& returns, double lambda);
double garchVolatility(const std::vector<double>& returns, double omega, double alpha, double beta);
double impliedVolSurface(const std::vector<double>& strikes, const std::vector<double>& maturities, const std::vector<std::vector<double>>& prices);
double volSmile(double strike, double atm, double skew, double convexity);
double volSkew(const std::vector<double>& strikes, const std::vector<double>& ivs);
double volTermStructure(const std::vector<double>& maturities, const std::vector<double>& vols, double T);
double localVolatility(double S, double T, const std::vector<std::vector<double>>& impliedVols);
double stochasticVolHeston(double S, double V, double r, double kappa, double theta, double sigma, double rho, double T, int steps);
double sabr(double F, double K, double T, double alpha, double beta, double rho, double nu);

// INTEREST RATE MODELS (10)
double vasicekRate(double r0, double a, double b, double sigma, double T, int steps);
double coxIngersollRoss(double r0, double a, double b, double sigma, double T, int steps);
double hullWhite(double r0, double a, double sigma, const std::vector<double>& forwardCurve, double T, int steps);
double blackKarasinski(double r0, double a, double sigma, double T, int steps);
double hjmModel(const std::vector<double>& forwardCurve, const std::vector<std::vector<double>>& vols, double T, int steps);
double liborMarketModel(const std::vector<double>& libors, const std::vector<double>& vols, const std::vector<std::vector<double>>& corr, double T, int steps);
double bondOptionPrice(double F, double K, double sigma, double T);
double swaptionPrice(double swapRate, double K, double sigma, double T, const std::vector<double>& discounts);
double capletPrice(double L, double K, double sigma, double T, double tau);
double floorletPrice(double L, double K, double sigma, double T, double tau);

// EXOTIC OPTIONS (10)
double asianOption(double S, double K, double r, double sigma, double T, int steps, bool isCall);
double barrierOption(double S, double K, double barrier, double r, double sigma, double T, bool isCall, bool isUp, bool isIn);
double lookbackOption(double S, double r, double sigma, double T, bool isCall);
double cliquetOption(double S, double r, double sigma, const std::vector<double>& resetTimes, double localCap, double localFloor);
double basketOption(const std::vector<double>& spots, const std::vector<double>& weights, double K, double r, const std::vector<double>& vols, const std::vector<std::vector<double>>& corr, double T);
double spreadOption(double S1, double S2, double K, double r, double sigma1, double sigma2, double rho, double T);
double quantoOption(double S, double K, double rd, double rf, double sigma, double sigmaFX, double rho, double T);
double varianceSwap(const std::vector<double>& prices, double strikeVar);
double volatilitySwap(const std::vector<double>& prices, double strikeVol);
double corridorOption(double S, double K, double lower, double upper, double r, double sigma, double T, int steps);

// CREDIT DERIVATIVES (10)
double creditDefaultSwap(double notional, double spread, double recovery, double hazardRate, const std::vector<double>& times);
double cdsSpread(double notional, double recovery, double hazardRate, const std::vector<double>& times);
double survivalProbability(double hazardRate, double T);
double defaultProbability(double hazardRate, double T);
double creditVaR(const std::vector<double>& exposures, const std::vector<double>& pds, const std::vector<double>& lgds, double confidence);
double expectedLoss(double exposure, double pd, double lgd);
double unexpectedLoss(double exposure, double pd, double lgd);
double cvaCalculation(const std::vector<double>& exposures, const std::vector<double>& pds, double recovery, const std::vector<double>& discounts);
double dvaCalculation(const std::vector<double>& exposures, const std::vector<double>& pds, double recovery, const std::vector<double>& discounts);
double fvaCalculation(const std::vector<double>& exposures, double fundingSpread, const std::vector<double>& discounts);
