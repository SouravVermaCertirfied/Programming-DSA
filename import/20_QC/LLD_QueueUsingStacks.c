/*
Problem Statement:
    design a queue, using two stacks.

Approch:
    - use two stacks, one for pushing and other for popping.
*/

#include<stdlib.h>
#include<stdbool.h>
#include<stdio.h>

#define STACKSIZE 10

struct mystack{
    int vals[STACKSIZE];
    int top;
};

struct myqueue{
    struct mystack ins;
    struct mystack outs;
    int front;
    int rear;
};

void qinit(struct myqueue *q){
    q->front = -1;
    q->rear = -1;
    q->outs.top = -1;
    q->ins.top = -1;
}

bool isEmpty(struct mystack *s){
    if(s->top == -1)
        return true;
    return false;
}

void pushStack(struct mystack *s, int x){
    if(s->top+1 == STACKSIZE){
        printf("queueu is full \n");
        return;
    }
    s->top += 1;
    s->vals[s->top] = x;
    return;
}

void popStack(struct mystack *s){
    if(s->top == -1){
        return;
    }
    s->top -= 1;
    return;
}

int topStack(struct mystack *s){
    if(s->top == -1){
        printf("stack is empty, cannot pop \n");
        return 1;
    }
    return s->vals[s->top];
}

void push(struct myqueue *q, int x){
    if(isEmpty(&(q->ins)) && isEmpty(&(q->outs))){
        pushStack(&(q->ins), x);
    }
    else if(!isEmpty(&(q->ins)) && isEmpty(&(q->outs))){
        pushStack(&(q->ins), x);
    }
    else if(isEmpty(&(q->ins)) && !isEmpty(&(q->outs))){
        while(!isEmpty(&(q->outs))){
            pushStack(&(q->ins), topStack(&(q->outs)));
            popStack(&(q->outs));
        }
        pushStack(&(q->ins), x);
    }
    return;
}

void pop(struct myqueue *q){
    if(isEmpty(&(q->ins)) && !isEmpty(&(q->outs))){
        popStack(&(q->outs));
    }
    else if(!isEmpty(&(q->ins)) && isEmpty(&(q->outs))){
        while(!isEmpty(&(q->ins))){
            pushStack(&(q->outs), topStack(&(q->ins)));
            popStack(&(q->ins));
        }
        popStack(&(q->outs));
    }
}

void printstack(struct mystack *s){
    if(isEmpty(s)){
        printf(" is empty ! \n");
        return;
    }
    int i=s->top;
    while(i>0){
        printf("%d ",s->vals[i]);
        i--;
    }
    printf("\n");
    printf("\n");
}


void printall(struct myqueue *q){
    printf("Printing ins : ");
    printstack(&(q->ins));
    printf("Printing outs : ");
    printstack(&(q->outs));
    return;
}

int main(){
    struct myqueue q;
    qinit(&q);
    printf("\n");

    for(int i=0; i<12; i++){
        push(&q, i);
        printall(&q);
    }
    for(int i=0; i<16; i++){
        pop(&q);
        printall(&q);
    }
    printf("\n");
    return 0;
}



