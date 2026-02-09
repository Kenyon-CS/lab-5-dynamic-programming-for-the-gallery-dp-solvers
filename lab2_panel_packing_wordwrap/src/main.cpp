\
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

    std::vector<int> w(n+1, 0); // 1-indexed widths
    for (int i = 1; i <= n; i++) in >> w[i];
    if (!in) { std::cerr << "Error: bad widths\n"; return 2; }

    std::cout << "Lab 2 (word-wrap / panel packing)\n";
    std::cout << "Panel length L=" << L << ", n=" << n << "\nWidths:\n  ";
    for (int i = 1; i <= n; i++) std::cout << w[i] << (i==n?'\n':' ');
    std::cout << "\n";

    const long long INF = std::numeric_limits<long long>::max()/4;

    // Prefix sums to compute sums quickly
    std::vector<int> pref(n+1, 0);
    for (int i = 1; i <= n; i++) pref[i] = pref[i-1] + w[i];

    auto sum = [&](int i, int j) -> int { return pref[j] - pref[i-1]; };

    // ============================
    // TODO: cost(i,j) matrix
    // cost = (L - sum(i..j))^2 if fits, else INF
    // last line cost often treated as 0 when j==n
    // ============================
    std::vector<std::vector<long long>> cost(n+1, std::vector<long long>(n+1, INF));
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j++) {
            int s = sum(i,j);
            if (s <= L) {
                long long slack = (long long)(L - s);
                long long c = slack * slack;
                // Common convention: last panel cost = 0
                if (j == n) c = 0;
                cost[i][j] = c;
            }
        }
    }

    // ============================
    // TODO: dp
    // dp[j] = min penalty for 1..j
    // prev[j] stores best i (start index) for last panel
    // ============================
    std::vector<long long> dp(n+1, INF);
    std::vector<int> prev(n+1, -1);
    dp[0] = 0;

    // TODO: fill dp and prev

    std::cout << "TODO: compute dp[n] and reconstruct breaks.\n";

    // For small n, print cost matrix and dp
    if (n <= 25) {
        std::cout << "\nCost matrix cost(i,j) (INF shown as .):\n    j->";
        for (int j = 1; j <= n; j++) std::cout << std::setw(6) << j;
        std::cout << "\n";
        for (int i = 1; i <= n; i++) {
            std::cout << "i=" << std::setw(2) << i << " ";
            for (int j = 1; j <= n; j++) {
                if (j < i) { std::cout << std::setw(6) << " "; continue; }
                if (cost[i][j] >= INF/2) std::cout << std::setw(6) << ".";
                else std::cout << std::setw(6) << cost[i][j];
            }
            std::cout << "\n";
        }

        std::cout << "\ndp (currently INF except dp[0]):\n";
        for (int j = 0; j <= n; j++) {
            if (dp[j] >= INF/2) std::cout << "dp[" << j << "]=INF\n";
            else std::cout << "dp[" << j << "]=" << dp[j] << "\n";
        }
    }

    return 0;
}
