#include <iostream>
#include<vector>
using namespace std;

class Node{
    public:
        int val;
        Node *next;
    
        Node(int val){
            this->val = val;
            this->next = NULL;
        }
};

class MyLL{
    private:
        Node *head = NULL;
    public:
        Node *getHead(){
            return head;
        }
        Node *createLL(vector<int> &arr){
            Node *last = NULL;
            for(int i=0; i<arr.size();i++){
                Node *temp = new Node(arr[i]);
                if(head==NULL){
                    head = temp;
                    last = temp;
                }
                else{
                    last->next = temp;
                    last = temp;
                }
            }
            return head;
        }

        Node *reverseLL(Node *head){
            if(head==NULL || head->next == NULL)
                return head;
            Node *ptr = head;
            Node *last = NULL;
            Node *temp;
            while(ptr!=NULL){
                temp = ptr->next;
                ptr->next = last;
                last = ptr;
                ptr=temp;
            }
            return last;
        }

        Node *printLL(Node *head){
            Node *ptr = head;
            if(head==NULL){
                cout<<"Empty list"<<endl;
                return head;
            }
            cout<<endl;
            while(ptr!=NULL){
                cout<<ptr->val<<" ";
                ptr=ptr->next;
            }
            cout<<endl;
            return head;
        }
};

int main() {
    vector<int> input;
    for(int i=0;i<10; i++)
        input.push_back(i);
    MyLL *ll = new MyLL();
    Node *head  = ll->createLL(input);
    ll->printLL(head);
    head = ll->reverseLL(head);
    ll->printLL(head);
    cout << "Hello Geek!";
    return 0;
}