// { Driver Code Starts
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stack>
using namespace std;
/* Link list Node */
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};




 // } Driver Code Ends
/*
struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/

class Solution{
  public:
    //Function to check whether the list is palindrome.
    bool isPalindrome(Node *head)
    {
        //Your code here
        Node * loc = head;
        int mid = 0;
        int count = 0;
        stack <int> s;
        cout<<"Linked List"<<endl;
        while(loc!=NULL){
        	cout<<loc->data<<" ";
            loc = loc->next;
            count++;

        }
        cout<<"Count : "<<count<<endl;

        mid = (count/2);

        loc = head;
        int i = 0;
        while(i<mid){
        	s.push(loc->data);
            loc = loc->next;
            i++;
        }
        if((count&1) == 0x01){
            loc = loc->next;
        }
        while(loc!=NULL){
        	int value = s.top();
        	s.pop();
            if(loc->data != value){
                return false;
            }
            loc = loc->next;
        }
        return true;
    }
};



// { Driver Code Starts.
/* Driver program to test above function*/
int main()
{
  int T,i,n,l,firstdata;
//    cin>>T;
  	  T = 3;
  	  int arr[] = {4,7,5};
  	  int daa[][100] = {{1,2,3,1},{1,2,3,4,3,2,1},{5,4,3,4,5}};
    while(T)
    {

        struct Node *head = NULL,  *tail = NULL;
//        cin>>n;
        n = arr[T-1];
        // taking first data of LL
        firstdata = daa[T-1][0];
        head = new Node(firstdata);
        tail = head;
        // taking remaining data of LL
        for(i=1;i<n;i++)
        {
            l = daa[T-1][i];
            tail->next = new Node(l);
            tail = tail->next;
        }
    Solution obj;
   	cout<<obj.isPalindrome(head)<<endl;
   	T--;
    }
    return 0;
}

  // } Driver Code Ends
