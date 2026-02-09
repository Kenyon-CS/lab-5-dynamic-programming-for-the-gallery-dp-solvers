\
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

    int W = 0;
    int n = 0;
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

    std::cout << "Lab 1 (0/1 knapsack)\n";
    std::cout << "Capacity W=" << W << ", n=" << n << "\n";
    std::cout << "Items:\n";
    for (auto& it : items) {
        std::cout << "  " << std::setw(8) << it.name
                  << " width=" << std::setw(2) << it.width
                  << " value=" << std::setw(3) << it.value << "\n";
    }
    std::cout << "\n";

    // ============================
    // TODO: DP TABLE
    // dp[i][w] = best value using first i items with capacity w
    // Use (n+1) x (W+1)
    // ============================
    std::vector<std::vector<int>> dp(n+1, std::vector<int>(W+1, 0));

    // TODO: fill dp table

    // TODO: reconstruct chosen items (backtrack from dp[n][W])
    std::vector<std::string> chosen;

    std::cout << "TODO: compute optimal value and chosen items.\n";
    std::cout << "Expected: print dp[n][W] and chosen item names.\n";

    // Optional: if W and n are small, print dp table.
    if (W <= 40 && n <= 30) {
        std::cout << "\nDP table (currently empty / zeros):\n";
        std::cout << "      w ->";
        for (int w = 0; w <= W; w++) std::cout << std::setw(4) << w;
        std::cout << "\n";
        for (int i = 0; i <= n; i++) {
            std::cout << "i=" << std::setw(2) << i << "  ";
            for (int w = 0; w <= W; w++) std::cout << std::setw(4) << dp[i][w];
            std::cout << "\n";
        }
    }

    return 0;
}
