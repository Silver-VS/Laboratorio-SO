#include <stdio.h>
#include "assert.h"
#include "pthread.h"

#define __DEBUG

_Noreturn void *IncrDecr(void *);

int x = 0;

_Noreturn void *IncrDecr(void *arg){
#ifdef __DEBUG
    printf("Hilo IncrDecr iniciado\n");
#endif
    for(;;){
        x = x+1;
        x = x-1;
    }
}

int main(int argc, char *argv[]){
    pthread_t t0id, t1id;
    pthread_create(&t0id, NULL, IncrDecr, NULL);
    pthread_create(&t1id, NULL, IncrDecr, NULL);
#ifdef __DEBUG
    printf("Hilos creados\n");
    printf("Inicio de sonda de testeo\n");
#endif
    while(1){
        assert(0 <= x && x <= 2);
        printf("%2d", x);
    }
}

