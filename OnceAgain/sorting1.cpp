#include<iostream>
#include <cstdlib> // For rand() and srand()
#include <ctime>   // For time()
#include <chrono>

using namespace std;
const int size = 0xFFFF;

int *bubleSort(int *arr, int size){
	for(int i=0;i<size;i++){
		for(int j=i;size<7;j++){
			if(arr[j]<arr[i]){
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
	return 0;
}

int printArr(int *arr){
	for(int i=0;i<size;i++){
		cout<<arr[i]<<" ";
	}
	cout<<endl;
	return 0;
}
int main(){
	//srand(static_cast<unsigned int>(time(0)));
	auto start = std::chrono::high_resolution_clock::now();

	int arr[size];
	for(int i=0;i<size;i++){
		arr[i] = rand();
	}
	printArr(arr);
	bubleSort(arr, size);
	printArr(arr);
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Time taken: " << duration.count() << " seconds" << std::endl;
	return 0;
}
