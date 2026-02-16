## Bit Manipulation Tip

Subtle but common issue is shifting a 1 into the most significant bit (MSB) of a signed integer:
```c
int x = 1 << 31; // Undefined behavior
```
**Why is this a problem?**  
`int` is `signed`. Shifting 1 into the sign bit is undefined behavior according to the C standard.  
The code may compile without warnings, but at runtime it can produce unpredictable results—wrong values, crashes, or silent errors.  
✅ Correct approach: use unsigned integers for shifts that may reach the MSB:
```c
unsigned int x = 1U << 31; // Safe and well-defined
```

## Default Values struct
- you CANNOT initilize the default values for a `struct` in C.
- you CAN initilize the default values for a `struct` in CPP. Only for C++ v11 plus.
- you class you can always do it in, ofcorse in CPP.