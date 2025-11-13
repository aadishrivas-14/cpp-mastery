# Quantitative Finance Problems - Detailed Guide

## Problem Breakdown by Category

---

## 📊 PROBABILITY & STATISTICS

### 1. Monte Carlo Option Pricing
**Companies:** All quant firms  
**Difficulty:** Medium  
**Concept:** Simulate stock price paths using GBM, calculate payoff

**Formula:**
```
S(T) = S(0) * exp((r - σ²/2)T + σ√T * Z)
Option Price = e^(-rT) * E[max(S(T) - K, 0)]
```

**Interview Questions:**
- How many simulations needed for accuracy?
- What's the convergence rate? (O(1/√n))
- How to reduce variance? (Antithetic variates, control variates)

---

### 2. Value at Risk (VaR)
**Companies:** Banks, risk management roles  
**Difficulty:** Easy  
**Concept:** Maximum loss at given confidence level

**Methods:**
- Historical Simulation (implemented)
- Parametric (assumes normal distribution)
- Monte Carlo

**Interview Questions:**
- VaR limitations? (Doesn't capture tail risk)
- 95% vs 99% VaR?
- How to backtest VaR?

---

### 3. Sharpe Ratio
**Companies:** All firms  
**Difficulty:** Easy  
**Concept:** Risk-adjusted return metric

**Formula:**
```
Sharpe = (E[R] - Rf) / σ(R)
```

**Interview Questions:**
- What's a good Sharpe ratio? (>1 good, >2 excellent)
- Limitations? (Assumes normal returns, symmetric risk)
- Alternatives? (Sortino, Calmar, Information Ratio)

---

### 4. Covariance Matrix
**Companies:** Portfolio management  
**Difficulty:** Medium  
**Concept:** Measure asset correlations

**Formula:**
```
Cov(X,Y) = E[(X - μx)(Y - μy)]
```

**Interview Questions:**
- How to ensure positive definite?
- Shrinkage methods?
- Factor models vs full covariance?

---

### 5. Expected Shortfall (CVaR)
**Companies:** Risk management  
**Difficulty:** Medium  
**Concept:** Expected loss beyond VaR

**Formula:**
```
CVaR = E[Loss | Loss > VaR]
```

**Interview Questions:**
- Why better than VaR? (Coherent risk measure)
- How to optimize for CVaR?
- Computational challenges?

---

## 💰 PRICING & DERIVATIVES

### 6-7. Black-Scholes Call/Put
**Companies:** All derivatives desks  
**Difficulty:** Easy  
**Concept:** Closed-form option pricing

**Assumptions:**
- Constant volatility
- No dividends
- Efficient markets
- Log-normal stock prices

**Interview Questions:**
- Derive the PDE
- Put-call parity
- What happens as T→0?
- Effect of each parameter

---

### 8. Implied Volatility
**Companies:** Options trading  
**Difficulty:** Hard  
**Concept:** Solve for σ given market price

**Method:** Newton-Raphson
```
σ(n+1) = σ(n) - [BS(σ) - Market] / Vega(σ)
```

**Interview Questions:**
- Why is IV important?
- Volatility smile/skew?
- How to handle edge cases?

---

### 9-10. Greeks (Delta, Gamma)
**Companies:** Options market making  
**Difficulty:** Medium  
**Concept:** Option sensitivities

**Delta:**
```
Δ = ∂V/∂S = N(d₁) for calls
```

**Gamma:**
```
Γ = ∂²V/∂S² = N'(d₁) / (S σ √T)
```

**Interview Questions:**
- Delta hedging strategy?
- Gamma scalping?
- When is gamma highest?

---

## 📈 TIME SERIES & MARKET MICROSTRUCTURE

### 11. VWAP
**Companies:** Execution trading  
**Difficulty:** Easy  
**Concept:** Volume-weighted price

**Use Cases:**
- Benchmark for execution
- Detect manipulation
- Fair value estimate

**Interview Questions:**
- VWAP vs TWAP?
- How to beat VWAP?
- Gaming VWAP?

---

### 12. TWAP
**Companies:** Execution algorithms  
**Difficulty:** Easy  
**Concept:** Time-weighted price

**Strategy:** Split order evenly over time

**Interview Questions:**
- When to use TWAP vs VWAP?
- Market impact?
- Optimal slicing?

---

### 13. Exponential Moving Average
**Companies:** Technical trading  
**Difficulty:** Easy  
**Concept:** Weighted average favoring recent prices

**Formula:**
```
EMA(t) = α * Price(t) + (1-α) * EMA(t-1)
α = 2/(N+1)
```

**Interview Questions:**
- EMA vs SMA?
- Lag properties?
- Crossover strategies?

---

### 14. Bollinger Bands
**Companies:** Volatility trading  
**Difficulty:** Medium  
**Concept:** Volatility-based bands

**Formula:**
```
Upper = SMA + k*σ
Lower = SMA - k*σ
```

**Interview Questions:**
- Mean reversion strategy?
- Breakout strategy?
- Optimal k value?

---

### 15. Order Book Imbalance
**Companies:** HFT firms  
**Difficulty:** Medium  
**Concept:** Bid-ask pressure

**Formula:**
```
Imbalance = (BidSize - AskSize) / (BidSize + AskSize)
```

**Interview Questions:**
- Predictive power?
- Time horizon?
- Depth levels to consider?

---

## 🤖 ALGORITHMIC TRADING

### 16. Optimal Execution (Almgren-Chriss)
**Companies:** Execution trading  
**Difficulty:** Hard  
**Concept:** Minimize cost + risk

**Trade-off:**
- Fast execution → High market impact
- Slow execution → High price risk

**Interview Questions:**
- Derive optimal trajectory
- Risk aversion parameter
- Extensions (adaptive, limit orders)

---

### 17. Mean Reversion Signal
**Companies:** Statistical arbitrage  
**Difficulty:** Medium  
**Concept:** Trade deviations from mean

**Strategy:**
- Buy when price < mean
- Sell when price > mean

**Interview Questions:**
- Half-life estimation?
- Ornstein-Uhlenbeck process?
- When does it fail?

---

### 18. Pairs Trading Z-Score
**Companies:** Stat arb desks  
**Difficulty:** Medium  
**Concept:** Relative value trading

**Formula:**
```
Z = (Spread - μ) / σ
```

**Interview Questions:**
- Cointegration vs correlation?
- Entry/exit thresholds?
- Risk management?

---

### 19. Kelly Criterion
**Companies:** Prop trading  
**Difficulty:** Medium  
**Concept:** Optimal bet sizing

**Formula:**
```
f* = (p*b - q) / b
```

**Interview Questions:**
- Full Kelly vs fractional?
- Assumptions?
- Drawdown risk?

---

### 20. Maximum Drawdown
**Companies:** Risk management  
**Difficulty:** Easy  
**Concept:** Peak-to-trough decline

**Use Cases:**
- Strategy evaluation
- Risk limits
- Investor psychology

**Interview Questions:**
- Drawdown duration?
- Recovery time?
- Calmar ratio?

---

## 🔢 NUMERICAL METHODS

### 21. Binomial Tree
**Companies:** Derivatives pricing  
**Difficulty:** Medium  
**Concept:** Discrete-time option pricing

**Advantages:**
- American options
- Dividends
- Path-dependent

**Interview Questions:**
- Convergence to Black-Scholes?
- Number of steps needed?
- Trinomial tree?

---

### 22. Finite Difference PDE
**Companies:** Quant research  
**Difficulty:** Hard  
**Concept:** Solve PDEs numerically

**Methods:**
- Explicit (implemented)
- Implicit (stable)
- Crank-Nicolson (best)

**Interview Questions:**
- Stability conditions?
- Boundary conditions?
- Grid spacing?

---

### 23. Newton-Raphson
**Companies:** All quant roles  
**Difficulty:** Medium  
**Concept:** Root finding

**Formula:**
```
x(n+1) = x(n) - f(x) / f'(x)
```

**Interview Questions:**
- Convergence rate? (Quadratic)
- When does it fail?
- Alternatives? (Bisection, Secant)

---

### 24-25. Interpolation
**Companies:** Yield curve construction  
**Difficulty:** Medium  
**Concept:** Estimate values between points

**Methods:**
- Linear (simple)
- Cubic spline (smooth)
- Polynomial (oscillation)

**Interview Questions:**
- Extrapolation dangers?
- Smoothness requirements?
- Yield curve bootstrapping?

---

## 📊 PORTFOLIO OPTIMIZATION

### 26. Mean-Variance Optimization
**Companies:** Asset management  
**Difficulty:** Hard  
**Concept:** Markowitz framework

**Objective:**
```
min w'Σw
s.t. w'μ = target
     w'1 = 1
```

**Interview Questions:**
- Estimation error?
- Constraints (long-only, turnover)?
- Black-Litterman?

---

### 27. Portfolio Variance
**Companies:** Risk management  
**Difficulty:** Medium  
**Concept:** Total portfolio risk

**Formula:**
```
σ²(p) = w'Σw
```

**Interview Questions:**
- Marginal contribution to risk?
- Risk decomposition?
- Factor models?

---

### 28. Efficient Frontier
**Companies:** Portfolio management  
**Difficulty:** Hard  
**Concept:** Risk-return tradeoff

**Properties:**
- Convex curve
- Tangency portfolio (max Sharpe)
- Two-fund separation

**Interview Questions:**
- Capital Market Line?
- Market portfolio?
- Leverage?

---

### 29. Risk Parity
**Companies:** Alternative investments  
**Difficulty:** Hard  
**Concept:** Equal risk contribution

**Idea:** Each asset contributes equally to portfolio risk

**Interview Questions:**
- vs Equal weight?
- vs Mean-variance?
- Leverage needed?

---

### 30. Maximum Sharpe Ratio
**Companies:** All asset managers  
**Difficulty:** Hard  
**Concept:** Optimal risk-adjusted return

**Solution:** Tangency portfolio on efficient frontier

**Interview Questions:**
- Analytical solution?
- Constraints?
- Robust estimation?

---

## 🎲 PROBABILITY PUZZLES

### 31. Expected Coin Flips
**Companies:** Jane Street, Citadel  
**Difficulty:** Medium  
**Concept:** Geometric series

**Answer:** 2^(n+1) - 2 for n heads

**Interview Questions:**
- Analytical solution?
- Generalize to unfair coin?
- Markov chain approach?

---

### 32. Gambler's Ruin
**Companies:** All quant firms  
**Difficulty:** Medium  
**Concept:** Random walk with barriers

**Formula:**
```
P(win) = (1 - (q/p)^a) / (1 - (q/p)^(a+b))
```

**Interview Questions:**
- Fair game (p=0.5)?
- Expected duration?
- Martingale approach?

---

### 33. Random Walk Return Time
**Companies:** Probability-heavy firms  
**Difficulty:** Hard  
**Concept:** First passage time

**Result:** Infinite expected return time!

**Interview Questions:**
- Why infinite?
- Bounded vs unbounded?
- Recurrence vs transience?

---

### 34. Dice Roll Sum
**Companies:** Brain teaser interviews  
**Difficulty:** Easy  
**Concept:** Convolution of distributions

**Method:** Dynamic programming or simulation

**Interview Questions:**
- Analytical formula?
- Most likely sum?
- Generalize to n dice?

---

### 35. Shuffle Entropy
**Companies:** Randomness testing  
**Difficulty:** Medium  
**Concept:** Measure of disorder

**Metric:** Inversions, runs, cycles

**Interview Questions:**
- Perfect shuffle?
- How many shuffles needed?
- Riffle shuffle analysis?

---

## 🎯 Interview Strategy

1. **Clarify the problem** - Ask about assumptions
2. **Start simple** - Brute force first
3. **Optimize** - Discuss improvements
4. **Edge cases** - Handle special scenarios
5. **Trade-offs** - Discuss alternatives

**Good luck!** 🚀
