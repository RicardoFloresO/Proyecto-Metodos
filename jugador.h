#ifndef JUGADOR_H
#define JUGADOR_H

#include "mapa.h"

typedef struct {
    int fila; 
    int columna; 
} Posicion;

typedef struct {
    Posicion pos;
    int dispositivos[3];
} Jugador;

void inicializarJugador(Jugador *j, Posicion inicio);

int menuTurnoJugador(Jugador *j, Mapa* m);  

#endif
