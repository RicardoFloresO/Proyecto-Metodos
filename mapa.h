#ifndef MAPA_H
#define MAPA_H


// Define constantes que se usaran
#define FILAS 8
#define COLUMNAS 8

struct casilla{
	int fila; //en que fila del tablero esta la casilla
	int columna; //en que columna del tablero esta la casilla
	int altura; //un entero del 0 al 5, es decir, la altura de la casilla
	char idPosicion; // Vacio; Jugador; Bot, se considera solo la mayuscula V;J;B
	int esSalida; //un 1 si es salida, un 0 si no es salida
};
typedef struct casilla Casilla;

struct mapa{
	int filas; //Se definira cierta cantidad de filas para poder ampliar o reducir el mapa a futuro
	int columnas; //Se definira cierta cantidad de columnas para poder ampliar o reducir el mapa a futuro
	Casilla inicioJugador; //En que posicion inicia el jugador
	Casilla inicioBot;	//En que posicion inicia el bot
	Casilla salida; //En que posicion esta la salida
	Casilla tablero[FILAS][COLUMNAS]; //tablero fijo de 8x8
	
};
typedef struct mapa Mapa;


Mapa* crearMapa(); 

int validarMapa(Mapa* mapita);

void mostrarMapa(Mapa* mapita);

#endif 