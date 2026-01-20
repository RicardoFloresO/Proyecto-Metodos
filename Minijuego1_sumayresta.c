#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Número aleatorio de dos dígitos 10-99 
int numero_dos_digitos(void) {
    return rand() % 90 + 10;
}

//Genera suma o resta (resultado puede ser negativo) 
int generar_operacion(int *a, int *b, char *simbolo) {
    int op = rand() % 2;   // 0 = suma, 1 = resta

    *a = numero_dos_digitos();
    *b = numero_dos_digitos();

    if (op == 0) {
        *simbolo = '+';
        return (*a + *b);
    } else {
        *simbolo = '-';
        return (*a - *b);   // puede ser negativo
    }
}

// Pide la respuesta del usuario 
int pedir_respuesta(int a, int b, char simbolo) {
    int r;
    printf("Resuelve (un intento): %d %c %d = ", a, simbolo, b);
    scanf("%d", &r);
    return r;
}

// Verifica la respuesta 
void verificar_respuesta(int respuesta, int correcta) {
    if (respuesta == correcta) {
        printf("Correcto\n");
    } else {
        printf("Incorrecto. La respuesta era %d\n", correcta);
    }
}

int main(void) {
    srand((unsigned)time(NULL));

    int a, b;
    char simbolo;

    int correcta = generar_operacion(&a, &b, &simbolo);
    int respuesta = pedir_respuesta(a, b, simbolo);
    verificar_respuesta(respuesta, correcta);

    return 0;
}
