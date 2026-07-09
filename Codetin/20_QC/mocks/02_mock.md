> **QC 8 YOE Firmware Engineer (Senior/Staff-track) 90-minute mock interview**. This is not a pure coding round.

Assumptions:

* Role: **Embedded Firmware Engineer / BSP / Device Driver / Low-level C**
* Experience: **8 years**
* Target: Qualcomm-style interview (SoC, ARM, RTOS, Linux kernel interface, debugging, performance, ownership)
* Format: I’ll give **all questions upfront** as requested.
* In an actual mock, you would answer one by one and I would cross-question like an interviewer.

# Qualcomm Firmware Engineer — 90 Minute Mock Interview

## Section 1: Resume Deep Dive & Project Ownership (10 min)

1. Walk me through your current project architecture. Draw the complete software stack from application layer to hardware.

2. What exactly was your ownership in your last project? What parts did you design vs maintain?

3. Describe the most difficult firmware bug you debugged. How did you narrow down the root cause?

4. Tell me about a performance optimization you implemented. What was the before/after measurement?

5. Describe a production issue that escaped testing. How did you fix it and prevent recurrence?

6. If I gave your last project codebase to another engineer, what areas would they struggle to understand?

7. How do you review firmware code written by another engineer?

---

# Section 2: Advanced C Programming (15 min)

8. Explain the difference between:

* `const int *p`
* `int * const p`
* `const int * const p`

9. What happens internally when you call:

```c
foo();
```

Explain stack changes, return address, registers involved.

10. Write your own implementation of `memcpy()`.

Follow-up:

* What happens if source and destination overlap?
* How will you optimize it for ARM?

11. Explain undefined behavior examples in C.

12. What is the output?

```c
int a = 10;

printf("%d %d %d",
       a,
       a++,
       ++a);
```

Why?

13. Explain memory layout of a firmware image:

* text
* rodata
* data
* bss
* heap
* stack

14. What happens if a stack overflow occurs in embedded firmware?

15. How do you detect memory corruption in a production device?

16. Explain:

* volatile
* memory barrier
* compiler barrier

17. Why is volatile not enough for thread synchronization?

18. Explain function pointers. Where have you used them in firmware?

19. Design a callback mechanism in C.

20. Explain structure padding and alignment.

Example:

```c
struct test {
    char a;
    int b;
    char c;
};
```

What is sizeof?

---

# Section 3: Embedded Systems Fundamentals (15 min)

21. Explain the boot sequence of a Qualcomm-based device.

22. Difference between:

* bootloader
* ROM code
* secondary bootloader
* kernel
* firmware

23. What happens after RESET pin assertion?

24. Explain interrupt handling flow.

25. Difference between:

* polling
* interrupt
* DMA

26. When would you choose polling over interrupt?

27. Explain DMA architecture.

28. CPU writes data to peripheral using DMA. What cache problems can occur?

29. Explain cache coherency issues.

30. Difference between:

* write-through cache
* write-back cache

31. Explain memory mapped IO.

32. How do you access a hardware register safely?

Example:

```c
#define REG (*(volatile uint32_t *)0x1000)
```

Is this enough?

33. What happens when two interrupts occur simultaneously?

34. Explain interrupt priority handling.

35. What should never be done inside ISR?

---

# Section 4: ARM Architecture (15 min)

36. Explain ARM Cortex-A vs Cortex-M differences.

37. Explain ARM exception levels:

* EL0
* EL1
* EL2
* EL3

38. What happens during a context switch?

39. Which registers must be saved?

40. Explain ARM pipeline.

41. What causes pipeline stalls?

42. Explain branch prediction.

43. Difference between:

* IRQ
* FIQ
* SVC
* abort

44. Explain MMU.

45. Difference between:

* virtual address
* physical address

46. Explain page tables.

47. What happens during a page fault?

48. Explain TLB.

49. How do you debug an ARM crash dump?

50. Explain ARM exception frame.

---

# Section 5: RTOS Concepts (10 min)

51. Which RTOS have you worked with?

