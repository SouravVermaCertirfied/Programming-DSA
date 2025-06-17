# Datatypes

`Declaration`  
The compiler does not generate instructions to 

## C Data Types - Signed Variants

| Data Type        | Size (Bytes) | % | Range Lower                                  | Range Upper                                 |
|------------------|--------------|--------|----------------------------------------------|---------------------------------------------|
| `char`           | 1            | `c` | -128                                         | 127                                         |
| `short`          | 2            | `s` | -32,768                                      | 32,767                                      |
| `int`            | 4            | `d` | -2,147,483,648                               | 2,147,483,647                               |
| `long`           | 4 or 8       | `l` | -2,147,483,648                               | 2,147,483,647 (4 bytes) or -9,223,372,036,854,775,808 | 9,223,372,036,854,775,807 (8 bytes) |
| `long long`      | 8            | `ll` | -9,223,372,036,854,775,808                   | 9,223,372,036,854,775,807                   |
| `float`          | 4            | `f` | -1.2E-38                                     | 3.4E+38                                     |
| `double`         | 8            | `d` | -2.2E-308                                    | 1.8E+308                                    |
| `long double`    | 8 or 16      | `ld` | -3.4E-4932                                   | 1.1E+4932                                   |

---

## C Data Types - Unsigned Variants

| Data Type             | Size (Bytes) | Range Lower  | Range Upper                                 |
|-----------------------|--------------|--------------|---------------------------------------------|
| `unsigned char`       | 1            | 0            | 255                                         |
| `unsigned short`      | 2            | 0            | 65,535                                      |
| `unsigned int`        | 4            | 0            | 4,294,967,295                               |
| `unsigned long`       | 4 or 8       | 0            | 4,294,967,295 (4 bytes) or 0               | 18,446,744,073,709,551,615 (8 bytes) |
| `unsigned long long`  | 8            | 0            | 18,446,744,073,709,551,615                  |
| `unsigned float`      | 4            | 0            | Same as signed `float`, but only positive values |
| `unsigned double`     | 8            | 0            | Same as signed `double`, but only positive values |
| `unsigned long double`| 8 or 16      | 0            | Same as signed `long double`, but only positive values |

---

#### Notes:
- The size and ranges of types like `long`, `long long`, and `long double` can vary depending on the platform and the specific compiler used.
- The `float`, `double`, and `long double` types are typically used for floating-point numbers, but their ranges are quite broad and they can also represent both positive and negative values.

## Fixed data size.
- Use `#include <stdint.h>` to for fixed sizes.  
- This has these data types:  
`int8_t` , `int16_t` , `int32_t` and `int64_t`  
They all also have unsigned, prefixed with `u-`

<br>

# Special Data Types
- `size_t`
- `ptrdiff_t`

## `size_t`
- Defined in `stdio.h` and `stddef.h`
- it is the standard return type, returned by `sizeof` operator.
- It is gaurenteed to be big engough to be able to store size of biggest datatype / object of in the program.
- Underneath it is actually something like a `unsigned int`, `unsigned long`, or `unsigned long long` based on the system.
- Functions like printf use `%zu` to print size_t values.
- %zu tells printf to expect a size_t argument.
