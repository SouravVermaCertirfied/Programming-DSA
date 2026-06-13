# Structure
- Padding
- Use of ` . ` operator during intiaiziation

## 1. `.` operator for initialization
- This is a **designated initializer**, where each field of the struct is explicitly initialized by name using the `.` operator.
- This makes initilization order independent.
- **Example**
```c
struct car{
    int vin;
    char name[10];
};

int main()
{
    struct car c1 = {1,"mustang" }; // normal
    struct car c2 = {.vin = 1, .name = "roadster"}; // with desginated initializer.
}
```

## 2. Initialization
- After the declaration compound init is not allowed in c
- there is another way to achive this C99 onwards, using explicit typecasting.
```c
struct car{
    int vin;
    char name[10];
};

int main(){

    struct car c1 = {1,"mustang" }; // ALLOWED

    struct car c2;
    c2 = {.vin = 1, .name = "roadster"}; // NOT ALLOWED. as init should be done in the declaration line itself

    c2 = (struct car){.vin = 1, .name = "roadster"}; // ALLOWED, with explicit typecasting
}
```

## 3. Structure Padding
Structure padding refers to **insertion of extra bytes between members of the `struct` to ensure each member is aligned**.  
This can affect the overall `sizeof` the structure.  

### Why padding is done by the compiler ?
CPU can access memory in fixed chunks of blocks,  
if the variable values are spread accross multiple blocks it has write more instructions to fetch/write to those variable, hence making it slower.  
Usually compiler tries to allocate memory to multiples of 4 for `int` and multipes of 8 for `double`. And tries to put the stqrting address at the starting of the block. For `char` there is no aligned required.

Eg:  
```c
struct car{
    char id;    // 1 byte + 3 bytes padding
    int vin;    // 4 bytes + 0 bytes padding
    char code;  // 1 byte + 3 bytes padding
}

printf("%d", sizeof(car));// this will be 12 bytes
```

### How to supress Padding ?
It can be done using `pragma`.  
```c
struct __attribute__((packed)) car{

};
```
Also, this format can be used:
```c
#pragma (push,1) // this forces aligned to 1 byte (ie No Padding)
struct car{

};
#pragma (pop) // this restores to previous packing
```

## 4. Nesting a `struct`
- `struct` nesting in not valid in C, compile time error.
- Eg: you cannot create an object of `struct foo` inside `struct foo`.
- Because doing this would lead to infine memory requirement, evey object has an object inside it and it runs perpetually.
- Hence, we use pointer becuase it has fixed size (`sizeof(anytype)`) is constant for a machine. eg 64 bits for a 64 bit machine.
```c
struct Node{
    int x;
    struct Node  obj; // invalid
    struct Node *ptr; // valid
};
```

- **You can create object of any other `struct` inside a `struct`.**
- But, you cannot trick the compiler by using another `struct`.
- eg. `struct Node` can an object `struct Foo` as its member.
```c
struct Node; // forward declaration

struct Foo{
    int x;
    struct Node
};

struct Node{
    int y;
    struct Foo  obj; // invalid, compilation error
    struct Foo *ptr; // valid
};
```
Key rule in C:  
**A `struct` cannot contain another struct by value unless that struct’s full definition is already known.**
- At this point:
    - `struct Foo` is incomplete
    - The compiler does not know its size

To embed `struct Foo obj;`, the compiler must know:
- how big `Foo` is
- how to lay it out in memory
- But struct `Foo` is not fully defined yet → ❌ error.

---
<div style="display: flex; justify-content: space-between;">
    <a href="09_PointersQB.md">← 09_PointersQB.md</a>
    <a href="12_Strings.md">12_Strings.md →</a>
</div>