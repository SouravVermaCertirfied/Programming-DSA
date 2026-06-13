# Example 1: User-Defined Exceptions ( without using `exception` class)

Problem Statement: We want to calculate the average of an array.   
However, if:  
The array size is zero, an exception for "Array Size Zero" must be thrown.  
The array size is negative, an exception for "Array Size Negative" must be thrown.  
We can implement this using two user-defined exception classes.

<details><summary>Code here</summary>

```cpp
#include<iostream>
using namespace std ;

class arraySizeZero {};
class arraySizeNegative {};

int average(int arr[], int n)
{
    if(n == 0)
        throw arraySizeZero();
    if(n < 0)
        throw arraySizeNegative();
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum = sum + arr[i];
    int res = sum/n;
    return res;
}
int main()
{
    int n; 
    cin >> n;
    int arr[n];
    for(int i = 0; i < n; i++)
        cin >> arr[i];
    try 
    {
        int res = average(arr, n);    
        cout << res;
    }
    catch (arraySizeNegative &e1)
    {
        cout << "Array Size Negative"; // Handle negative size exception
    }
    catch (arraySizeZero &e2)
    {
        cout << "Array Size Zero";   // Handle zero size exception
    }
    cout << "\nBye\n";
    
    return 0 ;
}
```
</details>

---

# Example 2: User-Defined Exception Using the `exception` Class
We want to create a custom `exception` class by inheriting from the standard exception class. This allows us to override the `what()` function to provide a custom error message.

<details><summary>Code here</summary>

```cpp

#include <iostream>
#include <exception>
using namespace std;

// Custom Exception Class
class MyException : public exception {
    virtual const char *what() const throw() {
        return "Exception Occurred";  // Custom error message
    }
};

int main() {
    try {
        throw MyException();  // Throwing an object of MyException
    } 
    catch (exception &e) {
        cout << e.what() << endl;  // Catching and printing the error message
    }
    return 0;
}

```
</details>

---
<div style="display: flex; justify-content: space-between;">
    <a href="04_ExceptionHandling.md">← 04_ExceptionHandling.md</a>
    <a href="05_SmartPointers.md">05_SmartPointers.md →</a>
</div>