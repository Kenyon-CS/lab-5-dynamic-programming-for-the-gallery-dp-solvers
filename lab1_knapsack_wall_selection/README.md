# Lab 1 — Room Wall-Space Selection (0/1 Knapsack)

## Problem
A room has **W units** of usable wall capacity.
Each artwork `i` has:
- `width_i` (wall space consumed; includes clearance)
- `value_i` (curatorial value)

Choose a subset (0/1 each) to **maximize total value** without exceeding capacity.

## Input format
Text file:
```
W
n
name width value
name width value
...
```

Example:
```
10
4
A 2 3
B 3 4
C 4 5
D 5 8
```

## Output requirements (what your program should do)
- Print the optimal value
- Print the chosen artwork names
- For the **simple** dataset, print the full DP table `dp[i][w]`

## DP table
`dp[i][w]` = best value using first `i` items with capacity `w`.

Recurrence:
- skip: `dp[i-1][w]`
- take (if `width_i <= w`): `dp[i-1][w-width_i] + value_i`

## Datasets
- `data/simple.txt` — small, meant for printing the whole table.
- `data/large*.txt` — larger instances for correctness + performance.

