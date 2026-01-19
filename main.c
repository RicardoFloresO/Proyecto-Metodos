#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"
#include "jugador.h"

int main(){
	//Crea una semilla aleatoria porque el rand en cualquier punto es "fijo"
	srand(time(NULL));

	// Se crea el mapa
	Mapa* mapa = crearMapa();

	// Crear al jugador
	Jugador jugador;

	mostrarMapa(mapa);

	free(mapa);

	return 0;
}