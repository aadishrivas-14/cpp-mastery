#include "../include/problems.h"
#include <gtest/gtest.h>

TEST(Stochastic, Girsanov) { EXPECT_NE(girsanovTransform({1,2,3}, 0.05, 0.2), 0); }
TEST(Calibration, Heston) { auto params = calibrateHeston({10,12}, {100,110}, {1,2}, 100, 0.05); EXPECT_EQ(params.size(), 5); }
TEST(Portfolio, MeanVariance) { auto w = meanVarianceOptimization({0.1,0.12}, {{0.04,0.01},{0.01,0.05}}, 0.11); EXPECT_EQ(w.size(), 2); }
TEST(ML, LinearRegression) { auto coef = linearRegression({{1,2},{2,3},{3,4}}, {3,5,7}); EXPECT_GT(coef.size(), 0); }
TEST(HFT, Microprice) { EXPECT_GT(micropriceEstimate({99.9,99.8}, {100,200}, {100.1,100.2}, {150,250}), 99); }
