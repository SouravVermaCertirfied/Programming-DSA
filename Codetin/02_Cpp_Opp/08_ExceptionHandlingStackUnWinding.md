# Stack Unwinding (related to Exception Handling)

Note: The local objects are destroyed in reverse order in which they were constructed.  

When an exception is thrown in C++, the program starts unwinding the stack to find a matching catch block.  
During this process:
- Functions in the call stack are popped off one by one.  
- The destructors of objects in these functions are executed to release resources.  
- If no matching catch block is found, the program terminates.

---
<p align="left"><a href="07_OverridingAndVirtualKeyword.md">← 07_OverridingAndVirtualKeyword.md</a></p>
<p align="right" style="margin-top:-2.4em;"></p>