52. Explain RTOS scheduler.

53. Difference between:

* task
* thread
* process

54. Explain priority inversion.

55. How do you solve priority inversion?

56. Mutex vs semaphore.

57. Binary semaphore vs counting semaphore.

58. What happens if ISR gives semaphore to waiting task?

59. Explain deadlock scenarios.

60. How do you debug RTOS timing issues?

61. Explain watchdog implementation.

62. How do you design a fault recovery mechanism?

---

# Section 6: Linux Kernel / Driver Questions (15 min)

63. Explain Linux boot flow on an embedded Qualcomm platform.

64. Explain Linux device driver architecture.

65. Difference between:

* kernel space
* user space

66. Explain system call flow.

67. Write the flow of:

```
open()
read()
write()
ioctl()
```

68. Explain character driver.

69. What happens when user calls ioctl?

70. Explain interrupt handling in Linux driver.

71. Difference between:

* top half
* bottom half

72. Explain:

* workqueue
* tasklet
* threaded IRQ

73. Explain device tree.

74. Why are device trees used?

75. Explain:

```dts
compatible = "vendor,device";
```

76. How does Linux match a driver with hardware?

77. Explain kernel memory allocation:

* kmalloc
* vmalloc

78. Explain kernel panic debugging.

79. How do you analyze:

```
Unable to handle kernel NULL pointer dereference
```

80. Explain Linux power management.

---

# Section 7: Qualcomm Specific Firmware Topics (10 min)

81. Describe Qualcomm boot architecture.

82. What Qualcomm SoCs have you worked with?

83. Explain:

* RPM
* RPMh
* TrustZone
* HLOS

84. Explain Qualcomm power management architecture.

85. What is SPMI?

86. Explain PMIC communication.

87. How would you debug a device failing to boot after PMIC change?

88. Explain DDR initialization flow.

89. How do you debug early boot failure before UART is available?

90. Explain Qualcomm crash dump collection.

91. What logs would you collect from a field failure?

92. How do you reduce firmware boot time?

---

# Section 8: Debugging Scenarios (10 min)

93. Device randomly resets after running for 5 hours. How do you debug?

94. Firmware works in debug build but fails in release build.

95. Device hangs only under heavy CPU load.

96. Interrupt latency suddenly increases.

97. Memory usage slowly increases over days.

98. UART logs stop printing randomly.

99. Firmware watchdog resets the device. How do you find the reason?

100. A driver works on one board revision but fails on another.

---

# Section 9: Coding Round (10 min)

101. Reverse a linked list.

102. Detect loop in linked list.

103. Implement circular buffer.

104. Implement producer-consumer queue.

105. Find first non-repeating character.

106. Implement bit manipulation:

Set bit N
Clear bit N
Toggle bit N
Check bit N

107. Count number of set bits.

108. Swap two integers without temporary variable.

109. Implement debounce logic for a button.

110. Design a firmware logging framework.

---

# Section 10: Senior Engineer Behavioral (5 min)

111. Why Qualcomm?

112. Why are you looking for a change?

113. Describe a disagreement with another engineer.

114. Tell me about a technical decision you made that was wrong.

115. How do you mentor junior engineers?

116. How do you handle ambiguous requirements?

117. How do you balance delivery pressure vs code quality?

118. What area of firmware do you want to become stronger in?

119. What would your manager say is your biggest strength?

120. What questions do you have for us?

---

## Interviewer Evaluation Criteria

I would score you on:

| Area                      | Weight |
| ------------------------- | ------ |
| C / C++ depth             | 20%    |
| Embedded fundamentals     | 15%    |
| ARM architecture          | 15%    |
| Linux/RTOS                | 20%    |
| Debugging ability         | 15%    |
| Qualcomm domain knowledge | 10%    |
| Communication/ownership   | 5%     |

For an **8 YOE Qualcomm firmware role**, strong candidates should be able to answer ~80% confidently and deeply explain trade-offs.

When you’re ready, start with **Question 1** and answer as if you are in the interview. I’ll act as the Qualcomm interviewer and drill down.
