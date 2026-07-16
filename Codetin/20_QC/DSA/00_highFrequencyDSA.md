# Cold-start expectation (important reality check) 

If you truly want “cold start ready”, you should be able to:

* Immediately recognize pattern in 30–60 seconds
* Write optimal approach without brute forcing first
* Code cleanly in 15–25 minutes per medium problem
---

## 1. Arrays + Two Pointers (VERY IMPORTANT)

You should be able to solve these in 10–20 min each:

1. [1 Two Sum](https://leetcode.com/problems/two-sum/description/) (all variants: unsorted, sorted, return indices)
* [15. 3Sum](https://leetcode.com/problems/3sum/description/) (and avoid duplicates) || [18. 4Sum](https://leetcode.com/problems/4sum/description/)
* [11. Container With Most Water](https://leetcode.com/problems/container-with-most-water/description/) || [42. Trapping Rain Water](https://leetcode.com/problems/trapping-rain-water/description/)
* Move Zeroes [283. Move Zeroes](https://leetcode.com/problems/move-zeroes/description/)
* Remove Duplicates from Sorted Array [26. Remove Duplicates from Sorted Array](https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/)
* Sort Colors (Dutch National Flag) [75. Sort Colors](https://leetcode.com/problems/sort-colors/description/)
8. Maximum Subarray (Kadane’s Algorithm) [53. Maximum Subarray](https://leetcode.com/problems/maximum-subarray/description/)

**What they test:** pointer logic, greedy thinking, edge cases.

### Sorting
---
  - Merge Intervals (sorting + greedy) [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/description/)
  - Merge Sort
  - Quick Sort
  - Heap Sort (concepts + implementation)

---

## 2. Sliding Window (VERY HIGH FREQUENCY)

* Maximum Sum Subarray of size K
* Longest Substring Without Repeating Characters [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/description/)
* Minimum Window Substring (important) [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/description/)
* Longest Repeating Character Replacement [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/description/)
* Subarray Sum Equals K (prefix sum + hashmap) [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/description/)

**Key idea:** you should immediately think “window + hashmap/prefix sum”.

---

## 3. Hashing / Prefix Sum

* Two Sum (again, but optimized) [1. Two Sum](https://leetcode.com/problems/two-sum/description/)
* Subarray Sum Equals K [560. Subarray Sum Equals K](https://leetcode.com/problems/subarray-sum-equals-k/description/)
* Longest Consecutive Sequence [128. Longest Consecutive Sequence](https://leetcode.com/problems/longest-consecutive-sequence/description/)
* Group Anagrams [49. Group Anagrams](https://leetcode.com/problems/group-anagrams/description/)
* Top K Frequent Elements [347. Top K Frequent Elements](https://leetcode.com/problems/top-k-frequent-elements/description/)
* Product of Array Except Self [238. Product of Array Except Self](https://leetcode.com/problems/product-of-array-except-self/description/)

**What they test:** frequency maps, cumulative reasoning.

---

## 4. Stack / Monotonic Stack (VERY IMPORTANT for QC-style interviews)

* Valid Parentheses [20. Valid Parentheses](https://leetcode.com/problems/valid-parentheses/description/)
* Next Greater Element I & II [496. Next Greater Element I](https://leetcode.com/problems/next-greater-element-i/description/) / [503. Next Greater Element II](https://leetcode.com/problems/next-greater-element-ii/description/)
* Daily Temperatures [739. Daily Temperatures](https://leetcode.com/problems/daily-temperatures/description/)
* Largest Rectangle in Histogram (HARD but critical) [84. Largest Rectangle in Histogram](https://leetcode.com/problems/largest-rectangle-in-histogram/description/)
* Min Stack [155. Min Stack](https://leetcode.com/problems/min-stack/description/)

**If you master monotonic stack, you’re ahead of many candidates.**

---

## 5. Linked List (Common in screening rounds)

1. [206. Reverse Linked List](https://leetcode.com/problems/reverse-linked-list/description/) ( recursive & interative ) || [92. Reverse Linked List II](https://leetcode.com/problems/reverse-linked-list-ii/description/)
2. **`Cycles`:** [LC141 Detect](https://leetcode.com/problems/linked-list-cycle/description/) (explain math) || [Find start](https://leetcode.com/problems/linked-list-cycle-ii/description/) || [remove the the loop](https://www.geeksforgeeks.org/problems/remove-loop-in-linked-list/1)
3. [21. Merge Two Sorted Lists](https://leetcode.com/problems/merge-two-sorted-lists/description/)
4. [19. Remove Nth Node From End of List](https://leetcode.com/problems/remove-nth-node-from-end-of-list/description/)
5. **`Modify`:** [25. Reverse Nodes in k-Group](https://leetcode.com/problems/reverse-nodes-in-k-group/description/) || [24. Swap Nodes in Pairs](https://leetcode.com/problems/swap-nodes-in-pairs/description/) || [61. Rotate List](https://leetcode.com/problems/rotate-list/description/)
6. **`Design`** [146. LRU Cache](https://leetcode.com/problems/lru-cache/description/) || [460. LFU Cache](https://leetcode.com/problems/lfu-cache/description/)


---

## 6. Binary Search (must be sharp)

1. [704. Binary Search](https://leetcode.com/problems/binary-search/description/)
2. [33. Search in Rotated Sorted Array](https://leetcode.com/problems/search-in-rotated-sorted-array/description/)
3. [34. Find First and Last Position of Element in Sorted Array](https://leetcode.com/problems/find-first-and-last-position-of-element-in-sorted-array/description/)
* [162. Find Peak Element](https://leetcode.com/problems/find-peak-element/description/)
*  [4. Median of Two Sorted Arrays](https://leetcode.com/problems/median-of-two-sorted-arrays/description/) (advanced, optional but strong signal)

---

## 7. Trees (VERY IMPORTANT)

* Inorder / Preorder / Postorder traversal (recursive + iterative)
* Level Order Traversal (BFS) [102. Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/description/)
* [104. Maximum **Depth** of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/description/) | [543. **Diameter** of Binary Tree](https://leetcode.com/problems/diameter-of-binary-tree/description/)
* Lowest Common Ancestor [236. Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/description/)
* Validate BST [98. Validate Binary Search Tree](https://leetcode.com/problems/validate-binary-search-tree/description/)

---

## 8. Graphs (basic + BFS/DFS)

* Number of Islands [200. Number of Islands](https://leetcode.com/problems/number-of-islands/description/)
* Clone Graph [133. Clone Graph](https://leetcode.com/problems/clone-graph/description/)
* BFS shortest path in grid [1091. Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/description/)
* Detect cycle (undirected graph)
* Topological Sort (Course Schedule) [207. Course Schedule](https://leetcode.com/problems/course-schedule/description/)

---

## 9. Dynamic Programming (only core patterns for 1-week prep)

Don’t overdo DP—focus patterns:

* Climbing Stairs [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/description/)
* House Robber I & II [198. House Robber](https://leetcode.com/problems/house-robber/description/) / [213. House Robber II](https://leetcode.com/problems/house-robber-ii/description/)
* Coin Change [322. Coin Change](https://leetcode.com/problems/coin-change/description/)
* Longest Increasing Subsequence [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/description/)
* 0/1 Knapsack (basic form)
* Edit Distance (optional stretch) [72. Edit Distance](https://leetcode.com/problems/edit-distance/description/)

---

## 10. “Qualcomm-style bonus areas” (important in embedded/system companies)

They sometimes mix DSA with reasoning:

* Bit manipulation:

  * Single Number [136. Single Number](https://leetcode.com/problems/single-number/description/)
  * Count set bits [338. Counting Bits](https://leetcode.com/problems/counting-bits/description/)
  * Reverse bits [190. Reverse Bits](https://leetcode.com/problems/reverse-bits/description/)
  * extract bits , set bits and reset bit, exhange bit values at given position
* Memory/efficiency questions:

  * O(1) space tricks
* Time complexity reasoning

---