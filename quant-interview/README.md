# Quantitative Finance Interview Problems - 200+ Questions (TDD Mode)

Complete hands-on learning: **YOU implement all 200 functions** based on test cases!

## 📊 Status: 200 Functions Ready for Implementation

- 🔥 **Easy:** 70 functions (74 tests) - Foundation & Fundamentals
- 🚀 **Medium:** 80 functions (10 tests) - Advanced Pricing & Models
- 💎 **Hard:** 50 functions (5 tests) - Research & Cutting Edge

**All functions are TODO stubs - no pre-made solutions!**

---

## 🎯 Quick Start

```bash
# Start with Easy
cd quant-interview/easy
cat tests/test_easy_problems.cpp  # Read requirements
vim src/problems.cpp              # Implement functions
cd build && cmake .. && make      # Build
./test_easy_problems              # Test all
./test_easy_problems --gtest_filter="Stats.Mean*"  # Test one
```

---

## 📁 Structure

```
quant-interview/
├── easy/                    # 70 functions - Foundation
│   ├── include/problems.h
│   ├── src/problems.cpp     # ← YOU IMPLEMENT HERE
│   ├── tests/test_easy_problems.cpp
│   ├── CMakeLists.txt
│   └── build/
├── medium/                  # 80 functions - Core Models
│   ├── include/problems.h
│   ├── src/problems.cpp     # ← YOU IMPLEMENT HERE
│   ├── tests/test_medium_problems.cpp
│   ├── CMakeLists.txt
│   └── build/
├── hard/                    # 50 functions - Advanced
│   ├── include/problems.h
│   ├── src/problems.cpp     # ← YOU IMPLEMENT HERE
│   ├── tests/test_hard_problems.cpp
│   ├── CMakeLists.txt
│   └── build/
├── README.md
├── TDD_WORKFLOW.md          # Detailed guide
└── PROBLEMS_GUIDE.md        # Problem descriptions
```

---

## 🔥 EASY PROBLEMS (70 functions)

### Basic Statistics (10)
mean, median, variance, stddev, covariance, correlation, percentile, skewness, kurtosis, geometricMean

### Returns & Performance (10)
simpleReturn, logReturn, cumulativeReturn, annualizedReturn, annualizedVolatility, sharpeRatio, sortinoRatio, calmarRatio, informationRatio, treynorRatio

### Basic Pricing (10)
presentValue, futureValue, discountFactor, compoundInterest, continuousCompounding, bondPrice, bondYield, durationMacaulay, durationModified, convexity

### Option Basics (10)
callPayoff, putPayoff, callIntrinsicValue, putIntrinsicValue, callTimeValue, putCallParity, forwardPrice, futuresPrice, optionBreakeven, maxLoss

### Probability Basics (10)
expectedValue, probabilityAnd, probabilityOr, conditionalProbability, bayesTheorem, binomialProbability, poissonProbability, normalPDF, normalCDF, lognormalPDF

### Portfolio Basics (10)
portfolioReturn, portfolioVolatility, equalWeight, marketCapWeight, betaCoefficient, alpha, trackingError, activeReturn, rSquared, systematicRisk

### Technical Indicators (10)
sma, ema, rsi, macd, bollingerUpper, bollingerLower, atr, stochastic, momentum, roc

### Risk Metrics (10)
downsideDeviation, semiVariance, valueAtRisk, conditionalVaR, maxDrawdown, averageDrawdown, ulcerIndex, gainLossRatio, winRate, profitFactor

---

## 🚀 MEDIUM PROBLEMS (80 functions)

### Black-Scholes & Greeks (10)
blackScholesCall, blackScholesPut, callDelta, putDelta, gamma, vega, theta, rho, impliedVolatility, digitalOption

### Monte Carlo Methods (10)
monteCarloEuropean, monteCarloAsian, monteCarloBarrier, monteCarloLookback, monteCarloPath, varianceReduction, quasiMonteCarloSobol, importanceSampling, controlVariates, antitheticVariates

### Binomial/Trinomial Trees (10)
binomialEuropean, binomialAmerican, trinomialTree, crrModel, jrModel, impliedBinomialTree, bermudanOption, compoundOption, chooserOption, rainbowOption

### Finite Difference Methods (10)
explicitFDM, implicitFDM, crankNicolson, americanFDM, barrierFDM, twoFactorFDM, jumpDiffusionFDM, localVolFDM, stochasticVolFDM, pdeGreeks

### Volatility Models (10)
historicalVolatility, ewmaVolatility, garchVolatility, impliedVolSurface, volSmile, volSkew, volTermStructure, localVolatility, stochasticVolHeston, sabr

### Interest Rate Models (10)
vasicekRate, coxIngersollRoss, hullWhite, blackKarasinski, hjmModel, liborMarketModel, bondOptionPrice, swaptionPrice, capletPrice, floorletPrice

### Exotic Options (10)
asianOption, barrierOption, lookbackOption, cliquetOption, basketOption, spreadOption, quantoOption, varianceSwap, volatilitySwap, corridorOption

