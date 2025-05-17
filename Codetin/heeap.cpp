#include<iostream>
#include<vector>
using namespace std;

class Heap{
    public:
	int capacity = 100;
	int values[100];
	int heapsize = 0;
	
	int parentIdx(int i){
	    int ans = (i-1)/2;
	    return ans;
	}
	
	int leftChildIdx(int i){
	    return (2*i + 1);
	}
	
	int rightChildIdx(int i){
	    return (2*i + 2);
	}
	
	Heap(vector<int> inputs){
		for(int i=0;i<inputs.size();i++){
			values[i] = inputs[i];
			heapsize++;
		}
	}
	
	void minheapifyme(int idx){
		
		if(idx<=0 || values[idx] < values[leftChildIdx(idx)] && values[idx] < values[leftChildIdx(idx)] ){
		    return ;
		}
		else{
		    for(int i=idx; i>=0 ;i--){
		        if(values[i] > values[parentIdx(i)]){
		            swap(values[i], values[parentIdx(i)]);
		        }
		    }
		}
	}
	
	void printheap(){
		for(int i=0; i<heapsize; i++){
			cout<<values[i]<<" ";
		}
		cout<<endl;
	}
};

int main(){
	vector<int> inputs = {1, 2, 3, 4, 5, 6, 7};
	Heap *heap = new Heap(inputs);
	heap->printheap();
	heap->minheapifyme(6);
	heap->printheap();
	
}