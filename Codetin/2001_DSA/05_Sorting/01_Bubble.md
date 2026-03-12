##  Bubble Sort

Swaps adjecent elements if the order is wrong.

#### Key Points:
- <span style="color: red;">Each pass moves the largest unsorted element to its correct position - the largest element bubbles out!</span>
- Compares **arr[j]>arr[j+1]**.
- **+1**th index is being compared
- Note the limits for outter and inner loops.

**Bubble sort without optimizatoin**
```c
void myBubbleSort(int *arr, int size){
    
    for(int i=0; i<size-1; i++){
        for(int j=0; j<size-i; j++){
            if(arr[j]>arr[j+1])
                swap(arr[j], arr[j+1]);
        }
    }
}
```
**Bubble sort with optimization**
```c
void myBubbleSort(int *arr, int size){
    bool swapped = true;
    for(int i=0; i<size-1; i++){
        swapped = false;
        for(int j=0 ; j<size-i; i++){
            if(arr[j]>arr[j+1]){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(swapped==true)
            break;
    }
}
```

***Modified bubble sort to compare based on user function***
```c

typedef bool (*CompareFunc(int, int));

bool ascending(int a, int b){
    return a>b;
}

bool decending(int a, int b){
    return b>a;
}

void myBubbleSortc(int *arr, CompareFunc compare){

    bool swapped;
    for(int i=0; i<size-1; i++){
        swapped = false;
        for(int j=0; j<size-i; j++){
            if(compare(arr[j], arr[j+1])){
                swap(arr[j], arr[j+1]);
                swapped = true;
            }
        }
        if(swapped==false)
            break;
    }
}

// function calling
int main(){
    myBubbleSortc(arr, 10, ascending);
    myBubbleSortc(arr, 10, decending);
    return 0;
}
```
**Calling Functions**

```c
void swap(int *first, int *last){
    int temp = *first;
    *first = last;
    *last = temp;
}
```
```c
int main(){
    int arr[] = {5, 8, 2, 10, 6}
    int size = sizeof(arr);
    bubble_sort(arr);
}
```
