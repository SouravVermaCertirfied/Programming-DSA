/* One lift - 10 floors - 1 button per floor */
/*  This is a hypthetical senario, 
*   There is just 1 button on every floor, and the lift moves to the next calling floor, as long as there are calling floor,
*   algo to decide next floor to process is simple and dumb, the lift just process the lowest floor first.
*/

#include<stdio.h>

#define MAX_FLOORS 10u // define the number of floors

int buttons_arr[10] = {0}; // 1 means reqeust is coming that floor, 0 means no request for that floor
int requestPending = 0 ; // 0 means no request pending, greater means there are floors with presesed buttons

int lift_pos = 0; // show where the lift is currently
int currentRequestUnderProcess = -1; // -1 means lift is idle, and other value means that lift is moving towards that floor

void setNewRequest(int pos){
    buttons_arr[pos] = 1;
    requestPending++;
}

int getNextFloorRequest(){
    for(int i=0; i<MAX_FLOORS; i++){
        if(buttons_arr[i]==1)
            return i;
    }
    return -1;
}

void lift_stateMachine(){
    // check if there is pending requests
    if(requestPending>0){ 
        // if the lift is idle, request it move
        if(currentRequestUnderProcess == -1){
            currentRequestUnderProcess = getNextFloorRequest();
            printf("The lift will now move to %d \n",currentRequestUnderProcess);
        }
        // if the lift is not idle, let it move to the target floor and go to idle state
        else{
            lift_pos = currentRequestUnderProcess;
            buttons_arr[currentRequestUnderProcess] = 0;
            printf("Reached to floor %d \n",currentRequestUnderProcess);
            currentRequestUnderProcess = -1;
            requestPending--;
        }
    }
    // else do not do anything
    else{
        /* do nothing */
    }
}

int main(){
    unsigned int foreverCounter = 1000;
    int intialButtonRequest[10] = {0,1,1,1,1,0,1,1,1,1};
    for(int i=0; i<10; i++){
        if(intialButtonRequest[i] == 1)
            setNewRequest(i);
    }
    while(foreverCounter--){
        lift_stateMachine();
    }
}
