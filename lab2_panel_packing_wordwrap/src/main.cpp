#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

static void usage(const char* prog) {
    std::cerr << "Usage: " << prog << " datafile\n";
}

int main(int argc, char** argv) {
    if (argc != 2) { usage(argv[0]); return 2; }
    std::ifstream in(argv[1]);
    if (!in) { std::cerr << "Error: cannot open " << argv[1] << "\n"; return 2; }

    int L = 0, n = 0;
    in >> L >> n;
    if (!in || L <= 0 || n < 0) { std::cerr << "Error: bad header\n"; return 2; }

    std::vector<int> w(n + 1, 0); // 1-indexed widths
    for (int i = 1; i <= n; i++) in >> w[i];
    if (!in) { std::cerr << "Error: bad widths\n"; return 2; }

    std::cout << "Lab 2: Word-Wrap DP -- Panel / Wall-Segment Packing\n";
    std::cout << std::string(52, '=') << "\n";
    std::cout << "Wall length L=" << L << ", n=" << n << "\nWidths:\n  ";
    for (int i = 1; i <= n; i++) std::cout << w[i] << (i == n ? '\n' : ' ');

    std::cout << "\nRecurrence:\n"
              << "  cost(i,j) = (L - sum(w[i..j]))^2   if sum <= L  (slack squared)\n"
              << "            = 0                       if j==n and sum <= L  (last wall free)\n"
              << "            = INF                     if sum > L\n"
              << "  dp[0] = 0\n"
              << "  dp[j] = min_{i=1}^{j} { dp[i-1] + cost(i,j) }   for j = 1..n\n\n";

    const long long INF = std::numeric_limits<long long>::max() / 4;

    // Prefix sums for O(1) range-sum queries: sum(i,j) = pref[j] - pref[i-1]
    std::vector<int> pref(n + 1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i - 1] + w[i];
    auto rangeSum = [&](int i, int j) { return pref[j] - pref[i - 1]; };

    // cost(i,j): penalty for placing panels i..j on one wall segment
    std::vector<std::vector<long long>> cost(n + 1, std::vector<long long>(n + 1, INF));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int s = rangeSum(i, j);
            if (s <= L) {
                long long slack = static_cast<long long>(L - s);
                // Last wall (j==n) carries no penalty: unused space is acceptable
                cost[i][j] = (j == n) ? 0LL : slack * slack;
            }
        }
    }

    // dp[j] = minimum total penalty to place panels 1..j
    // prev[j] = start index of the last wall segment that ends at j
    std::vector<long long> dp(n + 1, INF);
    std::vector<int>       prev(n + 1, -1);
    dp[0] = 0;

    for (int j = 1; j <= n; j++) {
        for (int i = 1; i <= j; i++) {
            if (cost[i][j] < INF && dp[i - 1] < INF) {
                long long cand = dp[i - 1] + cost[i][j];
                if (cand < dp[j]) {
                    dp[j]   = cand;
                    prev[j] = i; // segment [i..j] is optimal ending for first j panels
                }
            }
        }
    }

    // Print cost matrix and dp array when dataset is small enough to read
    if (n <= 25) {
        std::cout << "Cost matrix cost(i,j)  (INF shown as .):\n";
        std::cout << "    j->";
        for (int j = 1; j <= n; j++) std::cout << std::setw(6) << j;
        std::cout << "\n";
        for (int i = 1; i <= n; i++) {
            std::cout << "i=" << std::setw(2) << i << " ";
            for (int j = 1; j <= n; j++) {
                if (j < i) { std::cout << std::setw(6) << " "; continue; }
                if (cost[i][j] >= INF / 2) std::cout << std::setw(6) << ".";
                else                        std::cout << std::setw(6) << cost[i][j];
            }
            std::cout << "\n";
        }

        std::cout << "\ndp[0..n]:\n";
        for (int j = 0; j <= n; j++) {
            if (dp[j] >= INF / 2) std::cout << "  dp[" << j << "] = INF\n";
            else                   std::cout << "  dp[" << j << "] = " << dp[j] << "\n";
        }
        std::cout << "\n";
    }

    if (dp[n] >= INF) {
        std::cout << "No valid partition exists (some panel wider than L).\n";
        return 1;
    }

    // Reconstruct wall segments by following prev[] pointers backward
    std::vector<std::pair<int, int>> segs;
    for (int j = n; j > 0; ) {
        int i = prev[j];
        segs.push_back({i, j});
        j = i - 1;
    }
    std::reverse(segs.begin(), segs.end());

    std::cout << "Optimal cost  : " << dp[n] << "\n";
    std::cout << "Wall segments :\n";
    for (int k = 0; k < static_cast<int>(segs.size()); k++) {
        auto [a, b] = segs[k];
        int s = rangeSum(a, b);
        std::cout << "  Wall " << std::setw(2) << k + 1
                  << ": panels " << a << ".." << b << "  widths [";
        for (int p = a; p <= b; p++) std::cout << w[p] << (p == b ? "" : ", ");
        std::cout << "]  sum=" << s << "  slack=" << (L - s) << "\n";
    }

    return 0;
}