### Credit Derivatives (10)
creditDefaultSwap, cdsSpread, survivalProbability, defaultProbability, creditVaR, expectedLoss, unexpectedLoss, cvaCalculation, dvaCalculation, fvaCalculation

---

## 💎 HARD PROBLEMS (50 functions)

### Advanced Stochastic Calculus (10)
girsanovTransform, feynmanKac, kolmogorovBackward, fokkerPlanck, martingaleTest, itoIntegral, stratonovichIntegral, levyProcess, jumpDiffusion, fractionalBrownian

### Calibration & Optimization (10)
calibrateHeston, calibrateSABR, calibrateLocalVol, calibrateJumpDiffusion, calibrateCIR, lossFunction, levenbergMarquardt, geneticAlgorithm, simulatedAnnealing, particleSwarm

### Portfolio Optimization (10)
meanVarianceOptimization, blackLitterman, riskParityOptimization, maxSharpeOptimization, minVarianceOptimization, cvarOptimization, robustOptimization, factorModelOptimization, transactionCostOptimization, dynamicProgrammingPortfolio

### Machine Learning for Finance (10)
linearRegression, ridgeRegression, lassoRegression, logisticRegression, neuralNetwork, randomForest, gradientBoosting, svm, pca, kmeans

### High-Frequency Trading (10)
micropriceEstimate, orderFlowImbalance, vpin, kyleModel, almgrenChriss, obizhaeva_wang, marketImpact, implementationShortfall, twapExecution, vwapExecution

---

## 💼 Target Companies

**HFT:** Jane Street, Citadel Securities, Jump Trading, Tower Research, Hudson River Trading  
**Banks:** Goldman Sachs, Morgan Stanley, JP Morgan, Barclays, Deutsche Bank  
**Prop Trading:** Optiver, IMC, SIG, DRW, Five Rings  
**Hedge Funds:** Two Sigma, DE Shaw, Renaissance Technologies, Millennium

---

## 📖 How TDD Works

### 1. Read Test Cases
```cpp
TEST(Stats, Mean_Simple) {
  EXPECT_NEAR(mean({1,2,3,4,5}), 3.0, 0.01);
}
```

### 2. Check TODO Stub
```cpp
double mean(const std::vector<double>& data) {
  // TODO: Calculate arithmetic mean
  // Hint: Sum all elements and divide by count
  return 0.0;  // ← Replace this!
}
```

### 3. Implement
```cpp
double mean(const std::vector<double>& data) {
  double sum = 0;
  for (double x : data) sum += x;
  return sum / data.size();
}
```

### 4. Test
```bash
./test_easy_problems --gtest_filter="Stats.Mean*"
# [  PASSED  ] 2 tests. ✅
```

---

## 🎓 Learning Path

### Week 1-2: Easy (Foundation)
- Basic statistics and probability
- Returns and performance metrics
- Simple pricing and options
- Portfolio basics
- Technical indicators
- Risk metrics

**Goal:** 74/74 tests passing

### Week 3-5: Medium (Core Models)
- Black-Scholes and Greeks
- Monte Carlo simulation
- Tree methods
- Finite difference methods
- Volatility modeling
- Interest rate models
- Exotic options
- Credit derivatives

**Goal:** 10/10 tests passing

### Week 6-8: Hard (Advanced)
- Stochastic calculus
- Model calibration
- Portfolio optimization
- Machine learning
- High-frequency trading

**Goal:** 5/5 tests passing

---

## 🏆 Completion Criteria

### Easy Complete When:
- ✅ All 74 tests passing
- ✅ Understand mathematical concepts
- ✅ Can explain each formula

### Medium Complete When:
- ✅ All 10 tests passing
- ✅ Understand derivatives pricing
- ✅ Can implement numerical methods

### Hard Complete When:
- ✅ All 5 tests passing
- ✅ Understand advanced models
- ✅ Ready for quant researcher roles

---

## 📚 Resources

### Read First
- **TDD_WORKFLOW.md** - Detailed TDD guide
- **PROBLEMS_GUIDE.md** - Problem descriptions
- **Test files** - Specifications for each function

### Books
- **Hull** - Options, Futures, and Other Derivatives
- **Shreve** - Stochastic Calculus for Finance
- **Wilmott** - Paul Wilmott on Quantitative Finance
- **Crack** - Heard on the Street

---

## 💡 Tips

1. **Start with Easy** - Build foundation first
2. **Read tests first** - They tell you what to implement
3. **Use hints** - Every TODO has formula hints
4. **Test incrementally** - One function at a time
5. **Understand the math** - Don't just code, learn why

---

## 🎯 Interview Readiness

After completing all 200 problems:

✅ **Quant Trader** - Market making, execution, pricing  
✅ **Quant Researcher** - Model development, backtesting  
✅ **Quantitative Developer** - Pricing libraries, systems  
✅ **Risk Manager** - VaR, stress testing, limits  
✅ **Portfolio Manager** - Optimization, allocation  

---

## 🚀 Get Started

```bash
cd quant-interview/easy
cat TDD_WORKFLOW.md  # Read the guide
vim src/problems.cpp # Start implementing!
```

**Good luck! Start with `mean()` and work your way through all 200 functions!** 💪📈
