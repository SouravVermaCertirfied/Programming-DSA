# One-Switch-One-Elevator

```c
/* Elevator DS */

typedef enum {
    idle,
    movingUp,
    movingDown,
    stuck
} elevatorStatesType;

typedef enum{
    idle,
    pending
} requestStateType;

typedef struct elevator{
    enum state;
    

} elevatorType;
```
```c
#define REG_STATE 0 

typedef enum{
    idle,
    moveUp,
    moveDown
} buttonStateType;

buttonStateType button;
```
```c
int b1;
 getButtonState(){
    return button;
}
```
```c
/* State Machine */
void inline elevatorStateMachine(elevatorType e1){
    switch(e1.state){
        case idle:
            break;
    }
}
```

```c
int main(){
    elevatorType e1;
    while(1){
        elevatorStateMachine(e1);
    }
    return 0;
}
```