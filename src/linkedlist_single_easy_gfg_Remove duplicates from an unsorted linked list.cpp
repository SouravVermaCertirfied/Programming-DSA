// { Driver Code Starts
#include <bits/stdc++.h>
using namespace std;

struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};

void print(Node *root)
{
Node *temp = root;
while(temp!=NULL)
{
cout<<temp->data<<" ";
temp=temp->next;
}
}


 // } Driver Code Ends
/*
The structure of linked list is the following

struct Node {
  int data;
  struct Node *next;
  Node(int x) {
    data = x;
    next = NULL;
  }
};
*/


class Solution
{
    public:
    //Function to remove duplicates from unsorted linked list.

    Node * removeDuplicates( Node *head)
    {
     // your code goes here
     if(head==NULL){
         return head;
     }
     Node * loc = head;
     Node * ploc = NULL;
     unordered_map<int, bool> umap;
     while(loc!=NULL){
         if (umap.find(loc->data) == umap.end()){
             umap[loc->data] = true;
             ploc = loc;
             loc = loc->next;
         }
         else{
             ploc->next = loc->next;
             loc = loc->next;
         }
     }
     return head;
    }
};


// { Driver Code Starts.

int main() {
	// your code goes here
	int T;
//	cin>>T;
	T = 1;
	while(T--)
	{
		int K;
//		cin>>K;
		K = 7;
		int arr[] = {5,2,2,3,3,4,4};
		struct Node *head = NULL;
        struct Node *temp = head;

		for(int i=0;i<K;i++){
		int data;
//		cin>>data;
		data = arr[i];
			if(head==NULL)
			head=temp=new Node(data);
			else
			{
				temp->next = new Node(data);
				temp=temp->next;
			}
		}

	    Solution ob;
		Node *result  = ob.removeDuplicates(head);
		print(result);
		cout<<endl;

	}
	return 0;
}  // } Driver Code Ends
