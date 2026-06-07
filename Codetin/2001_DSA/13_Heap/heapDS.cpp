#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

using namespace std;

class MyMinHeap {
    private:
        vector<int> buff;

        // Top-down heapify (sinks an element down to its correct position)
        void minHeapify(int i) {
            int left = leftChild(i);
            int right = rightChild(i);
            int smallest = i;

            // Check if left child is smaller than current element
            if (left < buff.size() && buff[left] < buff[smallest]) {
                smallest = left;
            }
            // Check if right child is smaller than the smallest so far
            if (right < buff.size() && buff[right] < buff[smallest]) {
                smallest = right;
            }

            // If the heap property is violated, swap and continue heapifying down
            if (smallest != i) {
                swap(buff[i], buff[smallest]);
                minHeapify(smallest);
            }
        }

    public:
        int getParent(int i) { return (i - 1) / 2; }
        int leftChild(int i)  { return (2 * i + 1); }
        int rightChild(int i) { return (2 * i + 2); }

        // Returns the minimum element in O(1) time
        int getMin() {
            if (buff.empty()) {
                throw runtime_error("Heap is empty!");
            }
            return buff[0];
        }

        // Inserts a new element in O(log N) time
        void insertElement(int item) {
            buff.push_back(item); // Fix: Use push_back instead of insert
            int i = buff.size() - 1;

            // Bottom-up heapify (swaps up until min-heap property is satisfied)
            while (i != 0 && buff[getParent(i)] > buff[i]) {
                swap(buff[i], buff[getParent(i)]);
                i = getParent(i); // Fix: Update 'i' to move up the tree
            }
        }

        // Removes the minimum element (the root)
        void extractMin() {
            if (buff.empty()) return;
            
            if (buff.size() == 1) {
                buff.pop_back();
                return;
            }

            // Move the last element to the root and sink it down
            buff[0] = buff.back();
            buff.pop_back();
            minHeapify(0);
        }

        // Deletes an element at a specific index 'i'
        void deleteItem(int i) {
            if (i >= buff.size()) {
                cout << "Index out of range!" << endl;
                return;
            }

            if (buff.size() == 1 || i == buff.size() - 1) {
                buff.pop_back();
                return;
            }

            // Swap with the last element
            swap(buff[i], buff[buff.size() - 1]);
            buff.pop_back();

            // The swapped element could be either too small or too large.
            // Check if it needs to go up or down.
            if (i > 0 && buff[getParent(i)] > buff[i]) {
                // Move up
                while (i != 0 && buff[getParent(i)] > buff[i]) {
                    swap(buff[i], buff[getParent(i)]);
                    i = getParent(i);
                }
            } else {
                // Move down
                minHeapify(i);
            }
        }

        // Helper to visualize the heap array
        void printHeap() {
            for (int val : buff) cout << val << " ";
            cout << endl;
        }
};

int main() {
    MyMinHeap heap;
    
    heap.insertElement(3);
    heap.insertElement(2);
    heap.insertElement(15);
    heap.insertElement(5);
    heap.insertElement(4);
    heap.insertElement(45);

    cout << "Min element: " << heap.getMin() << endl; // Output: 2

    cout << "Heap array: ";
    heap.printHeap(); // Output: 2 3 15 5 4 45 

    heap.extractMin();
    cout << "Min element after extracting root: " << heap.getMin() << endl; // Output: 3

    heap.deleteItem(1); // Deletes element at index 1
    cout << "Heap array after deleting index 1: ";
    heap.printHeap();

    return 0;
}