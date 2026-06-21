#include <stdio.h>

#define MAX 10   // maximum capacity of queue

// Define the Queue structure
typedef struct {
    int data[MAX];
    int front;
    int rear;
    int capacity;
} Queue;

// Initialize the queue
void initQueue(Queue *q, int capacity) {
    q->front = -1;
    q->rear = -1;
    q->capacity = capacity;
}

// Check if the queue is empty
int isEmpty(Queue *q) {
    return (q->front == -1);
}

// Check if the queue is full
int isFull(Queue *q) {
    return (q->rear == q->capacity - 1);
}

// Enqueue operation — add element to the rear
void enqueue(Queue *q, int value) {
    if (isFull(q)) {
        printf("Queue is full. Cannot enqueue %d.\n", value);
        return;
    }

    // If queue is empty, set front to 0
    if (q->front == -1)
        q->front = 0;

    q->rear++;
    q->data[q->rear] = value;
    printf("Enqueued: %d\n", value);
}

// Dequeue operation — remove the oldest element (front)
void dequeue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty. Cannot dequeue.\n");
        return;
    }

    printf("Dequeued: %d\n", q->data[q->front]);

    // If this was the last element, reset the queue
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
}

// Print all elements in order
void printQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    for (int i = q->front; i <= q->rear; i++) {
        printf("%d ", q->data[i]);
    }
    printf("\n");
}

// Main function to test
int main() {
    Queue q;
    initQueue(&q, MAX);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);
    enqueue(&q, 40);
    printQueue(&q);

    dequeue(&q);
    printQueue(&q);

    enqueue(&q, 50);
    enqueue(&q, 60);
    printQueue(&q);

    // Try dequeuing all elements
    while (!isEmpty(&q)) {
        dequeue(&q);
    }
    printQueue(&q);

    // Try dequeue on empty queue
    dequeue(&q);

    return 0;
}
