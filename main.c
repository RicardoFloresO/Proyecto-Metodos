#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mapa.h"

int main(){
	//Crea una semilla aleatoria porque el rand en cualquier punto es "fijo"
	srand(time(NULL));

	Mapa* mapa = crearMapa();

	mostrarMapa(mapa);

	free(mapa);

	return 0;
}