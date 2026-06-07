#include <iostream>
#include <queue> // Required header

using namespace std;

int main() {
    priority_queue<int> maxPq; // creating max queue
    priority_queue<int, vector<int>, greater<int>> minPq; // creating min queue

    // Insert elements
    maxPq.push(10);
    maxPq.push(30);
    maxPq.push(20);
    maxPq.push(5);
    // The largest element (30) will be at the top
    cout << "Top element: " << maxPq.top() << endl; // Output: 30
    // Remove the top element
    maxPq.pop(); 
    cout << "Next top element: " << maxPq.top() << endl; // Output: 20
    
    minPq.push(10);
    minPq.push(30);
    minPq.push(20);
    minPq.push(5);
    // The smallest element (5) will be at the top
    cout << "Top element: " << minPq.top() << endl; // Output: 5
    minPq.pop();
    cout << "Next top element: " << minPq.top() << endl; // Output: 10
    return 0;
}
