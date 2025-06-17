# Functions

1. Passing funtions
2. Passing array
3. Passing string to a function
4. Call by value and by reference

## 1. Passing a function to a function
- <span style="color:red;">Function pointers must match exactly in parameter and return types in C, as it does NOT support function overloading.</span>
- You can’t pass a 3-parameter float-returning function to a function expecting a 2-parameter int-returning one


```c
#include<stdio.h>

int add(int a, int b){
    return a+b;
}

int sub(int a, int b){
    return a-b;
}

int operate(int a, int b, int(*fun)(int, int)){
    return fun(a,b);
}

int main(){
    int a = 10;
    int b = 20;
    int ans = operate(a, b, add);
    printf("%d ",ans);
    int bns = operate(a, b, sub);
    printf("%d ",bns);
    return 0;
}
```

## 2. Passing array to a function

```c
    #include<stdio.h>

    int foo(int arr[], int *brr){
        arr[0] = 100;
        brr[1] = 200;
    }
    void printarr(int *arr){
        for(int i=0; i<3; i++)
            printf("%d ",arr[i]);
    }
    int main(){
        int arr[] = {1,2,3};
        foo(arr,arr);
        printarr(arr);
    }
```

## 3. Passing string to a function

```c
#include<stdio.h>

void foo(char *str, char jtr[]){
    printf("%s", str);
    str[0] = 'a';
    jtr[1] = 'b';
}

int main(){
    char name[] = "verma";
    foo(name, name);
    printf("\n%s", name);
    return 0;
}
```
**Output**
```
verma 
abrma
```

## 4. Call by value vs Call by Reference

```c
#include<stdio.h>
void foo(int byVal, int *byRef){
    byVal = 1;
    *byRef = 1;
}

int main(){
    int a = 10;
    int b = 20;
    printf("%d %d\n",a,b);
    foo(a,&b);
    printf("%d %d",a,b);
    return 0;
}
```
**Output**
```
10 20
10 1
```

