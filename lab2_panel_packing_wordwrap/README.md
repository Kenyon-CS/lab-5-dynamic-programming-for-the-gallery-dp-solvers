# Lab 2 — Panel / Wall-Segment Packing (Word Wrap DP)

## Problem
You have a sequence of artworks that must stay in a fixed order (narrative order).
You have wall panels of fixed length **L**.
You decide where to break the sequence into panels.

Penalty discourages ugly gaps:
- If artworks `i..j` fit on a panel, cost = `(L - sum(widths[i..j]))^2`
- If they do not fit, cost = INF
- Usually: **last panel cost = 0**

Goal: minimize total penalty.

## Input format
```
L
n
width_1 width_2 ... width_n
```

Example:
```
10
5
2 5 3 4 2
```

## Output requirements
- Minimum total penalty
- The panel breaks (which indices on each panel)
- For `data/simple.txt`, print:
  - the cost(i,j) matrix
  - dp[0..n]

## DP
Let `dp[j]` = min penalty to pack artworks 1..j.
Then:
`dp[j] = min_{i=1..j} ( dp[i-1] + cost(i,j) )`

Also store `prev[j]` for reconstruction.

