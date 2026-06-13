## Questions

### 1. The volatile const Paradox : Can a variable be both `const` and `volatile` ?   

Answer: Yes, a variable can be both.  
Scenario: A Hardware Status Register.  
Explanation: `const` tells the compiler that the programmer should not attempt to modify the value (the register is read-only). `volatile` tells the compiler that the value can change outside of the program's control (the hardware updates it). This prevents the compiler from optimizing out repeated reads to that memory address.


###

---
<div style="display: flex; justify-content: space-between;">
    <a href="04_StorageClasses.md">← 04_StorageClasses.md</a>
    <a href="05_TypeQualifiers.md">05_TypeQualifiers.md →</a>
</div>