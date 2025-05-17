#include<iostream>
using namespaces std;

#define TABLE_SIZE 11

class Node{
    private:
        int val;
        Node *next;
    public:
        Node(int val, Node *next=NULL){
            this->val = val;
            this->next = next;
        }
};

class Hastable{
    private:
        Node table[TABLE_SIZE];
    public:
        int hashFunction(int key){
            return (key%11);
        }

        int insert(int key){
            int index = hashFunction(key);
            Node *temp = new Node(key);
            if(table[index]==NULL){
                table[index] = temp;
            }
            else{
                Node *ptr = table[index];
                while(ptr->next!=NULL)
                    ptr = ptr->next;
                ptr->next = temp;
            }
        return index;
        }

        int search(int key){
            int index = hashFunction(key);
            if(table[index]==NULL)
                return -1;
            else{
                Node *ptr = table[index];
                while(ptr!=NULL){
                    if(ptr->val == key)
                        return index;
                    else
                        ptr = ptr->next;
                }
                
            }
            return -1;
        }

        int del(int key){
            if(search(key)==-1){
                return -1;
            }
            else{
                Node *ptr = table[index];
                Node *prev = NULL;
                while(ptr!=NULL){
                    if(ptr->val == key)
                        
                    else
                        ptr = ptr->next;
                }
            }
        }

};


int main(){
    Hastable ht;
    ht.insert(10);
    ht.insert(20);
    ht.search(50);
    ht.search(20);
    ht.delete(20);
    ht.search(20);
    return 0;
}