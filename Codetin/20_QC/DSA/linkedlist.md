# Floyd’s Cycle Detection Algorithm (Tortoise and Hare). 

## Why the Slow and Fast Pointers Must Meet

Consider a linked list with a cycle:

```
             X                 Y
Head ------> Start ----------> Meeting Point
              ^                    |
              |                    |
              +--------------------+
                    Cycle length = C
```

Define:

**X** = distance from the head to the start of the cycle. **Y** = distance from the start of the cycle to the meeting point. **C** = length of the cycle.

---

### 1. Distance traveled when they meet

The slow pointer moves one node at a time.

By the time it meets the fast pointer, it has traveled: `D_{slow} = X + Y`

The fast pointer moves twice as fast, so it has traveled: `D_{fast} = 2(X+Y)`

But because the fast pointer is inside the cycle, it has also gone around the loop some number of times. Let that number be (k): `D_{fast} = X + Y + kC`

where (k \geq 1).

---

### 2. Use the speed relationship

Since the fast moves 2x the speed of slow.

```javascript
d_fast = 2 * d_slow
x + (k * c) + y = x + y
x = kc - y // solving for x
x = (k-1)c + (c-y) // rewriting the above equation

Interpreted as :
distance between the start to the start of the loop = (cycles made in the loop) + (distance remaining from the meeting point to the start point)
```


## 3. Why does this prove the second meeting happens at the cycle start?

The equation: `X=(k-1)C+(C-Y)` means:

* (X) is the distance from the **head** to the cycle start.
* (C-Y) is the distance from the **meeting point back to the cycle start**.
* ((k-1)C) represents complete loops around the cycle, which return a pointer to the same position.

So if:

1. One pointer starts at the **head**.
2. The other pointer starts at the **meeting point**.
3. Both move one step at a time.

Then:

* The head pointer travels (X) steps.
* The meeting pointer travels (C-Y) steps, plus possibly some full cycles.

Because: `X=(k-1)C+(C-Y)`

they must arrive at the same node: the **start of the cycle**.