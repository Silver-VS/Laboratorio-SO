#include <stdio.h>
#include <pthread.h>

void *sumar(void *arg) {
    int a = 2, b = 3;
    int resultado = a + b;
    printf("La suma de %d y %d es: %d\n", a, b, resultado);
    pthread_exit(NULL);
}

void *multiplicar(void *arg) {
    int a = 2, b = 3;
    int resultado = a * b;
    printf("El producto de %d y %d es: %d\n", a, b, resultado);
    pthread_exit(NULL);
}