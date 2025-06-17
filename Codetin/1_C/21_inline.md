# `inline`

- It is a **hint** to the compiler, compiler can ignore this request, it is not a guarantee.
- It hints the compiler, that **the function should be expanded** where it is being called.
- This is to avoid stack, push/pop, jump return.
- **Performace** : Reduces function call overhead.
- **Code Size** : 
    - For very small function : Can reduce overall code size as push-pop-return to stack instructions may not be required.
    - For bigger function : Can increase overall code size due to ***duplication***.
- when a function is made `inline`, ***compiler may not generate standalone code at all*** for it.  
<hr>

1. <span style="color:red;"><strong>'non inline'</strong></span>
    - for non-inline functions, standalone function defination is created
    - it has its linker symbol
    - and the called places link to the standalone code defination.

2. <span style="color:red;"><strong>'inline' only i.e. without 'extern' or 'static'</strong></span>
    - here the compiler creates a ***weak*** defination for the linker purpose only.
    - Compilers use “weak” linkage or “COMDAT” sections (in ELF and PE binaries) to mark inline definitions.
    - These weak definitions do not conflict with each other at link time. They’re only “placeholders” for the compiler’s optimizer to use for inlining.
3. <span style="color:red;"><strong>'static' with 'inline'</strong></span>
    - when 'stactic' is used with 'inline', there is no symbol created for the static function itself, hence you may not find any symbol for that function in the **linker file**.
    ```c
    // here symobls for fun1() and fun2(), will be created. 
    // but symbol for foo() will NOT be created.
    static inline int foo(){
        return 0;
    }
    int fun1(){
        foo();
    }
    int fun2(){
        foo();
    }
    ```
4. <span style="color:red;"><strong>'extern' with 'inline'</strong></span>
    - Usage of extern with inline is a very very tricky one.
    - It might/might not create a standalone defination for the liner purpose, it is compiler dependent and undeterministic. 
        - if the defination is present there may not be error, linker may be statified with the standalone defination.
        - if the definatoin is not present then there may be linker error.
    - Hence, it is better to avoid using extern with inline.

<hr>

***So when putting in hearder files, we should static inline. and avoid using extern inline. right ?***  
 Exactly — for embedded systems, especially when putting functions in header files, the best practice is:  
✅ **Use static inline in headers.**  
 - This gives internal linkage — each source file including the header gets its own copy.
 - Avoids linker errors due to multiple definitions.
 - Perfect for small utility functions, register accessors, bit twiddling — common in embedded.
 - Compiler can inline them freely, no risk of duplicate symbols.  
❌ **Avoid extern inline in headers unless you really know what you’re doing.**
- extern inline semantics are tricky and compiler-dependent (especially GCC vs MSVC).
- It can lead to linker errors if the external definition is missing.
- Rarely needed in embedded unless you want a single external function symbol with optional inlining.
