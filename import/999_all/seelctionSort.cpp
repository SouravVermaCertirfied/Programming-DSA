#include <iostream>
using namespace std;

int size = 10;

void printarr(int *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void selectionSort(int *arr, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] > arr[i])
            {
                swap(arr[i], arr[j]);
            }
        }
    }
}

void insertionSort(int *arr, int size){

}


void bubbleSort(int *arr, int size){
    
}

int main()
{
    int arr[] = {5, 2, 8, 3, 1, , 4, 0, 6, 7, 9};
    printarr(arr, 7);
    selectionSort(arr, size);
    printarr(arr, 7);
}