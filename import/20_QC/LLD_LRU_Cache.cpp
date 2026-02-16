/*
    this is first attempt, where LRU Cache is implement using Double Lined List
*/

#include<iostream>
#include<stdlib.h>
using namespace std;

class Node{
    public:
        int val;
        int key;
        Node *next = NULL, *prev = NULL;
        Node(int val, int key){ this->key = key; this->val = val; }
};

class LRUCache{
    public:
    int cap;
    int size = 0;
    Node *head = NULL, *tail = NULL;
    /* todo: extned with hasmap in next iteration */
    /*Node **hashmap;  */
    LRUCache(int cap){ this->cap = cap; }

    int getVal(int key){
        if(head==NULL)
            return -1;
        Node *ptr = head;
        while(ptr){
            if(ptr->key == key)
                return ptr->val;
            ptr = ptr->next;
        }
        return -1;
    }

    bool isEmpty(){
        if(head==NULL && tail==NULL)
            return true;
        return false;
    }
    int putVal(int key, int val){
        if(cap==0) return 1;
        // todo: make space if full, remove the last node
        if(size >= cap){
            if(head!=NULL && head==tail){ // there is just one node
                delete head;
                head = NULL;
                tail = NULL;
            }
            else{
                tail->prev->next = NULL;
                Node *temp = tail;
                tail = tail->prev;
                // delete temp;
            }
        }
        else{
            size++;
        }
        // insert a node at the first position
        Node *tnode = new Node(key, val);
        if(isEmpty()){
            // enter as first element
            head = tnode;
            tail = tnode;
        }
        else{
            // enter at first position
            head->next->prev = tnode;
            tnode->next = head;
            tnode->prev = NULL;
            head = tnode;
        }
        return 0;
    }
};

int main(){
    int cap = 5 ;
    LRUCache LRU(cap);
    for(int i=0; i<15; i++){
        cout<<LRU.putVal(i, i)<< " ";
    }
    cout<<endl;
    for(int i=0; i<15; i++){
        cout<<LRU.getVal(i)<<" ";
    }
    return 0;
}