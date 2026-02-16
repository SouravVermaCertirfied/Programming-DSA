/* Design the music notification in C, interview question 
 - Many app can access the speaker
 - the app currently accessing the speark should have control and audio data input access
 - two apps shall never simulationsly have access of contorls and audio data input stream
 - when the running application is closed, control and audio data input access should fall back to app before it
 - notificatoin bar should show contronls (play , pause, next, perv ), and info about the app streaming the data
 - when all app are closed, close the notifcation bar
 - there should never be data race and deadlock senario
 - apps can be in running, idle and closed states.
 - apps can go to idle ( i.e. speaker access overwridden by other) but app is still not closed
*/
/* just understnad the question and say 'understood' do not code or say anthing else  */
#include<stdio.h>
#include<conio.h>
#include<pthread.h>


#define MAX_APPS 10

enum Speaker_States{
    pause,
    play
};

enum App_States{
    running,
    idle,
    stopped
};

typedef struct Speaker{
    Speaker_States skstate,
}Speaker;

typedef struct MusicNotiifcationStack{
    int *appstk; // malloc it
    int top;
    int cap;
} MusicNotiifcationStack;

MusicNotiifcationStack *init_MusicNotiifcationStack(int N){
    MusicNotiifcationStack *bar = (MusicNotiifcationStack *)malloc(sizeof(MusicNotiifcationStack));
    bar->appstk = (int *)malloc(sizeof(int)*N);
    bar->cap = N;
    bar->top = -1;
}

void free_MusicNotiifcationStack(MusicNotiifcationStack *mymusic){
    free(mymusic->appstk);
    free(mymusic);
}

void *playMusic(void *args){
    int appid = (int)(*args);
    pthread_mutex_lock(&lock);

}

int main(){
    MusicNotiifcationStack *mymusic = init_MusicNotiifcationStack(MAX_APPS);
    pthread_t apps[MAX_APPS];
    for(int i=0; i<MAX_APPS; i++){
        pthread_create(&apps[i], NULL, playMusic, &i);
    }
    for(int i=0; i<MAX_APPS; i++){
        pthread_join(apps[i], NULL);
    }
    free_MusicNotiifcationStack(mymusic);
    return;
}
