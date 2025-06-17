# Multi-Threading in C `POSIX`

- header is `pthread.h`
- compiled using command `gcc -pthread your_program.c -o your_program`
- `pthread_create` is used to create a thread.  
- <span style="color:blue;"><strong> Use structures if more than one arguments have to be passed, as create thread accepts only one argument </strong></span>.  
    **Example**
    ```c
    pthread_create(&t1, NULL, thread_function, &args1);
    ```
    **Syntax**
    ```c
    int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine) (void *),
                   void *arg);
    ```
| Argument           | Purpose                                        | Usually Set As     |
| ------------------ | ---------------------------------------------- | ------------------ |
| `pthread_t *`      | Output: Thread ID                              | `&thread_id`       |
| `pthread_attr_t *` | Thread attributes (e.g., stack size, detached) | `NULL` for default |
| `void *(*)(void*)` | Thread function (entry point)                  | `your_function`    |
| `void *`           | Single argument to pass to the thread          | `&your_data`       |

## Simple `pthread`
```c
#include<pthread.h>
#include<stdio.h>

struct car{
    int vin;
    char name[10];
};

void *threadFunc1(void* input){
    int *inputs = (int*)input;
    printf("Inside thread func1, got input : %d \n",*inputs);
}


void *threadFunc2(void* input){
    struct car *inputs = (struct car*)input;
    printf("Inside thread func2, got input : %d and %s .\n",inputs->vin,inputs->name);
}

int main(){
    pthread_t t1;
    pthread_t t2;

    int input1 = 10;
    struct car c1 = {.vin = 20, .name="mustang"};
    pthread_create(&t1, NULL, threadFunc1, &input1);
    pthread_create(&t2, NULL, threadFunc2, &c1);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Ending main\n");

    return 0;
}
```

## Pooling using pthread

