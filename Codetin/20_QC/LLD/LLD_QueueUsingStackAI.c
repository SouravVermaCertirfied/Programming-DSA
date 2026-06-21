#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Stack structure
typedef struct {
    int data[MAX];
    int top;
} Stack;

// Initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Check if stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Check if stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Push element onto stack
void push(Stack *s, int x) {
    if (isFull(s)) {
        printf("Stack Overflow\n");
        return;
    }
    s->data[++(s->top)] = x;
}

// Pop element from stack
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack Underflow\n");
        return -1;
    }
    return s->data[(s->top)--];
}

// Queue structure using two stacks
typedef struct {
    Stack stackPush;
    Stack stackPop;
} Queue;

// Initialize queue
void initQueue(Queue *q) {
    initStack(&q->stackPush);
    initStack(&q->stackPop);
}

// Move elements from stackPush to stackPop
void moveStack(Stack *from, Stack *to) {
    while (!isEmpty(from)) {
        push(to, pop(from));
    }
}

// Enqueue operation
void enqueue(Queue *q, int x) {
    push(&q->stackPush, x);
}

// Dequeue operation
int dequeue(Queue *q) {
    if (isEmpty(&q->stackPop)) {
        if (isEmpty(&q->stackPush)) {
            printf("Queue is empty\n");
            return -1;
        }
        moveStack(&q->stackPush, &q->stackPop);
    }
    return pop(&q->stackPop);
}

// Main function to test
int main() {
    Queue q;
    initQueue(&q);

    enqueue(&q, 10);
    enqueue(&q, 20);
    enqueue(&q, 30);

    printf("Dequeued: %d\n", dequeue(&q)); // 10
    printf("Dequeued: %d\n", dequeue(&q)); // 20

    enqueue(&q, 40);
    printf("Dequeued: %d\n", dequeue(&q)); // 30
    printf("Dequeued: %d\n", dequeue(&q)); // 40
    printf("Dequeued: %d\n", dequeue(&q)); // Queue empty

    return 0;
}
