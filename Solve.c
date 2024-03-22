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

int main() {
    pthread_t hilo_suma, hilo_multiplicacion;

    // Crear hilos
    pthread_create(&hilo_suma, NULL, sumar, NULL);
    pthread_create(&hilo_multiplicacion, NULL, multiplicar, NULL);

    // Esperar a que los hilos terminen
    pthread_join(hilo_suma, NULL);
    pthread_join(hilo_multiplicacion, NULL);

    return 0;
}