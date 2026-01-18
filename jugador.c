#include <stdio.h>
#include <ctype>
#include "jugador.h"

// static solo se usa dentro de este archivo y no se puede llamar de otros modulos 
static void mostratDisp(Jugador *j);
static void usarDisp(Jugador *j);
static void moverJugador(Jugador *j, Tablero t); 

void inicializarJugador(Jugador *j, Posicion inicio) {

    // Asignar posicion inicial
    j->pos.x = inicio.x;
    j->pos.y = inicio.y;

    // Activar todos los dispositivos
    j->dispositivos[0] = 1;
    j->dispositivos[1] = 1;
    j->dispositivos[2] = 1;
}


int menuTurnoJugador( Jugador *j, Tablero t){
    int opcion;
    printf("\n***TURNO JUGADOR***\n");
    printf("1)Moverse.\n");
    printf("2)Dispositivo.\n");
    printf("3)Rendirse.\n");
    printf("Eliga una opcion: ");

    if (scanf("%d", &opcion) !=1){
        printf("Opcion invalida\n");
        while(getchar()!= '\n'); //limpia la memoria (buffer)
        return 0;

    }
    switch (opcion){
        case 1:
            moverJugador(j,t);
            return 1;
        case 2:
            usarDisp(j);
            return 0;
        case 3:
            printf("Te haz rendido.\n");
            return -1;
        default:
            printf("Opcion invalida\n");
            return 0;
    }

}

static void moverJugador(Jugador *j, Tablero t){
    char tecla;
    Posicion nueva;
    // Copiar posicion actual
    nueva.x = j->pos.x;
    nueva.y = j->pos.y;

    printf("Mover (W=arriba, A=izq, S=abajo, D=der): ");
    scanf(" %c", &tecla);
    tecla = toupper(tecla);

    if (tecla == 'W') {
        nueva.x = nueva.x - 1;
    }
    else if (tecla == 'S') {
        nueva.x = nueva.x + 1;
    }
    else if (tecla == 'A') {
        nueva.y = nueva.y - 1;
    }
    else if (tecla == 'D') {
        nueva.y = nueva.y + 1;
    }
    else {
        printf("Tecla invalida\n");
        return;
    }

    if (nueva.x < 0 || nueva.x >= N || nueva.y < 0 ||nueva.y >= N ){
        printf("¡No se puede salir del tablero!");
        return;
    }
    if (movimientoValido(t, j->pos, nueva)) {
        j->pos.x = nueva.x;
        j->pos.y = nueva.y;
        printf("Movimiento correcto\n");
    }
    else {
        printf("Movimiento invalido (diferencia de altura > 2)\n");
    }
}
static void mostrarDisp(Jugador *j) {
    printf("\n--- DISPOSITIVOS ---\n");
    printf("1) Gaius       [%s]\n", j->dispositivos[0] ? "Disponible" : "Usado");
    printf("2) Quadratus   [%s]\n", j->dispositivos[1] ? "Disponible" : "Usado");
    printf("3) Hydrus      [%s]\n", j->dispositivos[2] ? "Disponible" : "Usado");
}

static void usarDisp(Jugador *j) {
    int opcion;

    mostrarDisp(j);
    printf("Seleccione dispositivo (1-3) o 0 para volver: ");
    if (scanf("%d", &opcion) != 1) {
        printf("Entrada invalida\n");
        while (getchar() != '\n');
        return;
    }

    if (opcion == 0) return;

    if (opcion < 1 || opcion > 3) {
        printf("Opcion invalida\n");
        return;
    }

    if (j->dispositivos[opcion - 1] == 0) {
        printf("Ese dispositivo ya fue usado\n");
        return;
    }

    printf("Dispositivo %d activado (funcionalidad pendiente)\n", opcion);
    j->dispositivos[opcion - 1] = 0;
}
