This summary distills our deep dive into C memory management, specifically focusing on how strings, structs, and pointers interact.

---

## 🚀 Critical to Know

* **String Literals are Read-Only:** A string defined as `"text"` lives in the constant data segment. You can point to it, but you cannot change its characters.
* **Arrays vs. Pointers:**
* `char name[10]` is a **container**. The memory is inside your struct.
* `char *name` is a **label**. It only holds an address; the data lives elsewhere.


* **Deep vs. Shallow Copy:**
* **Shallow:** Copying the pointer address. Both objects share the same string.
* **Deep:** Allocating new memory and copying the string content. Both objects are independent.


* **The `sizeof` Trap:** `sizeof(pointer)` returns the size of the address (4 or 8 bytes), while `strlen()` returns the actual number of characters. Always use `strlen() + 1` for `malloc`.

---

## 🛠️ Memory Styles Comparison

### Stack Style (Fixed Array)

Memory is allocated automatically inside the struct.

```c
typedef struct {
    int rollno;
    char name[10]; // Data is INSIDE the struct
} Person;

// Deep copy happens automatically with assignment
Person p2 = p1; 
// In-place modification is safe
p1.name[0] = 's'; 

```

### Heap Style (Dynamic Pointer)

Memory must be manually managed using `malloc` and `free`.

```c
typedef struct {
    int rollno;
    char *name; // Struct only holds an ADDRESS
} Person;

// Manual Deep Copy required
p2.name = (char *)malloc(strlen(p1.name) + 1);
strcpy(p2.name, p1.name);

```

---

## ❓ FAQ

### Are array names not pointers?

Not exactly. An array name is the identifier for a block of memory. It **decays** into a pointer (gives you the address of the first element) when used in expressions, but you cannot reassign an array name to point elsewhere like you can with a pointer variable.

### Does `memcpy` do a shallow or deep copy?

It depends on your struct. If your struct contains a `char name[10]`, `memcpy` performs a **Deep Copy** because the data is physically inside the block being copied. If it contains a `char *name`, `memcpy` performs a **Shallow Copy** because it only copies the memory address.

### Can I not update the value of "verma" to "sharma" in-place?

If `name` points to a string literal (`char *n = "verma"`), **no**. That memory is protected by the OS. To modify in-place, the string must be stored in an array or a `malloc`’d heap buffer.

### What if I want to be able to modify in-place `p1.name` as well?

You must ensure `p1.name` isn't pointing to a literal. You do this by allocating memory for it immediately upon creation:

```c
p1.name = (char *)malloc(strlen("verma") + 1);
strcpy(p1.name, "verma");
p1.name[0] = 's'; // Now this is safe!

```

### Why did `sizeof(*s->name)` fail in my copy function?

`s->name` is a pointer. `*s->name` is the first character of the string. Therefore, `sizeof(*s->name)` is always `1` (the size of a `char`). It does not represent the length of the string.

---

## ⚠️ Summary of Modifications

| Operation | String Literal (`char *`) | Stack Array (`char[]`) | Heap (`malloc`) |
| --- | --- | --- | --- |
| **In-place Modify** | ❌ Segfault | ✅ Yes | ✅ Yes |
| **Reassign Pointer** | ✅ Yes | ❌ No | ✅ Yes |
| **Manual Free** | ❌ No | ❌ No | ✅ Yes |

Was there a specific part of the Stack vs. Heap logic you'd like to dive deeper into next?

---
<div style="display: flex; justify-content: space-between;">
    <a href="24_Arrays.md">← 24_Arrays.md</a>
    <a href="25_tips.md">25_tips.md →</a>
</div>