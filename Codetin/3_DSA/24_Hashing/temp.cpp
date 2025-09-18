#include <iostream>
using namespace std;

#define BUCKETSIZE
#define HASH(val) (val%BUCKETSIZE) // returns the key aka index in the list

typedef struct {
    int val;
    Node *next;
} Node;

Node *list[BUCKETSIZE];

bool insertVal(int val){
    int key = HASH(val);
    int *newitem = malloc(sizeof(Node));
    newitem->val =  val;
    newitem->next = NULL;
    if(list[key]==NULL){
        list[key] = newitem;
    }
    else{
        Node *ptr = list[key];
        while(ptr->next!=NULL);
        ptr->next = newitem;
    }
}

bool searchVal(int val){
    int key= HASH(val);
    if(list[key]==NULL){
        return false;
    }
    else{
        Node *ptr = list[key];
        while(ptr->val!=val);
        if(ptr->val==val)
            return true;
    }
    return false;
}

void printList(Node **lister){
    Node *ptr = NULL;
    for(int i=0; i<BUCKETSIZE; i++){
        ptr = lister[i];
        while(ptr!=NULL){
            cout<<ptr->val<<" ";
        }
        cout<<endl;
    }

}

int main(){
    cout<<insertVal(10)<<endl;
    cout<<insertVal(20)<<endl;
    
    cout<<searchVal(50)<<endl;
    cout<<searchVal(20)<<endl;

    cout<<printList(50)<<endl;
    cout<<printList(20)<<endl;


    return 0;
}


