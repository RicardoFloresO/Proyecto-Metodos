#ifndef BOT_H
#define BOT_H

#include "mapa.h"
#include "jugador.h"

struct bot{
	//Posicion pos;
	Casilla pos;
	int dispositivos[3];
};
typedef struct bot Bot;

//void iniciarBot(Bot* b, Posicion incio);
void iniciarBot(Bot* b, Casilla incio);

void turnoBot(Bot* b, Jugador* j,Mapa* m);

#endif