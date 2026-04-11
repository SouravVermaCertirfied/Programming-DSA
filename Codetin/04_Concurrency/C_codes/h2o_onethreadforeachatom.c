#include <stdio.h>
#include <pthread.h>

pthread_mutex_t lock;
pthread_cond_t cond;

int h_needed = 2;  // How many H we still need for this molecule
int o_needed = 1;  // How many O we still need for this molecule
int mcount = 0;    // Molecules completed

void *hydrogen(void *args) {
    while (1) {
        pthread_mutex_lock(&lock);
        
        // ☢️ Exit condition: Stop if we've made 100 molecules
        if (mcount >= 100) {
            pthread_mutex_unlock(&lock);
            break;
        }

        // ☢️ Wait while it's NOT time for Hydrogen (if we already printed 2 H's)
        while (h_needed == 0 && mcount < 100) {
            pthread_cond_wait(&cond, &lock);
        }

        if (mcount < 100) {
            printf("H");
            h_needed--;

            // ☢️ If we've printed 2H and 1O, the molecule is done!
            if (h_needed == 0 && o_needed == 0) {
                printf(" "); // Space between molecules
                mcount++;
                h_needed = 2; // Reset for next molecule
                o_needed = 1;
            }
            pthread_cond_broadcast(&cond);
        }
        
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *oxygen(void *args) {
    while (1) {
        pthread_mutex_lock(&lock);
        
        if (mcount >= 100) {
            pthread_mutex_unlock(&lock);
            break;
        }

        // ☢️ Wait while it's NOT time for Oxygen (if we already printed 1 O)
        while (o_needed == 0 && mcount < 100) {
            pthread_cond_wait(&cond, &lock);
        }

        if (mcount < 100) {
            printf("O");
            o_needed--;

            if (h_needed == 0 && o_needed == 0) {
                printf(" "); 
                mcount++;
                h_needed = 2; 
                o_needed = 1;
            }
            pthread_cond_broadcast(&cond);
        }

        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t hy, ox; // One factory thread for H, one for O
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&cond, NULL);
    
    pthread_create(&hy, NULL, hydrogen, NULL);
    pthread_create(&ox, NULL, oxygen, NULL);
    
    pthread_join(hy, NULL);
    pthread_join(ox, NULL);
    
    printf("\nSuccessfully synthesized %d molecules!\n", mcount);
    
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    
    return 0;
}