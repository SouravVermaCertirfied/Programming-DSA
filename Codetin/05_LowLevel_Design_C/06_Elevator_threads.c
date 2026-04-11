#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

/*
DS needed : enum state, struct elevator, sch queue
functions needed : add_request, lift_funtion, sch_function, bestMatch, main
*/

#define MAX_ELEVATOR 10

enum State{
    IDLE,
    GOING_UP,
    GOING_DOWN,
    DOOR_OPENING,
    DOOR_CLOSING,
    NO_SERVICE // not used
};

typedef struct Elevator{
    int id;
    int curr_floor;
    int target_floor;
    int has_job;
    enum State states;
    pthread_mutex_t elock;
    pthread_cond_t econd;
} Elevator ;

Elevator *elevators[MAX_ELEVATOR];


typedef struct rQueue{
    int floor;
    struct rQueue *next;

}rQueue;
rQueue *rq = NULL;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t qcond = PTHREAD_COND_INITIALIZER;

/* functions */

void add_request(int floor){
    rQueue *temp = (rQueue *)malloc(sizeof(rQueue));
    temp->floor = floor;
    pthread_mutex_lock(&qlock);
    temp->next = rq;
    rq = temp;
    pthread_cond_signal(&qcond);
    pthread_mutex_unlock(&qlock);
    return ;
}

Elevator * bestMatch(int processFloor){
    int mdiff = 1e9;
    int tdiff = 0;
    Elevator *best = NULL;
    for(int i=0; i<MAX_ELEVATOR; i++){
        pthread_mutex_lock(&(elevators[i]->elock));
        if(elevators[i]->has_job == 0){
            tdiff = abs(processFloor - elevators[i]->curr_floor);
            if(tdiff < mdiff){
                mdiff = tdiff;
                best = elevators[i];
            }
        }
        pthread_mutex_unlock(&(elevators[i]->elock));
    }
    return best;
}

void *sch_function(void *args){

    while(1){
        pthread_mutex_lock(&qlock);
        while(rq==NULL){
            pthread_cond_wait(&qcond, &qlock);
        }
        int processfloor = rq->floor;
        rQueue *temp = rq;
        free(temp);
        rq = rq->next;
        pthread_mutex_unlock(&qlock);
        Elevator *e = bestMatch(processfloor);
        if(e==NULL){
            add_request(processfloor);
        }
        else{
            pthread_mutex_lock(&(e->elock));
            e->target_floor = processfloor;
            e->has_job = 1;
            e->states = IDLE;
            pthread_cond_signal(&e->econd);
            pthread_mutex_unlock(&(e->elock));
        }
    }
    return NULL;
}

void *lift_function(void *args){
    Elevator *e = (Elevator *)args;

    while(1){
        pthread_mutex_lock(&e->elock);
        while(e->has_job == 0 ){
            pthread_cond_wait(&e->econd, &e->elock);
        }
        switch(e->states){
            case IDLE : {
                if(e->target_floor < e->curr_floor){
                    e->states = GOING_DOWN;
                }
                else if(e->target_floor > e->curr_floor){
                    e->states = GOING_UP;
                }
                printf("Lift %d is going to : %d \n", e->id, e->target_floor);
                break;
            }
            case GOING_DOWN :{
                if(e->target_floor < e->curr_floor){
                    e->curr_floor -= 1;
                }
                else if(e->target_floor == e->curr_floor){
                    e->states = DOOR_OPENING;
                    e->has_job = 0;
                }
                break;
            }
            case GOING_UP :{
                if(e->target_floor > e->curr_floor){
                    e->curr_floor += 1;
                }
                else if(e->target_floor == e->curr_floor){
                    e->states = DOOR_OPENING;
                    e->has_job = 0;
                }
                break;
            }
            case DOOR_OPENING:{
                // delay sometime for simulation of opening door
                e->states = DOOR_CLOSING;
                break;
            }
            case DOOR_CLOSING:{
                // delay sometime for simulation of closing door
                e->states = IDLE;
                e->has_job = 0;
                printf("Lift %d is happily closing at : %d \n", e->id, e->target_floor);
                break;
            }
            default:{
                e->states = IDLE;
                break;
            }
        }
        pthread_mutex_unlock(&e->elock);
    }
    return NULL;

}

void init_elevator(int i){
    elevators[i] = (Elevator *)malloc(sizeof(Elevator));
    elevators[i]->id = i;
    elevators[i]->curr_floor = 0;
    elevators[i]->target_floor = 0;
    elevators[i]->has_job = 0;
    elevators[i]->states = IDLE;

    elevators[i]->elock = PTHREAD_MUTEX_INITIALIZER ;
    elevators[i]->econd = PTHREAD_COND_INITIALIZER ;
}

int main(){
    printf("welcome to the lift");
    pthread_t lift_threads[MAX_ELEVATOR];
    pthread_t sch_thread;

    for(int i=0; i<MAX_ELEVATOR; i++){
        init_elevator(i);
        pthread_create(&lift_threads[i], NULL, lift_function, elevators[i]);
    }
    pthread_create(&sch_thread, NULL, sch_function, NULL);

    add_request(5);
//    add_request(10);
//    add_request(3);
//    add_request(15);
//    add_request(60);

    for(int i=0; i<MAX_ELEVATOR; i++)
        pthread_join(lift_threads[i], NULL);
    pthread_join(sch_thread, NULL);

    pthread_mutex_destroy(&qlock);
    pthread_cond_destroy(&qcond);

    return 0;
}
