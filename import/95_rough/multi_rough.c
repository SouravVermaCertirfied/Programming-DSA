/*
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = NULL;
    }
};
*/

class Solution {
  public:
    Node* intersectPoint(Node* head1, Node* head2) {
        //  Code Here
        /* optimal approch*/
        int len1 = 0;
        int len2 = 0;
        Node * ptr1 = head1;
        Node * ptr2 = head2;
        while(ptr1 || ptr2){
            if(ptr1){
                len1++;
                ptr1 = ptr1->next;
            }
            if(ptr2){
                len2++;
                ptr2 = ptr2->next;
            }
        }

        ptr1 = head1;
        ptr2 = head2;

        if(len1 > len2){
            int diff = len1 - len2;
            while(diff){
                ptr1 = ptr1->next;
                diff--;
            }
        }
        else{
            int diff = len2 - len1;
            while(diff){
                ptr2 = ptr2->next;
                diff--;
            }
        }

        while(ptr1){
            if(ptr1 == ptr2){
                return ptr1;
            }
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        return NULL;
        
    }
};