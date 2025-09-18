# Structure
- Padding
- Use of ` . ` operator during intiaiziation

## `.` operator for initialization
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

## Initialization
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

## Structure Padding
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