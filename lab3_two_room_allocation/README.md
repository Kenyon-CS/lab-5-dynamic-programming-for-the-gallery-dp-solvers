# Lab 3 — Two-Room Allocation (2D Knapsack DP)

## Problem
You have two rooms with wall capacities:
- Room A capacity = CA
- Room B capacity = CB

Each artwork can be:
- placed in Room A (consumes width)
- placed in Room B (consumes width)
- skipped

Goal: maximize total value without exceeding either capacity.

## Input format
```
CA CB
n
name width value
name width value
...
```

Example:
```
6 7
5
P1 2 6
P2 3 5
P3 4 8
P4 5 9
P5 1 3
```

## Output requirements
- Maximum total value
- Assignment of each chosen artwork: A or B (and which were skipped)
- For `data/simple.txt`, print the full dp grid dp[a][b].

## DP
`dp[a][b]` = best value achievable for capacities (a,b) after processing some prefix of artworks.

Transition for item (w,v):
- skip
- put in A if w<=a: dp[a-w][b] + v
- put in B if w<=b: dp[a][b-w] + v

Implementation note:
Use `next = dp` copy per item (simplest), or reverse loops with care.

