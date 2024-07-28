#include<iostream>
#include<string.h>

using namespace std;

bool isPalindromeTwoPointerApproch(char input[], int size){
    bool ans = true;
    int left = 0;
    int right = size-1;

    while(left<right){
        if(input[left++]!=input[right--]){
            ans = false;
            break;
        }
    }
    return ans;
}

int main(){
    char input1[8] = "Souravv";
    char input2[8] = "aja";
    int size = strlen(input1);
    cout<<"Length of the string is : "<<size<<endl;
    isPalindromeTwoPointerApproch(input1, size) ? cout<<"Palindrome" : cout<<"Not a Palindrome";
    return 0;
}