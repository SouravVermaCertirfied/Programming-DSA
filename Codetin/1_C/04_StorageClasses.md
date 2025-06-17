# Storage Classes in C

> They decide - ***memory*** where it will stored, ***scope*** of the variable and ***access*** of the variable.

- There are 4 storage classes
- `auto`, `register`, `static` and `extern`


### Summary

| Storage Class | Definition                                                                                                                             | Initial Value           | Scope                          | Lifetime        | Linkage           | <span style ="color:red;">Memory Location</span>                        | Usage with Functions                           |
| ------------- | -------------------------------------------------------------------------------------------------------------------------------------- | ----------------------- | ------------------------------ | --------------- | ----------------- | -------------------------------------- | ---------------------------------------------- |
| **auto**      | Default storage class for local variables; stored on stack, exists only within the block/function where declared.                      | Garbage (undefined)     | Local (block)                  | Block execution | None (no linkage) | Stack                                  | No                                             |
| **register**  | Suggests storing variable in CPU register for fast access; limited to local variables, cannot take address.                            | Garbage (undefined)     | Local (block)                  | Block execution | None (no linkage) | CPU Register (suggested)               | No                                             |
| **static**    | Preserves variable value between function calls (if local); limits visibility of global vars/functions to the file (internal linkage). | Zero (if uninitialized) | Local (block) or File (global) | Entire program  | Internal linkage  | Data Segment (BSS or initialized data) | Yes — limits function visibility to file scope |
| **extern**    | Declares variable/function defined elsewhere; provides external linkage allowing access across files.                                  | N/A                     | Global                         | Entire program  | External linkage  | Data Segment                           | Yes — declares function defined elsewhere      |


## 1. `auto`

- This is the default scope any variable/
- When nothing is written is `auto`.  
- Example 
    ```c
    void func(){
        auto int a = 10;
    }
    ```

## 2. `register`

- This ***requests*** the compiler to assign a register to these variables.
- It is a hind and not a command
- The request many not necessary be met.
- <span style="color: #854754;">Address cannot be accessed using <strong>&</strong> operator.</span> Attempt to do this will lead to compilation error.
    ```c
    void func(){
        register int a = 10;
        int *ptr = &a; // this wrong ! Compilation error!!
    }
    ```
- Also a pointer variable can be made as register variable, example below.
- **Use Case** example - say there is counter variable of the loop, which has to be accessed very frequently, it can be made as a register for faster processing.
    Example
    ```c
    void func(){
        register int idx = 0;
        register *ptr = &idx; // valid code

        while(idx<10000){
            // do something
            ptr++; 
        }
    }
    ```
 
<details>
<summary> Interview question : In a 32-bit machine, if you try to make a `double` variable as `register` scope. what will happen ?</summary>

- Answer
- Since it is 32-bit machine it cannot store 64-bits in a single register.
- Hence, it will _ignore_ the _hint_ to store in register and allocate memory in the stack
- There will be no compilation error.
</details>

## 3. `static`
- Can be used with both function and variable.
- Local variable : retains value between function calls, lifetime is entire program.
- Function : Limits scope to the file (internal linkage).
- Example:
    ```c
    static int fun1();
    static int svar;

    int main(){
        static int var1;
    }

    static int fun1(){
        return 0;
    }
    ```

## 4. `extern`
- Declared with a variable or a function.
- Does not allocate any new memory, just tells the compiler that this variable/function
is declared else where.
- Example:
    ```c
    extern int var1;
    extern int func1();
    ```