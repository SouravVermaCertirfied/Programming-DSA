/*
- KMP avoid rechecking the characters by preprocessing the array in LPS array.
- On mismatch, we jump to longest running prefix, giving linear time complexity.
- TC - O(p+s)    
- SC - 
KMP Mental Model:
        - Text poiner never moves backwards
        - Pattern pointer jumps intelligently





*/