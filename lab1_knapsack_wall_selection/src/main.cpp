#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

struct Item {
    std::string name;
    int width = 0;
    int value = 0;
};

static void usage(const char* prog) {
    std::cerr << "Usage: " << prog << " datafile\n";
}

int main(int argc, char** argv) {
    if (argc != 2) { usage(argv[0]); return 2; }

    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Error: cannot open " << argv[1] << "\n";
        return 2;
    }

    int W = 0, n = 0;
    in >> W >> n;
    if (!in || W < 0 || n < 0) {
        std::cerr << "Error: bad header (W, n)\n";
        return 2;
    }

    std::vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        in >> items[i].name >> items[i].width >> items[i].value;
        if (!in) {
            std::cerr << "Error: bad item line " << i << "\n";
            return 2;
        }
    }

    std::cout << "Lab 1: 0/1 Knapsack -- Room Wall-Space Selection\n";
    std::cout << std::string(52, '=') << "\n";
    std::cout << "Capacity W=" << W << ", n=" << n << "\n";
    std::cout << "Items:\n";
    for (auto& it : items)
        std::cout << "  " << std::setw(6) << it.name
                  << "  width=" << std::setw(2) << it.width
                  << "  value=" << std::setw(3) << it.value << "\n";

    std::cout << "\nRecurrence:\n"
              << "  dp[0][w] = 0  for all w  (base case: no items)\n"
              << "  dp[i][w] = dp[i-1][w]                            if width_i > w\n"
              << "  dp[i][w] = max(dp[i-1][w], dp[i-1][w-w_i]+v_i)  otherwise\n\n";

    // DP table: dp[i][w] = max value using first i items with wall-space w
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        int wi = items[i - 1].width;
        int vi = items[i - 1].value;
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];                              // option 1: skip item i
            if (wi <= w)
                dp[i][w] = std::max(dp[i][w], dp[i - 1][w - wi] + vi); // option 2: hang item i
        }
    }

    // Print full DP table (readable when W and n are small)
    if (W <= 40 && n <= 30) {
        std::cout << "DP table dp[i][w]:\n";
        std::cout << "              w->";
        for (int w = 0; w <= W; w++) std::cout << std::setw(4) << w;
        std::cout << "\n";
        for (int i = 0; i <= n; i++) {
            if (i == 0)
                std::cout << " i= 0 (base)  ";
            else
                std::cout << " i=" << std::setw(2) << i
                          << " (" << std::setw(4) << items[i - 1].name << ") ";
            for (int w = 0; w <= W; w++) std::cout << std::setw(4) << dp[i][w];
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // Backtrack from dp[n][W] to recover which items were selected
    std::vector<std::string> chosen;
    int rem = W;
    for (int i = n; i > 0; i--) {
        if (dp[i][rem] != dp[i - 1][rem]) {   // value changed => item i was taken
            chosen.push_back(items[i - 1].name);
            rem -= items[i - 1].width;
        }
    }
    std::reverse(chosen.begin(), chosen.end());

    int totalW = W - rem;
    std::cout << "Optimal value : " << dp[n][W] << "\n";
    std::cout << "Total weight  : " << totalW << " / " << W << "\n";
    std::cout << "Chosen items  :";
    for (auto& s : chosen) std::cout << " " << s;
    std::cout << "\n";

    return 0;
}
