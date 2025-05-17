#include <iostream>

using namespace std;

/* Problem: 
   Approch: 
   TC :             SC:    */
class MyStack{
    private:
        int const defaultCapacity = 100;
        int currentCapacity = defaultCapacity;
        int top = -1;
        int *arr = (int*)calloc(defaultCapacity, sizeof(int));
        
    public:
        myStack(int *inputs, int size){
            for(int i=0; i<size; i++){
                pos++;
                arr[pos] = inputs[i];
            }
        }
        int getSize(){
            return currentCapacity;
        }

        int getTop(){
            return top;
        }

        int push(int val){
            if(top < currentCapacity-1){
                pos++;
                arr[pos] = val;
            }
            return pos;
        }

        int pop(){
            return arr[--pos];
        }

        int peek(){
            return arr[pos];
        }

        int printStack(){
            for(int i=0; i<=top;i++){
                printf("%d ",arr[i]);
            }
            printf("\n");
        }



}
int main() {
    int inputs[] = {1, 2, 3, 4, 5};
    MyStack mystack = new MyStack(inputs);
    return 0;
}