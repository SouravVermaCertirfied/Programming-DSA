/*  Create two classes :
    1. Node 
    2. Linked List - it should have these methods:
        2.1 create
        2.2 print all 
        2.3 print k the item
*/

#include<iostream>
#include<vector>
using namespace std;

class Node{
    public:
        int val;
        Node *next;

        Node(int val = -1, Node *next=NULL){
            this->val = val;
            this->next = next;
        }
};

class LinkedList{
    public:
        Node *head;

        LinkedList(Node *head=NULL){
            this->head = head;
        }

        Node *createLinkedList(vector<int> &arr){
            Node *last = NULL;
            for(int i=0; i<arr.size(); i++){
                Node *temp = new Node(arr[i], NULL);
                if(this->head == NULL){
                    this->head = temp;
                    last = temp;
                }
                else{
                    last->next = temp;
                    last = temp;
                }
            }
            return this->head;
        }

        void printLinkedList(){
            cout<<endl<<"Printing Linked List"<<endl;
            Node *fast = this->head;
            while(fast){
                cout<<fast->val<<" ";
                fast = fast->next;
            }
            cout<<endl;
            return;
        }

        int printKth(int k){
            cout<<endl<<"Printing kth : "<<k<<" item"<<endl;
            if(this->head == NULL || k==0)
                return -1;
            Node *fast = NULL;
            for(int i=0; i<k; i++){
                if(i==0)
                    fast = head;
                else{
                    if(fast->next)
                        fast = fast->next;
                    else
                        return -1;
                }
            }
            cout<<fast->val;
            return fast->val;
        }
};

int main(){
    vector<int> arr;
    for(int i=1; i<=5; i++) 
        arr.push_back(i);
    LinkedList *myLL = new LinkedList();
    myLL->createLinkedList(arr);
    myLL->printLinkedList();
    
    int tests[] = {0,1,3,5,6,7};
    for(int i=0; i<6; i++){
        myLL->printKth(tests[i]);
        cout<<endl;
    }
    
    return 0;
}