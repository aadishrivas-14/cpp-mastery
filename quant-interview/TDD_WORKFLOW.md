# Quant Interview - Test-Driven Development Workflow

## 🎯 Overview

This is a **hands-on, TDD-based** quant interview preparation where YOU implement all functions based on test cases. No pre-made solutions - you learn by doing!

---

## 📚 How It Works

### 1. Read the Test Cases
Each test file contains comprehensive test cases that specify:
- **Input:** What parameters the function receives
- **Expected Output:** What the function should return
- **Edge Cases:** Special scenarios to handle

### 2. Implement the Function
Open the corresponding `.cpp` file and implement the function to pass the tests.

### 3. Run Tests
Build and run tests to see which ones pass/fail.

### 4. Iterate
Fix failing tests until all pass.

---

## 🚀 Getting Started

### Easy Problems (70 functions)

```bash
cd quant-interview/easy

# 1. Read the test file to understand requirements
cat tests/test_easy_problems.cpp

# 2. Implement functions in src/problems.cpp
vim src/problems.cpp

# 3. Build and test
mkdir -p build && cd build
cmake ..
make

# 4. Run all tests
./test_easy_problems

# 5. Run specific test
./test_easy_problems --gtest_filter="Stats.Mean*"
```

---

## 📖 Example Workflow

### Step 1: Read Test Case

```cpp
TEST(Stats, Mean_Simple) {
  EXPECT_NEAR(mean({1,2,3,4,5}), 3.0, 0.01);
}

TEST(Stats, Mean_Decimals) {
  EXPECT_NEAR(mean({1.5, 2.5, 3.5}), 2.5, 0.01);
}
```

**What you learn:**
- Function name: `mean`
- Input: `std::vector<double>`
- Output: `double`
- Logic: Calculate arithmetic mean
- Test cases: integers and decimals

### Step 2: Check Function Signature

```cpp
// In include/problems.h
double mean(const std::vector<double>& data);
```

### Step 3: Implement

```cpp
// In src/problems.cpp
double mean(const std::vector<double>& data) {
  // TODO: Calculate arithmetic mean
  // Hint: Sum all elements and divide by count
  
  // YOUR IMPLEMENTATION HERE
  double sum = 0;
  for (double x : data) {
    sum += x;
  }
  return sum / data.size();
}
```

### Step 4: Test

```bash
cd build
make
./test_easy_problems --gtest_filter="Stats.Mean*"
```

**Output:**
```
[==========] Running 2 tests from 1 test suite.
[----------] 2 tests from Stats
[ RUN      ] Stats.Mean_Simple
[       OK ] Stats.Mean_Simple (0 ms)
[ RUN      ] Stats.Mean_Decimals
[       OK ] Stats.Mean_Decimals (0 ms)
[----------] 2 tests from Stats (0 ms total)

[==========] 2 tests from 1 test suite ran. (0 ms total)
[  PASSED  ] 2 tests.
```

---

## 📊 Problem Categories

### EASY (70 problems)

#### Basic Statistics (10)
- `mean` - Arithmetic mean
- `median` - Middle value
- `variance` - Measure of spread
- `stddev` - Standard deviation
- `covariance` - Joint variability
- `correlation` - Linear relationship
- `percentile` - Value at percentile
- `skewness` - Asymmetry measure
- `kurtosis` - Tail heaviness
- `geometricMean` - Multiplicative average

#### Returns & Performance (10)
- `simpleReturn` - (end - start) / start
- `logReturn` - ln(end / start)
- `cumulativeReturn` - Compound returns
- `annualizedReturn` - Scale to annual
- `annualizedVolatility` - Scale volatility
- `sharpeRatio` - Risk-adjusted return
- `sortinoRatio` - Downside risk adjusted
- `calmarRatio` - Return / max drawdown
- `informationRatio` - Active return / tracking error
- `treynorRatio` - Return / beta

#### Basic Pricing (10)
- `presentValue` - Discount future value
- `futureValue` - Compound present value
- `discountFactor` - e^(-rt)
- `compoundInterest` - Discrete compounding
- `continuousCompounding` - Continuous compounding
- `bondPrice` - PV of cashflows
- `bondYield` - IRR of bond
- `durationMacaulay` - Weighted time to cashflows
- `durationModified` - Price sensitivity
- `convexity` - Second-order sensitivity

