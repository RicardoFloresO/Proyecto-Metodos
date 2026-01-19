#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "bot.h"
#include "mapa.h"

// Con BEE en anchura crearemos una funcion para encontrar el camino mas corto del bot
// (similar a anchura() que esta en mapa.c)

void movBot(Bot* b, Mapa* m){
	int mejorDist = 1000;
	//Posicion mejorPaso;
	Casilla mejorPaso;

	// Damos los valores iniciales a mejorPaso
	mejorPaso.fila = b->pos.fila;
	mejorPaso.columna = b->pos.columna;

	// Vectores que permiten moverse
	int cambioFila[] = {-1,1,0,0}; // Arriba, Abajo, Centro, Centro
	int cambioColumna[] = {0,0,-1,1}; // Centro, Centro, Izqui, Der

	Casilla casSalida = m->salida;

	// Se miran a los vecinos para simular un camino mas corto a partir de cada uno de ellos
	for(int i =0; i<4; i++){
		int vecinoFila = b->pos.fila + cambioFila[i];
		int vecinoColumna = b->pos.columna + cambioColumna[i];

		// Ver que este dentro del mapa
		if(vecinoFila >= 0 && vecinoFila < FILAS && vecinoColumna >= 0 && vecinoColumna < COLUMNAS){
			int altBot = m->tablero[b->pos.fila][b->pos.columna].altura;
            int altSig = m->tablero[vecinoFila][vecinoColumna].altura;

            // VEr que se cumpla la dif de altura para moverse
            if (abs(altBot - altSig) <= 2){

            	Casilla casSig;
            	casSig.fila = vecinoFila;
            	casSig.columna = vecinoColumna;

            	int dist = anchura(m, casSig, casSalida);

            	//si no hay camino 
            	if (dist == -1){
            		dist = 1000;
            	}

            	//si es mejor camino que el actual
            	if(dist < mejorDist){
            		mejorDist = dist;
            		mejorPaso.fila = vecinoFila;
            		mejorPaso.columna = vecinoColumna;
            	}
            } 
		}
	}

	//moverse a la casilla siguiente
	if(mejorDist<1000){
		//actualizar mapa
		m->tablero[b->pos.fila][b->pos.columna].idPosicion = 'V';
		//actualizar posicion del bot
		b->pos = mejorPaso;
		//marcar bot en el mapa y actualizar su posicion en el mapa
		m->tablero[b->pos.fila][b->pos.columna].idPosicion = 'B';
		m->inicioBot.fila = mejorPaso.fila;
		m->inicioBot.columna = mejorPaso.columna;

		printf("Bot se mueve!!\n");
	}else{
		printf("Bot no encuentra camino!!\n");
	}
}

void iniciarBot(Bot* b, Casilla inicio){

    // Asignar posicion inicial
    b->pos.fila = inicio.fila;
    b->pos.columna = inicio.columna;

    // Activar todos los dispositivos
    b->dispositivos[0] = 1;
    b->dispositivos[1] = 1;
    b->dispositivos[2] = 1;

}


void turnoBot(Bot* b, Jugador* j,Mapa* m){
	printf("\n***TURNO BOT***\n");

	Casilla posBot = b->pos;
	Casilla posJugador = j->pos;

	// Se calculan las distancias a la salida del bot y jugador
	int distBot = anchura(m,posBot,m->salida);
	int distJugador = anchura(m,posJugador,m->salida);

	//En caso que anchura devuelva un -1 de camino invalido se cambia por un numero gigante
	//De este modo se sabra si el bot o jugador esta atrapado
	if (distBot == -1){
		distBot	= 1000;
	}
	if (distJugador == -1){
		distJugador	= 1000;
	}
	//Bandera para saber cuando uso un dispositivo
	int usoDispositivo = 0;
	//El bot se mueve si o si cuando esta mas cerca de la salida que el jugador 
	//En caso contrario busca usar un dispositivo al azar

	if(distBot > distJugador){

		int dispAux[3]; //arreglo para guardar los indices de los dispositivos disponibles
		int cant = 0;
		//Busca los dispositivos disponibles
		for (int i = 0; i < 3; i++){
			if(b->dispositivos[i] == 1){
				dispAux[cant] = i;
				cant++;
				
			}
		}

		//Si hay dispositivos disponibles, se elige uno al azar
		if(cant>0){
			int dispRandom = rand() % cant;
			int dispElegido = dispAux[dispRandom];

			//printf("->Bot utiliza (nombre dispositivo)");
			b->dispositivos[dispElegido] = 0; //Se marca como usado el dispositivo
			//
		}else{
			printf("Al Bot no le quedan items!!");
		}
	}

	//El bot se mueve
	movBot(b,m);
}