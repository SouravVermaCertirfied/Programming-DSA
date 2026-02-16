//{ Driver Code Starts
#include <bits/stdc++.h>
using namespace std;


// } Driver Code Ends

class Node{
    private:
        int key;
        int val;
        Node *next;
    public:
        Node(int key, int val){
            this->key = key;
            this->val = val;
            this->next = NULL;
        }
};

class LRUCache {
  private:
    int cap;
    Node *head;

  public:
    LRUCache(int cap) {
        // code here
        this->cap = cap;
        this->next = NULL;
    }

    int get(int key) {
        // code here - find and move to front
        // find the key, if it is found return the value and move the item to head
        // if not found return -1

    }

        
    void put(int key, int value) {
        // code here
        //if there is capacity insert to the head
        //if it is full
    }
};


//{ Driver Code Starts.

int main() {
    int t;
    cin >> t;
    while (t--) {

        int capacity;
        cin >> capacity;
        LRUCache *cache = new LRUCache(capacity);

        int queries;
        cin >> queries;
        while (queries--) {
            string q;
            cin >> q;
            if (q == "PUT") {
                int key;
                cin >> key;
                int value;
                cin >> value;
                cache->put(key, value);
            } else {
                int key;
                cin >> key;
                cout << cache->get(key) << " ";
            }
        }
        cout << endl;
        cout << "~" << endl;
    }
    return 0;
}

// } Driver Code Ends