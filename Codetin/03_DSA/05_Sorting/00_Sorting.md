# Sorting

Bubble - Selection - Interstion - Merge - Quick - Heap - Radix

| Algorithm          | Approach Summary                                                      | Time Complexity (Avg) | Space Complexity | Stable | In-Place | Comparison-Based | Adaptive |
| ------------------ | --------------------------------------------------------------------- | --------------------- | ---------------- | ------ | -------- | ---------------- | -------- |
| **Bubble Sort**    | Repeatedly swaps adjacent elements if they are in the wrong order.    | O(n²)                 | O(1)             | ✅      | ✅        | ✅                | ✅        |
| **Selection Sort** | Selects the smallest/largest element and places it correctly.         | O(n²)                 | O(1)             | ❌      | ✅        | ✅                | ❌        |
| **Insertion Sort** | Inserts elements into their correct position one at a time.           | O(n²)                 | O(1)             | ✅      | ✅        | ✅                | ✅        |
| **Merge Sort**     | Divides array, sorts halves, and merges them back together.           | O(n log n)            | O(n)             | ✅      | ❌        | ✅                | ❌        |
| **Quick Sort**     | Partitions around a pivot and sorts subarrays recursively.            | O(n log n)            | O(log n)         | ❌      | ✅        | ✅                | ❌        |
| **Heap Sort**      | Builds a heap and repeatedly extracts the max/min element.            | O(n log n)            | O(1)             | ❌      | ✅        | ✅                | ❌        |
| **Shell Sort**     | Sorts elements at set gaps, reducing gaps over time.                  | O(n log n)\*          | O(1)             | ❌      | ✅        | ✅                | ✅        |
| **Counting Sort**  | Counts occurrences and uses them to place elements in order.          | O(n + k)              | O(k)             | ✅      | ❌        | ❌                | ❌        |
| **Radix Sort**     | Sorts elements digit by digit (least to most significant).            | O(nk)                 | O(n + k)         | ✅      | ❌        | ❌                | ❌        |
| **Bucket Sort**    | Distributes elements into buckets and sorts each individually.        | O(n + k)              | O(n + k)         | ✅      | ❌        | ❌                | ✅        |
| **Tim Sort**       | Hybrid of merge and insertion sort; optimized for real-world data.    | O(n log n)            | O(n)             | ✅      | ❌        | ✅                | ✅        |
| **Intro Sort**     | Combines quick, heap, and insertion sort depending on input behavior. | O(n log n)            | O(log n)         | ❌      | ✅        | ✅                | ✅        |

<details>
<summary>Legend:</summary>

| Property             | One-Line Explanation                                          |
| -------------------- | ------------------------------------------------------------- |
| **Stable**           | Maintains the relative order of equal elements.               |
| **In-Place**         | Sorts the array using only a constant amount of extra memory. |
| **Comparison-Based** | Sorts by comparing elements to each other.                    |
| **Adaptive**         | Performs better if the input is already or nearly sorted.     |

</details>

<h2>Built in Sorting function in C</h2>

- `stdlib.h` supports `qsort()`
- Impelents something similar to quick sort
- This requires 4 inputs
    - `base` address of the first element of the arrau
    - `num` number of elements in the array
    - `size` size of each element in the array
    - `compar` function pointer - for comparing the two elements
- **Prototype**
    ```c
    void qsort(void *base, size_t num, size_t size, int (*compar)(const void *, const void *));
    ```
- **Example**
    In the compare function notice how the pointer is first type casted and then dereferenced.
    using the syntax `(*(int *)ptr)`
    ```c
    #include <stdio.h>
    #include <stdlib.h>

    int compareInts(const void *a, const void *b) {
    return (*(int*)a - *(int*)b); // Ascending order
    }

    int main() {
        int arr[] = {5, 2, 9, 1, 5, 6};
        size_t n = sizeof(arr) / sizeof(arr[0]);

        qsort(arr, n, sizeof(int), compareInts);

        for (size_t i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        return 0;
    }
    ```


<h2>Built in Sorting function in CPP</h2>

- Header `#include <algorithm>` ; Namespace `std`
- Singature: This is a overloaded function, hence two prototypes
    ```cpp
    template <class RandomIt> // where RandomIt is the random access iterator
    void sort(RandomIt first, RandomIt last);
    ```
    ```cpp
    template <class RandomIt, class Compare>
    void sort(RandomIt first, RandomIt last, Compare comp );
    ```
- Example;   
    ```cpp
    vector<int> v;
    std::sort(v.begin(), v.end());
    ```


| Feature               | Description                                                  |
| --------------------- | ------------------------------------------------------------ |
| **Algorithm Used**    | IntroSort (hybrid of QuickSort, HeapSort, and InsertionSort) |
| **Time Complexity**   | Average: O(n log n), Worst-case: O(n log n)                  |
| **Sort Order**        | Default: Ascending                                           |
| **Custom Comparator** | Can use a lambda or function to sort in custom order         |

