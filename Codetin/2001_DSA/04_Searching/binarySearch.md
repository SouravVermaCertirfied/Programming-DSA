## Why `(left + right) / 2` ❌ Overflows Use (left + (right - left)/2 ) always ✅

It is a classic example of an integer **overflow of intermediate sum**.  
While mathematically correct, it can fail on a computer due to fixed-size memory.

## The Problem
Most programming languages use fixed-size integers (like 32-bit signed integers). These have a maximum capacity (e.g., **2,147,483,647**).

When you calculate `(left + right) / 2`:
1. The computer first calculates the sum: `left + right`.
2. If both numbers are large, their sum can exceed the maximum capacity.
3. This causes the value to **"wrap around"** (usually becoming a negative number).
4. Dividing that negative result by 2 gives an incorrect midpoint.

### Example (32-bit Signed Integer)
* **Max Value:** $2,147,483,647$
* **Left:** $1,500,000,000$
* **Right:** $1,500,000,000$
* **Actual Sum:** $3,000,000,000$ (Greater than Max!)
* **Stored Sum:** $-1,294,967,296$ (Overflowed)
* **Result / 2:** $-647,483,648$ (Incorrect)

---

## Solution - Subtraction Method (Recommended)

This approach calculates the distance between the two points first, ensuring the **intermediate sum** never exceeds `right`.

$$mid = left + \frac{right - left}{2}$$

# **Problems List**
1. **Basic Binary Search**  
Standard binary search in a sorted array.  
Find first occurrence of an element.  
Find last occurrence of an element.  
Count occurrences of a given element.  
Check if an element exists in a rotated sorted array.  

2. **Variations on Sorted Arrays**  
☢️Find the ceiling of a number (smallest number ≥ target).  
☢️Find the floor of a number (largest number ≤ target).  
☢️Find the closest number to a target.  
Find the pivot in a rotated sorted array.  
Search in a rotated sorted array.  
☢️Find minimum in a rotated sorted array.  
Find maximum in a rotated sorted array.  
Find kth smallest/largest element in a sorted array.  
☢️Search in a 2D matrix where rows and columns are sorted.  

3. **Binary Search on Answer (or Optimization Problems)**  
☢️Aggressive cows / max distance problem.  
Wood cutting problem (max piece length).  
Painter’s partition problem. 
Minimize maximum pages in book allocation.  
Koko eating bananas problem.  
Split array largest sum problem.  
Capacity to ship packages within D days.  

4. **Special Patterns**
Search in an infinite sorted array (or unknown length).  
Peak element in an array (local maxima).  
Find mountain array peak.  
Bitonic array search (increasing then decreasing).  
Square root of a number (or nth root).  
Find smallest/largest number satisfying condition.  

5. **Miscellaneous / Trickier Binary Search**  
☢️Median of two sorted arrays.  
Find fixed point (arr[i] = i).  
Rotated array + duplicates search.  
Find number of rotations in a rotated array.  
☢️Allocate minimum number of pages (book distribution variation).  
☢️Minimize maximum work (job scheduling variation).  

6. **Advanced / Competitive Programming**  
Fractional problems: find largest fraction ≤ target.  
Ternary search problems for unimodal functions.   
Sliding window + binary search on sums.  
☢️Kth smallest element in a sorted matrix using binary search.  
Binary search on floating point numbers (precision problems).  
