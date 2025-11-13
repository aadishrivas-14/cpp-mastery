#pragma once
#include <vector>
#include <string>
#include <map>
#include <complex>

// ADVANCED STOCHASTIC CALCULUS (10)
double girsanovTransform(const std::vector<double>& path, double drift, double vol);
double feynmanKac(double (*payoff)(double), double S, double r, double sigma, double T, int steps);
double kolmogorovBackward(double S, double K, double r, double sigma, double T);
double fokkerPlanck(const std::vector<double>& density, double drift, double vol, double dt, double dx);
double martingaleTest(const std::vector<double>& path, double drift);
double itoIntegral(const std::vector<double>& integrand, const std::vector<double>& brownian, double dt);
double stratonovichIntegral(const std::vector<double>& integrand, const std::vector<double>& brownian, double dt);
double levyProcess(double alpha, double beta, double scale, double loc, double T, int steps);
double jumpDiffusion(double S, double r, double sigma, double lambda, double muJ, double sigmaJ, double T, int steps);
double fractionalBrownian(double H, double T, int steps);

// CALIBRATION & OPTIMIZATION (10)
std::vector<double> calibrateHeston(const std::vector<double>& marketPrices, const std::vector<double>& strikes, const std::vector<double>& maturities, double S, double r);
std::vector<double> calibrateSABR(const std::vector<double>& marketVols, const std::vector<double>& strikes, double F, double T);
std::vector<double> calibrateLocalVol(const std::vector<std::vector<double>>& impliedVols, const std::vector<double>& strikes, const std::vector<double>& maturities);
std::vector<double> calibrateJumpDiffusion(const std::vector<double>& marketPrices, const std::vector<double>& strikes, double S, double r, double T);
std::vector<double> calibrateCIR(const std::vector<double>& bondPrices, const std::vector<double>& maturities);
double lossFunction(const std::vector<double>& model, const std::vector<double>& market);
std::vector<double> levenbergMarquardt(double (*func)(const std::vector<double>&), const std::vector<double>& initial, double tol);
std::vector<double> geneticAlgorithm(double (*fitness)(const std::vector<double>&), int popSize, int generations);
std::vector<double> simulatedAnnealing(double (*energy)(const std::vector<double>&), const std::vector<double>& initial, double temp);
std::vector<double> particleSwarm(double (*objective)(const std::vector<double>&), int particles, int iterations);

// PORTFOLIO OPTIMIZATION (10)
std::vector<double> meanVarianceOptimization(const std::vector<double>& returns, const std::vector<std::vector<double>>& cov, double targetReturn);
std::vector<double> blackLitterman(const std::vector<double>& marketWeights, const std::vector<std::vector<double>>& cov, const std::vector<double>& views, const std::vector<std::vector<double>>& P, double tau);
std::vector<double> riskParityOptimization(const std::vector<std::vector<double>>& cov);
std::vector<double> maxSharpeOptimization(const std::vector<double>& returns, const std::vector<std::vector<double>>& cov, double rf);
std::vector<double> minVarianceOptimization(const std::vector<std::vector<double>>& cov);
std::vector<double> cvarOptimization(const std::vector<std::vector<double>>& scenarios, double confidence);
std::vector<double> robustOptimization(const std::vector<double>& returns, const std::vector<std::vector<double>>& cov, double uncertainty);
std::vector<double> factorModelOptimization(const std::vector<std::vector<double>>& factorLoadings, const std::vector<double>& factorReturns, const std::vector<double>& specificRisks);
std::vector<double> transactionCostOptimization(const std::vector<double>& currentWeights, const std::vector<double>& targetWeights, double tcost);
std::vector<double> dynamicProgrammingPortfolio(const std::vector<std::vector<double>>& returns, int periods, double gamma);

// MACHINE LEARNING FOR FINANCE (10)
std::vector<double> linearRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& y);
std::vector<double> ridgeRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& y, double lambda);
std::vector<double> lassoRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& y, double lambda);
std::vector<double> logisticRegression(const std::vector<std::vector<double>>& X, const std::vector<double>& y);
std::vector<double> neuralNetwork(const std::vector<std::vector<double>>& X, const std::vector<double>& y, const std::vector<int>& layers);
std::vector<double> randomForest(const std::vector<std::vector<double>>& X, const std::vector<double>& y, int trees);
std::vector<double> gradientBoosting(const std::vector<std::vector<double>>& X, const std::vector<double>& y, int iterations);
std::vector<double> svm(const std::vector<std::vector<double>>& X, const std::vector<double>& y, double C);
std::vector<double> pca(const std::vector<std::vector<double>>& data, int components);
std::vector<int> kmeans(const std::vector<std::vector<double>>& data, int k);

// HIGH-FREQUENCY TRADING (10)
double micropriceEstimate(const std::vector<double>& bidPrices, const std::vector<double>& bidSizes, const std::vector<double>& askPrices, const std::vector<double>& askSizes);
double orderFlowImbalance(const std::vector<double>& buyVolume, const std::vector<double>& sellVolume, int window);
double vpin(const std::vector<double>& buyVolume, const std::vector<double>& sellVolume, int buckets);
double kyleModel(double sigma, double lambda, int N);
double almgrenChriss(double X, int T, double sigma, double eta, double gamma);
double obizhaeva_wang(double X, int T, double sigma, double rho, double eta);
double marketImpact(double volume, double adv, double volatility);
double implementationShortfall(const std::vector<double>& executionPrices, double arrivalPrice, double volume);
double twapExecution(double totalVolume, int periods);
double vwapExecution(const std::vector<double>& volumes, double totalVolume);
