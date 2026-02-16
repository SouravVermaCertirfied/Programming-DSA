#   

- Pick the second element.
- compare to the elements to the left
- if there are elements who are found greater than that element, move then right to make place to **'insert'** the picked element
- after the insert the **'picked'** element is ensure to have all right greater than it, and all left smaller than it. in other words the 'picked' element has been put to its correct place.

**Code**
```c
void myInsertionSort(int *arr, int size) {
    for (int i = 1; i < size; i++) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

```
<details>
<summary><span><strong>Main Functions</strong></span></summary>

```c
void printArr(int *arr, int size){
    for(int i=0; i<size; i++){
        printf("%d ",arr[i]);
    }
}

void myswap(int *a, int *b){
    int t = *a;
    *a = *b;
    *b = t;
}

int main(){
    int arr[] = {7, 5, 1 , 9 , 3};
    myInsertionSort(arr);
    printArr(arr);
    return 0;
}
```

</details>





