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
    if (!in) { std::cerr << "Error: cannot open " << argv[1] << "\n"; return 2; }

    int CA = 0, CB = 0, n = 0;
    in >> CA >> CB >> n;
    if (!in || CA < 0 || CB < 0 || n < 0) { std::cerr << "Error: bad header\n"; return 2; }

    std::vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        in >> items[i].name >> items[i].width >> items[i].value;
        if (!in) { std::cerr << "Error: bad item line " << i << "\n"; return 2; }
    }

    std::cout << "Lab 3: 2-Knapsack -- Two-Room Allocation\n";
    std::cout << std::string(50, '=') << "\n";
    std::cout << "CA=" << CA << "  CB=" << CB << "  n=" << n << "\nItems:\n";
    for (auto& it : items)
        std::cout << "  " << std::setw(6) << it.name
                  << "  width=" << std::setw(2) << it.width
                  << "  value=" << std::setw(3) << it.value << "\n";

    std::cout << "\nRecurrence:\n"
              << "  dp[i][a][b] = 0  for all a,b  (base: no items)\n"
              << "  dp[i][a][b] = max(\n"
              << "    dp[i-1][a][b],                          // skip artwork i\n"
              << "    dp[i-1][a-w_i][b] + v_i  (if a>=w_i),  // hang in Room A\n"
              << "    dp[i-1][a][b-w_i] + v_i  (if b>=w_i)   // hang in Room B\n"
              << "  )\n\n";

    // Full 3D DP: dp[i][a][b] = best value using first i items,
    // with remaining wall-space a in Room A and b in Room B.
    // Keeping all layers lets us backtrack to recover the allocation.
    std::vector<std::vector<std::vector<int>>> dp(
        n + 1,
        std::vector<std::vector<int>>(CA + 1, std::vector<int>(CB + 1, 0))
    );

    for (int i = 1; i <= n; i++) {
        int wi = items[i - 1].width;
        int vi = items[i - 1].value;
        for (int a = 0; a <= CA; a++) {
            for (int b = 0; b <= CB; b++) {
                dp[i][a][b] = dp[i - 1][a][b];                           // skip
                if (a >= wi)
                    dp[i][a][b] = std::max(dp[i][a][b], dp[i - 1][a - wi][b] + vi); // Room A
                if (b >= wi)
                    dp[i][a][b] = std::max(dp[i][a][b], dp[i - 1][a][b - wi] + vi); // Room B
            }
        }
    }

    // Print final DP grid dp[n][a][b] when capacities are small enough to read
    if (CA <= 25 && CB <= 25) {
        std::cout << "DP grid dp[n=" << n << "][a][b]:\n";
        std::cout << "      b->";
        for (int b = 0; b <= CB; b++) std::cout << std::setw(4) << b;
        std::cout << "\n";
        for (int a = 0; a <= CA; a++) {
            std::cout << "a=" << std::setw(2) << a << "  ";
            for (int b = 0; b <= CB; b++) std::cout << std::setw(4) << dp[n][a][b];
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    // Backtrack through all item layers to recover room assignments.
    // Priority: Room A first, then Room B, then skip.
    std::vector<int> inA, inB, skipped;
    int a = CA, b = CB;
    for (int i = n; i > 0; i--) {
        int wi = items[i - 1].width;
        int vi = items[i - 1].value;
        if (a >= wi && dp[i][a][b] == dp[i - 1][a - wi][b] + vi) {
            inA.push_back(i - 1);
            a -= wi;
        } else if (b >= wi && dp[i][a][b] == dp[i - 1][a][b - wi] + vi) {
            inB.push_back(i - 1);
            b -= wi;
        } else {
            skipped.push_back(i - 1);
        }
    }
    std::reverse(inA.begin(), inA.end());
    std::reverse(inB.begin(), inB.end());

    int sumWA = 0, sumVA = 0, sumWB = 0, sumVB = 0;
    for (int idx : inA) { sumWA += items[idx].width; sumVA += items[idx].value; }
    for (int idx : inB) { sumWB += items[idx].width; sumVB += items[idx].value; }

    std::cout << "Optimal value : " << dp[n][CA][CB] << "\n\n";

    std::cout << "Room A  (capacity " << CA << "):\n";
    for (int idx : inA)
        std::cout << "  " << std::setw(6) << items[idx].name
                  << "  width=" << std::setw(2) << items[idx].width
                  << "  value=" << std::setw(3) << items[idx].value << "\n";
    std::cout << "  --- weight used: " << sumWA << "/" << CA
              << "   value: " << sumVA << "\n\n";

    std::cout << "Room B  (capacity " << CB << "):\n";
    for (int idx : inB)
        std::cout << "  " << std::setw(6) << items[idx].name
                  << "  width=" << std::setw(2) << items[idx].width
                  << "  value=" << std::setw(3) << items[idx].value << "\n";
    std::cout << "  --- weight used: " << sumWB << "/" << CB
              << "   value: " << sumVB << "\n\n";

    if (!skipped.empty()) {
        std::cout << "Not placed:\n";
        for (int idx : skipped)
            std::cout << "  " << items[idx].name
                      << "  (width=" << items[idx].width << ")\n";
    }

    return 0;
}
