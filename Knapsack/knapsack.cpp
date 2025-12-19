#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

int knapsackDP(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    int n = weights.size();
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int w = 0; w <= capacity; ++w) {
            dp[i][w] = dp[i - 1][w];
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    return dp[n][capacity];
}

int knapsackFPTAS(const std::vector<int>& weights, const std::vector<int>& values, int capacity, double epsilon) {
    if (weights.empty() || epsilon <= 0) return 0;
    int n = weights.size();
    int maxVal = *std::max_element(values.begin(), values.end());
    double k = (epsilon * maxVal) / n;
    if (k <= 0) k = 1;
    std::vector<int> scaledValues(n);
    int totalScaledValue = 0;
    for (int i = 0; i < n; ++i) {
        scaledValues[i] = std::floor(values[i] / k);
        totalScaledValue += scaledValues[i];
    }
    int scaledCapacity = std::min(capacity, totalScaledValue);
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(scaledCapacity + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int v = 0; v <= scaledCapacity; ++v) {
            dp[i][v] = dp[i - 1][v];
            if (scaledValues[i - 1] <= v && weights[i - 1] <= capacity) {
                dp[i][v] = std::max(dp[i][v], dp[i - 1][v - scaledValues[i - 1]] + values[i - 1]);
            }
        }
    }
    int best = 0;
    for (int v = 0; v <= scaledCapacity; ++v) {
        best = std::max(best, dp[n][v]);
    }
    return best;
}
