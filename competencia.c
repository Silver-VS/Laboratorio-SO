/*
 * Aceves Serrano Víctor Ghalieb
 * Castro Macías Julio Cesar
 * Portocarrero Rodriguez Habid
 * Lopez Garduño Isacc
 * Alejandro Fernandez Marvin
 * Angel Lecanda Castillo
 * Aguillon Colon Emanuel
 * López de la Rosa Elliot Moisés
 * Giles Macias Alexis
 */


#include <stdio.h>     // Para funciones de entrada/salida estándar
#include <stdlib.h>    // Para manejo de memoria dinámica y otras funciones
#include <string.h>    // Para manejo de cadenas de caracteres
#include <windows.h>   // Para funciones específicas de Windows, como manejo de hilos

#define MAX_LEN 256    // Longitud máxima de las cadenas

// La función write_chars es un punto clave en este programa que utiliza las características
// específicas de la programación multihilo en Windows. Esta función es diseñada para ser
// ejecutada en un hilo separado para cada cadena de caracteres que se desea imprimir.
// Veamos cada parte de su definición y funcionalidad:

// DWORD WINAPI write_chars(LPVOID param)
// |    |      |             |      |
// |    |      |             |      └─── param: Un puntero a void que permite pasar cualquier tipo de datos a la función.
// |    |      |             |
// |    |      |             └───────── write_chars: Nombre de la función. Esta función se encargará de imprimir los caracteres.
// |    |      |
// |    |      └─────────────────────── WINAPI: Macro que especifica la convención de llamada __stdcall. Esto asegura que la función
// |    |                                    sea compatible con el sistema de llamadas de Windows y que la pila se maneje correctamente.
// |    |                                    En __stdcall, el código de la función llamada se encarga de limpiar la pila. Esto es crucial
// |    |                                    en el entorno Windows donde la convención de llamada define cómo los argumentos son pasados a
// |    |                                    la función y cómo se realiza la limpieza después de la llamada a la función.
// |    |
// |    └─────────────────────────────── DWORD: Tipo de retorno de la función, que en este caso es un DWORD (un entero de 32 bits sin signo).
// |                                        En el contexto de las funciones de hilo en Windows, el tipo de retorno DWORD suele usarse para
// |                                        devolver un código de estado o un valor de salida, aunque en muchos casos este valor no se utiliza.
// |
// └───────────────────────────────────── Esta combinación indica que write_chars es una función que será utilizada como punto de entrada
//                                         para un hilo en Windows. La función debe adherirse a la convención de llamada __stdcall y está
//                                         diseñada para trabajar dentro del sistema de ejecución multihilo de Windows.

// Dentro de write_chars, la función recibe un puntero param, que se espera que apunte a una estructura o datos que contengan
// la cadena de caracteres a imprimir y posiblemente otros valores como el retardo entre cada carácter. El uso de LPVOID permite
// pasar diferentes tipos de estructuras de datos a la función, haciéndola flexible para múltiples usos. En este contexto, se
// realiza un casting del puntero a un tipo específico de estructura (ThreadData en este caso) para acceder a la cadena y al retardo.

// La función itera sobre cada carácter de la cadena, imprimiéndolo y luego esperando un tiempo determinado antes de continuar
// con el siguiente carácter. Esto simula una escritura en tiempo real y hace que la salida en la consola sea más interactiva
// y fácil de seguir. La función finalmente devuelve un valor, que en el contexto de un hilo, suele ser el código de salida del hilo.
// Función para escribir una cadena caracter por caracter con retardos aleatorios
DWORD WINAPI write_chars(LPVOID param) {
    char* str = (char*)param;
    int len = strlen(str);
    for (int i = 0; i < len; i++) {
        printf("%c", str[i]); // Escribe un caracter de la cadena
        fflush(stdout);        // Asegura que el caracter se imprima inmediatamente
        Sleep(rand() % 500);   // Espera un tiempo aleatorio entre 0 y 500 milisegundos
    }
    printf("\n"); // Imprime un salto de línea al final
    return 0;
}

int main() {
    char str1[MAX_LEN], str2[MAX_LEN]; // Define dos cadenas de caracteres

    srand(GetTickCount()); // Inicializa la semilla del generador de números aleatorios

    printf("Enter the first string: ");
    fgets(str1, MAX_LEN, stdin); // Lee la primera cadena desde la entrada estándar
    str1[strcspn(str1, "\n")] = 0; // Elimina el salto de línea al final

    printf("Enter the second string: ");
    fgets(str2, MAX_LEN, stdin); // Lee la segunda cadena desde la entrada estándar
    str2[strcspn(str2, "\n")] = 0; // Elimina el salto de línea al final

    HANDLE thread1 = CreateThread(NULL, 0, write_chars, str1, 0, NULL); // Crea el primer hilo
    HANDLE thread2 = CreateThread(NULL, 0, write_chars, str2, 0, NULL); // Crea el segundo hilo

    // Espera a que los hilos terminen
    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    // Cierra los identificadores de los hilos
    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}
