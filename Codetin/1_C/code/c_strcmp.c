/*
Strcmp is used to compare two strings and return 
0 means the are same
-ve means str1 is lexographically smaller than str2
+ve means str2 is lexographically larger than str2

eg. 'A' is considered lesser than 'a'
*/

int custom_strcmp(const char* str1, const char* str2){
    int ans = 0;
    char *ptr1 = str1;
    char *ptr2 = str2;
    int len1 = 0;
    int len2 = 0;
    
    return 0;

}

#include<stdio.h>
#include<string.h>

int main(){
    const char *str1 = "apple";
    const char *str2 = "banana";
    
    int ans = strcmp(str1, str2);
    printf("ans is : %d", ans);

}