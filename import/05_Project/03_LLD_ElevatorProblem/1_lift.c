/* one lift - 10 floors - 1 button per floor */

#define MAX_FLOOR 10u

typedef enum{
    idle,
    pressed
}buttonStateType;

typedef struct{
    buttonStateType buttonArr[10];
    int pendingRequest;
}buttonType;

void setButtons(buttonType *buttons, int floorNo, buttonStateType buttonState){
    buttons->buttonArr[floorNo] = buttonState;
    buttonState==idle ? buttons->pendingRequest-- : buttons->pendingRequest++;
}

buttonStateType getButtons(buttonType *buttons, int floorNo){
    return buttons->buttonArr[floorNo];
}

int getNextFloorToGo(buttonType *buttons){
    for(int i=0;i<MAX_FLOOR; i++){
        if(buttons->buttonArr[i])
            return i;
    }
    return -1;
}

typedef enum{
    idle,
    movingUp,
    movingDown
} liftStatesType;

lift_FCM(liftStatesType *lift, buttonType *buttons){
    int next = -1;
    switch(*lift){
        case idle :{
            next = getNextFloorToGo(&buttons);
        }
        break;
        case 
    }
}

int main(){
    buttonType buttons;
    setButtons(&buttons, 9, pressed);
    setButtons(&buttons, 3, pressed);
    setButtons(&buttons, 5, pressed);

    liftStatesType lift;
    lift = idle;

    int runForever = 1000;

    while(runForever--){
        lift_FCM(&lift, &buttons);
    }

    
}