/*
    Circular Queue with Overwrite Behavior (Fixed Capacity)

    - Implements a circular queue using a fixed-size array.
    - When the queue is FULL, inserting a new element
      OVERWRITES the OLDEST element (front moves forward).
    - No separate size variable (qsize) is maintained.
      Size is computed dynamically using front and rear indices.
    - Supports O(1) insert and delete operations.

    Queue State Rules:
    ------------------
    - Empty queue      : front == -1
    - Full queue       : (rear + 1) % CAP == front
    - Oldest element   : at index 'front'
    - Newest element   : at index 'rear'

    Features:
    ---------
    - insert(val)      : inserts element, overwrites if full
    - del()            : removes oldest element
    - getsize()        : returns current number of elements
    - printall_while() : prints elements using while(true)
    - printall_for()   : prints elements using a for-loop
                         with condition in the for statement

    Time Complexity:
    ----------------
    - Insert : O(1)
    - Delete : O(1)
    - Print  : O(n)

    Space Complexity:
    -----------------
    - O(CAP)
*/

#include <iostream>
using namespace std;

#define CAP 10

int arr[CAP];
int front = -1;
int rear  = -1;

/* helpers */
bool isEmpty() {
    return front == -1;
}

bool isFull() {
    return ((rear + 1) % CAP) == front;
}

/* insert with overwrite */
void insert(int val) {
    if (isEmpty()) {
        front = rear = 0;
        arr[rear] = val;
        return;
    }

    if (isFull()) {
        front = (front + 1) % CAP;
        rear  = (rear + 1) % CAP;
        arr[rear] = val;
        return;
    }

    rear = (rear + 1) % CAP;
    arr[rear] = val;
}

/* delete from front */
void del() {
    if (isEmpty()) {
        cout << "Queue empty\n";
        return;
    }

    if (front == rear) {
        front = rear = -1;
        return;
    }

    front = (front + 1) % CAP;
}

/* size without qsize */
int getsize() {
    if (isEmpty())
        return 0;

    if (rear >= front)
        return rear - front + 1;

    return CAP - front + rear + 1;
}

/* print variant 1: while(true) */
void printall_while() {
    if (isEmpty()) {
        cout << "Queue empty\n";
        return;
    }

    int i = front;
    while (true) {
        cout << arr[i] << " ";
        if (i == rear) break;
        i = (i + 1) % CAP;
    }
    cout << endl;
}

/* print variant 2: for loop with condition */
void printall_for() {
    if (isEmpty()) {
        cout << "Queue empty\n";
        return;
    }

    for (int i = front; i != (rear + 1) % CAP; i = (i + 1) % CAP) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    cout << "Insert:\n";
    for (int i = 0; i < 15; i++) {
        insert(i);
        printall_for();
        cout << "size = " << getsize() << endl;
    }

    cout << "\nDelete:\n";
    for (int i = 0; i < 15; i++) {
        del();
        printall_while();
        cout << "size = " << getsize() << endl;
    }

    return 0;
}
