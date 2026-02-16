# Selection

- The approch is to **'select'** and item in the array
- Then traverse through the right side of the array to find the index of the smallest element
- At the end if the a **'smaller'** item is found than the **'selected'** item 
- Then the smaller and the selected items are swapped.


```c
void mySelectionSort(int *arr, int size){

    int smallestIdx;
    for(int i=0; i<size-1; i++){
        smallestIdx = i;
        // find the min in the unsorted array right to the 'selected' item
        for(int j=i+1; j<size; j++){
            if(arr[j]<arr[smallestIdx]){
                smallestIdx = j;
            }
        }
        // swap the 'selected' item with the smallest found item
        if(smallestIdx!=i){
            myswap(&arr[i], &arr[smallestIdx]);
        }
    }
}
```
<details>
<summary></strong>Main Function</strong></summary>

```c
void myswap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void printArr(int *arr, int size){
    for(int i=0; i<size; i++)
        printf("%d ",arr[i]);
}

int main(){
    int arr[] = {5, 8, 1, 3, 9};
    mySelectionSort(arr, 5);
    printArr(arr, 5);
}

```
</details>