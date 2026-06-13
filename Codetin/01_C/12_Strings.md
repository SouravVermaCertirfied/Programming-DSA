# Strings
- Supported in c via header `string.h`

## String input from console
For taking a string input from user from console/terminal.  
Following methods can be used:  
- `fgets` is the recommmend way of string input.

| **Method**                    | **Syntax / Example**                                | **Input Behavior**                                                      | **Pros**                                      | **Cons / Warnings**                                                                 |
| ----------------------------- | --------------------------------------------------- | ----------------------------------------------------------------------- | --------------------------------------------- | ----------------------------------------------------------------------------------- |
| **`scanf("%s", str)`**        | `c char str[100]; scanf("%s", str); `               | Reads input **up to first whitespace** (space, tab, newline).           | Simple and commonly used for single words.    | Cannot read spaces; risk of buffer overflow if input exceeds array size.            |
| **`fgets(str, size, stdin)`** | `c char str[100]; fgets(str, sizeof(str), stdin); ` | Reads **entire line including spaces** until newline or `size-1` chars. | Safe, prevents buffer overflow; reads spaces. | Includes newline `\n` if input fits; may need to remove it manually.                |
| **`gets(str)`**               | `c char str[100]; gets(str); `                      | Reads a line until newline.                                             | Simple syntax.                                | **Unsafe!** Can cause buffer overflow. Removed from modern C standards.             |
| **`scanf("%[^\n]", str)`**    | `c char str[100]; scanf("%[^\n]", str); `           | Reads input **until newline**, includes spaces.                         | Can read full line like `fgets`.              | Still unsafe (no length check); newline remains in buffer, may need extra handling. |


### using `fgets`
- This can accept a buffer of string from user
- including space and tabs whitespaces


### using `scanf`

---
<div style="display: flex; justify-content: space-between;">
    <a href="11_Structure.md">← 11_Structure.md</a>
    <a href="14_strcpy_strcmp.md">14_strcpy_strcmp.md →</a>
</div>