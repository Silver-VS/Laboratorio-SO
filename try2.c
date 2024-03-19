#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Prototipo de la función para imprimir los caracteres
void printChars(const char* str, HANDLE sem);

int main() {
    // Inicialización de las cadenas de caracteres
    char str1[256], str2[256];

    // Obtención de las cadenas de parte del usuario
    printf("Enter the first string: ");
    fgets(str1, sizeof(str1), stdin);
    printf("Enter the second string: ");
    fgets(str2, sizeof(str2), stdin);

    // Creación de un semáforo para sincronizar la escritura de las cadenas
    HANDLE semaphore = CreateSemaphore(NULL, 1, 1, NULL);

    // Creación de procesos para cada cadena
    STARTUPINFO si;
    PROCESS_INFORMATION pi;

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    ZeroMemory(&pi, sizeof(pi));

    // Crear un proceso para imprimir la primera cadena
    if (CreateProcess(NULL, "printProcess.exe str1", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0) {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    // Esperar hasta que el proceso anterior finalice
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Crear un proceso para imprimir la segunda cadena
    if (CreateProcess(NULL, "printProcess.exe str2", NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi) == 0) {
        fprintf(stderr, "CreateProcess failed (%d).\n", GetLastError());
        return -1;
    }

    // Esperar hasta que el proceso anterior finalice
    WaitForSingleObject(pi.hProcess, INFINITE);

    // Cerrar manijas del proceso y del hilo
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Cerrar el semáforo
    CloseHandle(semaphore);

    return 0;
}

// Función para imprimir los caracteres de la cadena
void printChars(const char* str, HANDLE sem) {
    srand(time(NULL));  // Inicializar la semilla para números aleatorios

    for (int i = 0; i < strlen(str); i++) {
        WaitForSingleObject(sem, INFINITE);  // Esperar por el semáforo

        printf("%c", str[i]);  // Imprimir el carácter
        Sleep(rand() % 1000);  // Retardo aleatorio entre 0 y 1000 milisegundos

        ReleaseSemaphore(sem, 1, NULL);  // Liberar el semáforo
    }
}