#### Option Basics (10)
- `callPayoff` - max(S-K, 0)
- `putPayoff` - max(K-S, 0)
- `callIntrinsicValue` - In-the-money value
- `putIntrinsicValue` - In-the-money value
- `callTimeValue` - Price - intrinsic
- `putCallParity` - C - S + Ke^(-rt) = P
- `forwardPrice` - Se^(rt)
- `futuresPrice` - Se^((r-q)t)
- `optionBreakeven` - Strike ± premium
- `maxLoss` - Maximum loss calculation

#### Probability Basics (10)
- `expectedValue` - Σ(x * p)
- `probabilityAnd` - P(A ∩ B)
- `probabilityOr` - P(A ∪ B)
- `conditionalProbability` - P(A|B)
- `bayesTheorem` - P(A|B) from P(B|A)
- `binomialProbability` - Discrete distribution
- `poissonProbability` - Event rate distribution
- `normalPDF` - Gaussian density
- `normalCDF` - Gaussian cumulative
- `lognormalPDF` - Lognormal density

#### Portfolio Basics (10)
- `portfolioReturn` - Weighted return
- `portfolioVolatility` - sqrt(w'Σw)
- `equalWeight` - 1/n
- `marketCapWeight` - Cap / total cap
- `betaCoefficient` - Cov(asset, market) / Var(market)
- `alpha` - Excess return
- `trackingError` - Stddev of active return
- `activeReturn` - Portfolio - benchmark
- `rSquared` - Correlation squared
- `systematicRisk` - Beta * market vol

#### Technical Indicators (10)
- `sma` - Simple moving average
- `ema` - Exponential moving average
- `rsi` - Relative strength index
- `macd` - Moving average convergence divergence
- `bollingerUpper` - SMA + k*σ
- `bollingerLower` - SMA - k*σ
- `atr` - Average true range
- `stochastic` - %K oscillator
- `momentum` - Price change
- `roc` - Rate of change

#### Risk Metrics (10)
- `downsideDeviation` - Downside volatility
- `semiVariance` - Downside variance
- `valueAtRisk` - Maximum loss at confidence
- `conditionalVaR` - Expected shortfall
- `maxDrawdown` - Peak to trough
- `averageDrawdown` - Average of drawdowns
- `ulcerIndex` - Drawdown severity
- `gainLossRatio` - Gains / losses
- `winRate` - % winning trades
- `profitFactor` - Gross profit / gross loss

---

## 🎓 Learning Path

### Week 1: Statistics & Returns (20 problems)
**Focus:** Foundation of quantitative analysis

**Day 1-2:** Basic Statistics
- Implement mean, median, variance, stddev
- Understand covariance and correlation
- Learn percentile calculations

**Day 3-4:** Returns & Performance
- Simple vs log returns
- Annualization techniques
- Risk-adjusted metrics (Sharpe, Sortino)

**Day 5:** Review & Practice
- Implement all 20 functions
- Ensure all tests pass
- Understand mathematical derivations

### Week 2: Pricing & Options (20 problems)
**Focus:** Time value of money and derivatives

**Day 1-2:** Basic Pricing
- Present and future value
- Bond pricing and yield
- Duration and convexity

**Day 3-4:** Option Basics
- Payoff diagrams
- Put-call parity
- Forward and futures pricing

**Day 5:** Review & Practice

### Week 3: Probability & Portfolio (20 problems)
**Focus:** Probability theory and portfolio construction

**Day 1-2:** Probability
- Distributions (binomial, Poisson, normal)
- Bayes theorem
- Expected value

**Day 3-4:** Portfolio Theory
- Portfolio return and risk
- Beta and alpha
- Tracking error

**Day 5:** Review & Practice

### Week 4: Technical & Risk (20 problems)
**Focus:** Trading indicators and risk management

**Day 1-2:** Technical Indicators
- Moving averages
- Oscillators (RSI, Stochastic)
- Bollinger Bands

**Day 3-4:** Risk Metrics
- VaR and CVaR
- Drawdown analysis
- Performance ratios

**Day 5:** Review & Practice

---

## 💡 Tips for Success

### 1. Read Tests First
Always start by reading the test cases. They tell you:
- What the function should do
- What inputs to expect
- What outputs to return
- Edge cases to handle

### 2. Start Simple
Don't optimize prematurely. Get it working first:
```cpp
// First: Make it work
double mean(const std::vector<double>& data) {
  double sum = 0;
  for (double x : data) sum += x;
  return sum / data.size();
}

// Later: Make it elegant (if needed)
double mean(const std::vector<double>& data) {
  return std::accumulate(data.begin(), data.end(), 0.0) / data.size();
}
```

### 3. Use Hints
Each TODO has hints about the formula or approach:
```cpp
double variance(const std::vector<double>& data) {
  // TODO: Calculate variance
  // Hint: variance = average of squared deviations from mean
  
  // Hint tells you: Var(X) = E[(X - μ)²]
}
```

### 4. Test Incrementally
Don't implement everything at once:
```bash
# Test one function
./test_easy_problems --gtest_filter="Stats.Mean*"

# Test one category
./test_easy_problems --gtest_filter="Stats.*"

# Test all
./test_easy_problems
```

### 5. Understand the Math
Don't just code - understand WHY:
- **Sharpe Ratio:** Why divide by stddev? (Risk adjustment)
- **Log Returns:** Why use ln? (Additive property)
- **Beta:** Why covariance / variance? (Regression coefficient)

### 6. Check Edge Cases
Tests include edge cases:
```cpp
TEST(Stats, Median_Even) {
  EXPECT_NEAR(median({1,2,3,4}), 2.5, 0.01);  // Average of middle two
}
```

---

## 🔍 Debugging Tips

### Test Fails?

1. **Read the error message:**
```
Expected: 3.0
Actual: 0.0
```

2. **Check your implementation:**
```cpp
double mean(const std::vector<double>& data) {
  return 0.0;  // ← Still has TODO stub!
}
```

3. **Add debug prints:**
```cpp
double mean(const std::vector<double>& data) {
  double sum = 0;
  for (double x : data) {
    sum += x;
    std::cout << "x=" << x << ", sum=" << sum << std::endl;
  }
  return sum / data.size();
}
```

4. **Run single test:**
```bash
./test_easy_problems --gtest_filter="Stats.Mean_Simple"
```

---

## 📈 Progress Tracking

### Check Your Progress

```bash
# See how many tests pass
./test_easy_problems 2>&1 | grep "PASSED"

# Example output:
# [  PASSED  ] 45 tests.
# Progress: 45/120 tests (37.5%)
```

### Track by Category

```bash
# Statistics
./test_easy_problems --gtest_filter="Stats.*" 2>&1 | grep "PASSED"

# Returns
./test_easy_problems --gtest_filter="Returns.*" 2>&1 | grep "PASSED"

# Pricing
./test_easy_problems --gtest_filter="Pricing.*" 2>&1 | grep "PASSED"
```

---

## 🏆 Completion Criteria

### Easy Level Complete When:
- ✅ All 120 tests passing
- ✅ Understand mathematical concepts
- ✅ Can explain each formula
- ✅ Ready for Medium problems

### Move to Medium When:
- You can implement any Easy function from scratch
- You understand the financial concepts
- You're comfortable with C++ STL
- Tests pass consistently

---

## 📚 Resources

### Mathematical Finance
- **Hull** - Options, Futures, and Other Derivatives
- **Shreve** - Stochastic Calculus for Finance

### Probability & Statistics
- **Ross** - A First Course in Probability
- **Casella & Berger** - Statistical Inference

### C++ Programming
- **Stroustrup** - The C++ Programming Language
- **Meyers** - Effective Modern C++

---

## 🎯 Interview Preparation

After completing Easy problems, you'll be ready to:
- ✅ Answer basic quant interview questions
- ✅ Implement financial calculations
- ✅ Explain risk metrics
- ✅ Discuss portfolio theory
- ✅ Code technical indicators

**Next:** Move to Medium problems for derivatives pricing, Monte Carlo, and advanced models!

---

## 💪 Challenge Yourself

### Time Yourself
- Easy problems: 5-10 min each
- Can you implement `mean` in 2 minutes?
- Can you implement `sharpeRatio` in 5 minutes?

### No Hints Mode
- Comment out the hints
- Implement from test cases only
- Check your understanding

### Optimize
- After passing tests, optimize for speed
- Use STL algorithms
- Minimize allocations

---

**Good luck! Start with `mean()` and work your way through all 70 functions!** 🚀
