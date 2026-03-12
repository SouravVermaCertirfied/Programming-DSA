# Deadlock
- This is a condition where threads are **permanently** blocked, because each process is waiting for a resouce held by another, and hence none can proceed.
- For deadlock to occur, all FOUR Coffman's conditions should occur simultaneously. [Circular Wait, No Pre-Emption, Hold & Wait and Mutual Exculsion]

# Deadlock Handling
Below are the four approches that are used to deal with a deadlock.
- Deadlock Avoidance
- Deadlock prevntion
- Deadlock detection and recovery
- Deadlock Ignorance

## Deadlock Avoidance 
Use of deadlock avoidance techniques:
- **Algorithm based** : Eg Banker's Algorithm. Used when **multiple instance** of the resouce exist. It simulates allocation and ensures safe state for the system before allocating resource.
- **RAG (Resource Allocation Graphs)**: Used when each resource has only **one instance**, checks for cycles in the graph to avoid unsafe states.

## Banker's Algorithm
- **Banker’s Algorithm decides whether it’s safe to grant a request right now.**  
- Banker’s Algorithm is a deadlock-avoidance method used in operating systems. Before granting a resource request, the system checks whether doing so will keep the system in a safe state—meaning all processes can still finish execution in some order. It uses information about maximum resource needs, currently allocated resources, and available resources. If the request leads to an unsafe state, it is denied; otherwise, it is granted. 
- Points to note:
>- Safe ≠ deadlock-free forever  
>- Unsafe ≠ deadlock now  
>- Unsafe just means deadlock is possible

<details><summary><b>C code for classic Banker's Algorithm</b></summary>

```c
#include<stdio.h>
#include<stdlib.h>
#include<bool.h>

#define PRO 4u // no of process
#define RES 3u // no of resouces

int **bankerAlgo(allocated[PRO][RES], maximum[PRO][RES], available[RES]){
    int *ans = (int *)malloc(sizeof(int));
    /*
    1. Calculate Need Matrix
    2. 
    */
    int need[PRO][RES];
    for(int i=0; i<PRO; i++){
        for(int j=0; j<RES; j++){
            need[i][j] = maximum[i][j] - allocated[i][j];
        }
    }

    // finding the safe state
    bool deadlock = false;
    bool pending_tasks[PRO];
    for(int i=0; i<PRO; i++)    pending_tasks[i] = true;
    
    while(deadlock==false && pending_tasks > 0 ){
        for(int i=0; i<PRO; i++){
            safe = true;
            for(int j=0; j<RES; j++){
                if(available[i][j] < need[i][j] ){ // not safe
                    safe = false;
                    break;
                }
            }
            if(safe){
                ans[order++] = i;
                pending_tasks[]
            }
        }
        
    }


    return ans;
}

int main(){
    // allocation matrix, where each row=process & col=resource type
    int allocated[PRO][RES] = {{},{},{},{},{}};
    // max resouce, that each process would require
    int maximum[PRO][RES]   = {{},{},{},{},{}};
    // no of availabe resouce at given instance
    int available[RES] = {};

    int **ans = bankerAlgo(allocated, maximum, available); // function call

    printf("The valid sequence is :\n" ); // printing ans
    for(int i=0; i<PRO; i++) printf("%d ",ans[i]);
    
    return 0;
}

```
</details>

## Deadlock Prevention
Break one of the deadlock condition.

## Deadlock Detection And Recovery