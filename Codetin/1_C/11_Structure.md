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
