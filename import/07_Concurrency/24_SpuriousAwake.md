# spurious wakeup

A spurious wakeup happens when a thread that is waiting on a condition variable, wakes up even though no thread signaled it and the condition it was waiting for is still false.

In other words:
> The thread wakes up for no logical reason.

😵‍💫 **“But why would that ever happen?”**  
Because POSIX allows it.  

**BAD CODE**
```c
/*
Scenario:
    fuel == 10
    Thread waits
    Spurious wakeup happens
    Thread continues
    fuel -= 45 → negative fuel
    💥 Logic broken.
*/
pthread_mutex_lock(&lock);
if (fuel < 45) {
    pthread_cond_wait(&cond, &lock);
}
fuel -= 45;   // 💥 fuel might still be < 45
pthread_mutex_unlock(&lock);

```

**CORRECT CODE**  
```c
/*
Why while?
Re-checks the condition
Handles:
spurious wakeups
multiple waiting threads
race conditions
*/
pthread_mutex_lock(&lock);
while (fuel < 45) {
    pthread_cond_wait(&cond, &lock);
}
fuel -= 45;
pthread_mutex_unlock(&lock);

```