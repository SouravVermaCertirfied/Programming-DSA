/*  ONE ELEVATOR - 10 FLOORS - ONE BUTTON PER FLOOR */


/* define ds for elevator */

typedef enum {
    idle,
    movingUp,
    movingDown
} elevatorStateType;

typedef struct{
    elevatorStateType state;
} elevatorType;

/* define ds for button */
typedef enum{

}buttonStateType;

/* define function for reading the button status */

/* define state machine */

void inline elevatorStateMachine(elevatorType e1){
    switch(){
        
    }
}

/* define main function */
int main(){
    elevatorType e1;
    e1.state = idle;
    while(1){
        elevatorStateMachine(e1);
    }
}