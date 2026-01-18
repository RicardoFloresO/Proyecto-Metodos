#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"

// Se usara BES para generar el mapa y ver que las casillas adyacentes esten a +-1m de la casilla
// Luego se usara BEE para ver si el camino cumple con tener un camino valido a la salida
// En cada casilla de la matriz habra un numero y una letra 
// J->Jugador; B->Bot; S->Salida; V->Vacio

// Primero para generar el mapa hay que llenar las casillas con las alturas
// Para esto se usara "ruido" accediendo a la fila y columna, para colocar un valor aleatorio entre 0 y 5
// Esto luego se validara y se vera si el mapa sirve o no.

void llenarMapa(Mapa* mapita){
	for (int i = 0; i < filas; ++i){
		for (int j = 0; i < columnas; ++j){
			
			// Guardamos la fila y columna en el struct mapa en la parte tablero, la cual es del tipo casilla
			mapita->tablero[i][j].fila = i;
			mapita->tablero[i][j].columna = j;

			// Generamos una altura al azar entre 0 y 5
			mapita->tablero[i][j].altura = rand() % 6 //rand genera un numero aleatorio pero no se puede poner un limite en C
													  //entonces se usa el modulo para que de un valor entre 0 y 5
			
			// Se asignan vacios a los idPosicion en casilla y un 0 para marcar que ninguna casilla es salida
			mapita->tablero[i][j].idPosicion = "V";
			mapita->tablero[i][j].esSalida = 0;

		}
	}
}

// Se asignara en posiciones aleatorias al Jugador, al Bot y la Salida
void asignarPosiciones(Mapa* mapita){

	// Asignar una posicion al Jugador
	int filaJugador = rand() % FILAS;
	int columnaJugador = rand() % COLUMNAS;
	mapita->tablero[filaJugador][columnaJugador].idPosicion = "J";
	mapita->inicioJugador = mapita->tablero[filaJugador][columnaJugador];

	// Asignar una posicion al Bot
	int filaBot;
	int columnaBot;
	do{
		filaBot = rand() % FILAS;
		columnaBot = rand() % COLUMNAS;
	} while (filaBot == filaJugador && columnaBot == columnaJugador);

	mapita->tablero[filaBot][columnaBot].idPosicion = "B";
	mapita->inicioBot = mapita->tablero[filaBot][columnaJugador];

	// Asignar posicion a la salida
	int filaSalida;
	int columaSalida;
	do{
		filaSalida = rand() % FILAS;
		columnaSalida = rand() % COLUMNAS;
	}while ((filaSalida==filaBot && columnaSalida==columnaBot)||(filaSalida==filaJugador && columnaSalida==columnaJugador));

	mapita->tablero[filaSalida][columaSalida].esSalida = 1;
	mapita->salida = mapita->tablero[filaSalida][columnaSalida];

}

// BEE en anchura para encontrar caminos validos