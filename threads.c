#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
  
struct conts {
    double strt;
    double fin;
};

// The function to be executed by all threads
void *thrd(void *inp) {
    struct conts *thstrc = (struct conts*)inp;
    
    printf("from %f to %f\n" , thstrc->strt , thstrc->fin);
    pthread_exit(NULL);
}



int main(int argc , char *argv[]) {
    int num = atoi(argv[1]);
    pthread_t tid[num];
    struct conts poin[num];
    int thstrt = 0;
    int thfin = 0;
    printf("Enter start and finish numbers : ");
    scanf ("%d %d",&thstrt,&thfin);
    
    double dif = (thfin - thstrt);
    double val = dif/num;
    for (int i = 0 ; i < num ; i++) {
        if (i == 0) {
            poin[i].strt = thstrt;
        }
        else {
            poin[i].strt = poin[i-1].fin;
        }
        
        poin[i].fin = poin[i].strt + val;
        
        pthread_create(&tid[i], NULL, thrd, (void *) &poin[i]);
        
    }
    
    for (int i = 0 ; i < num ; i++) {
        if (pthread_join(tid[i], NULL) != 0) {
            perror("err");
        }
    }
    
    return 0;
}
