#ifndef MAPA_H
#define MAPA_H

struct casilla{
	int fila; //en que fila del tablero esta la casilla
	int columna; //en que columna del tablero esta la casilla
	int altura; //un entero del 0 al 5
	char idPosicion; // Vacio; Jugador; Bot, se considera solo la mayuscula V;J;B

};
typedef struct casilla Casilla;

struct mapa{
	int filas; //Se definira cierta cantidad de filas para poder ampliar o reducir el mapa a futuro
	int columnas; //Se definira cierta cantidad de columnas para poder ampliar o reducir el mapa a futuro
	Casilla inicioJugador; //En que posicion inicia el jugador
	Casilla inicioBot;	
	Casilla salida;
	Casilla tablero[8][8]; //tablero fijo de 8x8
	//Casilla **tablero; //En caso de que nos pidan modificar el tablero, se comenta la linea anterior y se descomenta esta
};
typedef struct mapa Mapa;


Mapa* crearMapa(); 

int validarMapa(Mapa* mapita);

