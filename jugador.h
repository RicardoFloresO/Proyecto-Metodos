#ifndef JUGADOR_H
#define JUGADOR_H

#include "tablero.h"

typedef struct {
    Posicion pos;
    int dispositivos[3];
} Jugador;

void inicializarJugador(Jugador *j, Posicion inicio);

int menuTurnoJugador(Jugador *j, Tablero t);  

#endif
