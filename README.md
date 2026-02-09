# Art Exhibition Layout Project — Dynamic Programming Labs (Starter)

This repo contains **three DP subproblems** inspired by the exhibition-layout planning project.
Each lab lives in its own folder with:
- a minimal C++ starter program
- a Makefile
- example datasets (one small + several larger)

Folders:
- `lab1_knapsack_wall_selection/` — 0/1 knapsack (pick artworks for a single room wall capacity)
- `lab2_panel_packing_wordwrap/` — “word wrap” DP (break ordered artworks across fixed-length panels)
- `lab3_two_room_allocation/` — 2D knapsack (assign each artwork to Room A, Room B, or skip)

## Build (all labs)
From a lab folder:
```bash
make
```

## Run (all labs)
```bash
./bin/lab data/simple.txt
./bin/lab data/large1.txt
```

## Expectations
These are **starter projects**. The provided code:
- parses input
- prints the problem instance
- includes TODOs for the DP table + reconstruction

Students should implement:
1) DP table fill
2) reconstruction (chosen items / breaks / room assignment)
3) sanity output for the provided datasets

## C++ version
Designed for **C++17**.

## Suggested workflow
1. Start with `data/simple.txt` and print the DP table.
2. Add reconstruction.
3. Move to `large*.txt`, verify output, then stress-test runtime.

