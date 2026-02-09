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
    if (!in) { std::cerr << "Error: cannot open " << argv[1] << "\n"; return 2; }

    int CA=0, CB=0, n=0;
    in >> CA >> CB >> n;
    if (!in || CA < 0 || CB < 0 || n < 0) { std::cerr << "Error: bad header\n"; return 2; }

    std::vector<Item> items(n);
    for (int i = 0; i < n; i++) {
        in >> items[i].name >> items[i].width >> items[i].value;
        if (!in) { std::cerr << "Error: bad item line " << i << "\n"; return 2; }
    }

    std::cout << "Lab 3 (two-room allocation / 2D knapsack)\n";
    std::cout << "CA=" << CA << " CB=" << CB << " n=" << n << "\nItems:\n";
    for (auto& it : items) {
        std::cout << "  " << std::setw(8) << it.name
                  << " width=" << std::setw(2) << it.width
                  << " value=" << std::setw(3) << it.value << "\n";
    }
    std::cout << "\n";

    // dp[a][b] for current prefix
    std::vector<std::vector<int>> dp(CA+1, std::vector<int>(CB+1, 0));

    // ============================
    // TODO: fill dp across items
    // Use next table to keep it simple:
    // next = dp; then consider placing item in A or B.
    // ============================

    std::cout << "TODO: compute optimal value dp[CA][CB] and reconstruct assignments.\n";

    // For small capacities, print dp grid (currently zeros)
    if (CA <= 25 && CB <= 25) {
        std::cout << "\nDP grid dp[a][b] (currently empty / zeros):\n";
        std::cout << "      b ->";
        for (int b = 0; b <= CB; b++) std::cout << std::setw(4) << b;
        std::cout << "\n";
        for (int a = 0; a <= CA; a++) {
            std::cout << "a=" << std::setw(2) << a << "  ";
            for (int b = 0; b <= CB; b++) std::cout << std::setw(4) << dp[a][b];
            std::cout << "\n";
        }
    }

    return 0;
}
