/*
Problem Statement:
    - C langage does not natively has a garbage collector.
    - write a simple, but functinal garbage collector for c.

Solution Approch:
    - the idea is create a wrapper for the malloc(), calloc() and free()
    - a linked list that tracks all the dynamically allocated memory
    - and frees them at the end of the program.
*/

#include<stdio.h>
#include<stdlib.h>

struct gcnode {
    void *val;
    struct gcnode *next;
};
typedef struct gcnode GCNode;

typedef struct{
    GCNode * head;
} GarbageCollector;

GarbageCollector gc;

void * my_malloc(int n){
    void *ptr = (void *)malloc(n);
    if(ptr){
        GCNode *temp = malloc(sizeof(GCNode));
        temp->val = ptr;
        temp->next = NULL;
        if(gc.head == NULL)
            gc.head = temp;
        else{
            GCNode *i = gc.head;
            while(i->next!=NULL)
                i = i->next;
            i->next = temp;
        }
    }
    return ptr;
}

void gc_cleanup(){
    if(gc.head == NULL)
        return;
    GCNode *itr = gc.head;
    GCNode *temp;
    while(itr){
        free(itr->val);
        temp = itr;
        itr = itr->next;
        free(temp);
    }
    return;
}

void my_free(void *ptr) {
    if (!ptr || !gc.head) return;

    GCNode *curr = gc.head;
    GCNode *prev = NULL;

    while (curr) {
        if (curr->val == ptr) {
            if (prev)
                prev->next = curr->next;
            else
                gc.head = curr->next;

            free(curr->val);
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    // Optional: if not found
    fprintf(stderr, "Warning: attempted to free untracked pointer %p\n", ptr);
}

void * my_calloc(int n, int s){
    n = n * s;
    return my_malloc(n);
}

int main(){
    gc.head = NULL;
    int *ptr = (int*)my_malloc(sizeof(int)*10);
    int *aptr = (int*)my_malloc(sizeof(int)*10);
    int *hehe = (int*)malloc(1);
    printf("%p\n", ptr);
    for(int i=0;i<10;i++){
        ptr[i] = i;
        aptr[i] = i+20;
        printf("%d - %d ",ptr[i], aptr[i]);
        printf("\n");
    }
    printf("\n");
    my_free(ptr);
    my_free(hehe);

    gc_cleanup();
    printf("%p\n", ptr);
    for(int i=0;i<10;i++){
        printf("%d - %d ",ptr[i], aptr[i]);
        printf("\n");
    }
    printf("\n");
    return 0;

}