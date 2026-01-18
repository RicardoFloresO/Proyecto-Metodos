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
	for (int i = 0; i < FILAS; i++){
		for (int j = 0; j < COLUMNAS; j++){
			
			// Guardamos la fila y columna en el struct mapa en la parte tablero, la cual es del tipo casilla
			mapita->tablero[i][j].fila = i;
			mapita->tablero[i][j].columna = j;

			// Generamos una altura al azar entre 0 y 5
			mapita->tablero[i][j].altura = rand() % 6; //rand genera un numero aleatorio pero no se puede poner un limite en C
													  //entonces se usa el modulo para que de un valor entre 0 y 5
			
			// Se asignan vacios a los idPosicion en casilla y un 0 para marcar que ninguna casilla es salida
			mapita->tablero[i][j].idPosicion = 'V';
			mapita->tablero[i][j].esSalida = 0;

		}
	}
}


// Se asignara en posiciones aleatorias al Jugador, al Bot y la Salida
void asignarPosiciones(Mapa* mapita){

	// Asignar una posicion al Jugador
	int filaJugador = rand() % FILAS;
	int columnaJugador = rand() % COLUMNAS;
	mapita->tablero[filaJugador][columnaJugador].idPosicion = 'J';
	mapita->inicioJugador = mapita->tablero[filaJugador][columnaJugador];

	// Asignar una posicion al Bot
	int filaBot;
	int columnaBot;
	do{ // Se elige al azar una fila y una columna
		filaBot = rand() % FILAS; 
		columnaBot = rand() % COLUMNAS;
	} while (filaBot == filaJugador && columnaBot == columnaJugador); // Se verifica que no sea la misma que la del jugador

	mapita->tablero[filaBot][columnaBot].idPosicion = 'B'; // En el tablero en su posicion correspondiente, se cambia el idPosicion de Vacio a Bot
	mapita->inicioBot = mapita->tablero[filaBot][columnaBot]; 

	// Asignar posicion a la salida
	int filaSalida;
	int columnaSalida;
	do{
		filaSalida = rand() % FILAS;
		columnaSalida = rand() % COLUMNAS;
	}while ((filaSalida==filaBot && columnaSalida==columnaBot)||(filaSalida==filaJugador && columnaSalida==columnaJugador));

	mapita->tablero[filaSalida][columnaSalida].esSalida = 1;
	mapita->salida = mapita->tablero[filaSalida][columnaSalida];

}


// Se verifica que las casillas tengan alguna al rededor tengan una altura de +-1
int alturasValidas(Mapa* mapita){
	int cambioFila[] = {-1,1,0,0}; // Arriba, Abajo, Centro, Centro
	int cambioColumna[] = {0,0,-1,1}; // Centro, Centro, Izqui, Der

	//recorrer el tablero
	for(int i = 0; i<FILAS; i++){
		for(int j = 0; j<COLUMNAS; j++){

			int alturaActual = mapita->tablero[i][j].altura;
			int vecinoValido = 0; // vecinoValido parte en 0 y cuando se encuentre uno se dira que es valido 

			//recorrer vecinos
			for (int k=0; k<4; k++){
				int vecinoFila = i + cambioFila[k];
				int vecinoColumna = j + cambioColumna[k];

				//ver que el vecino este en el mapa
				if (vecinoFila >= 0 && vecinoFila < FILAS && vecinoColumna >= 0 && vecinoColumna < COLUMNAS){
					int alturaVecino = mapita->tablero[vecinoFila][vecinoColumna].altura;
					int difAltura = alturaActual - alturaVecino;

					if(difAltura == 0 || difAltura == 1 || difAltura == -1){
						vecinoValido = 1;
					}
				}
			}
			if(vecinoValido == 0){
				return 0; //Si no cambio a 1 esta casilla esta aislada y no paso la prueba
			}

		}
	}
	return 1; // Las casillas cumplen la condicion
}



// BEE en anchura para encontrar caminos validos

// Primero se crea la estructura fila, con la metodologia FIFO

struct cola{
	int filaCola;
	int columnaCola;
	int pasos; // Pasos almacenara cuantos pasos tuvo que dar para llegar a la meta
};
typedef struct cola Cola;

// inicio sera la posicion del jugador/bot, final sera la salida; devuelve la cantidad de pasos que dio el jugador/bot hasta llegar a la salida
int anchura(Mapa* mapita, Casilla inicio, Casilla final){
	//Se crea una matriz en blanco para poder ir marcando cuales casillas se visitan
	int visitados[FILAS][COLUMNAS] = {0};

	Cola pendientes[FILAS*COLUMNAS]; // Arreglo de 64 elementos para saber cuales son los pendientes a visitar
	int cabezaCola = 0;
	int finalCola = 0;

	//inicializamos pendientes con los datos de donde parte el jugador/bot
	pendientes[finalCola].filaCola = inicio.fila;
	pendientes[finalCola].columnaCola = inicio.columna;
	pendientes[finalCola].pasos = 0;
	finalCola++;

	visitados[inicio.fila][inicio.columna] = 1;

	int cambioFila[] = {-1,1,0,0}; // Arriba, Abajo, Centro, Centro
	int cambioColumna[] = {0,0,-1,1}; // Centro, Centro, Izqui, Der

	while(cabezaCola<finalCola){

		// Se crea un actual que es la posicion que estamos verificando
		Cola actual = pendientes[cabezaCola];
		cabezaCola++;

		// Si encuentra la salida devolver cuantos pasos se demoro en llegar
		if (actual.filaCola == final.fila && actual.columnaCola == final.columna){
			return actual.pasos;
		}

		// Revisar vecinos
		for (int i = 0; i < 4; i++){
			// Coord vecinos
			int vecinoFila = actual.filaCola + cambioFila[i];
			int vecinoColumna = actual.columnaCola + cambioColumna[i];

			// Ver que este dentro del mapa 
			if(vecinoFila >= 0 && vecinoFila < FILAS && vecinoColumna >= 0 && vecinoColumna < COLUMNAS){

				// Ver que no se haya visitado ese nodo, visitados en la pos que se quiere visitar es 0, entonces no se ha visitado
				if (visitados[vecinoFila][vecinoColumna] == 0){
					
					// Comprobar alturas, tanto actual como en el vecino

					int alturaActual = mapita->tablero[actual.filaCola][actual.columnaCola].altura;
					int alturaVecino = mapita->tablero[vecinoFila][vecinoColumna].altura;
					int difAltura = alturaActual - alturaVecino;

					// Se verifica que la diferencia de altura sea +-1m
					if(difAltura == 0 || difAltura == 1 || difAltura == -1){
						// Actualizar pos visitada
						visitados[vecinoFila][vecinoColumna] = 1;

						//Actualizar final de la cola
						pendientes[finalCola].filaCola = vecinoFila;
						pendientes[finalCola].columnaCola = vecinoColumna;
						pendientes[finalCola].pasos = actual.pasos + 1;

						finalCola++;
					}

				}

			}

		}

	}
	return -1; // CUando la cola este vacia, entonces no hay camino
}


// Funcion para validar el mapa devuelve 1 si es valido y 0 si no es valido
int validarMapa(Mapa* mapita){
	// Se comprueba que las casillas tengan +-1 de dif de altura en alguna casilla anexa
	if(alturasValidas(mapita) == 0){
		return 0;
	}
	
	int distJugador = anchura(mapita, mapita->inicioJugador, mapita->salida);
	int distBot = anchura(mapita, mapita->inicioBot, mapita->salida);

	// Las 3 condiciones que tiene que cumplir el mapa, que los participantes partan a 4 pasos validos y que partan a la misma distancia
	if(distJugador < 4){
		return 0; //mapa no valido
	}
	if (distBot < 4){
		return 0;
	}
	if(distBot != distJugador){
		return 0;
	}

	return 1; // Mapa valido
}


// Funcion que crea el mapa
Mapa* crearMapa(){
	// Asignamos memoria para crear el mapa
	Mapa* mapaCreado = (Mapa*)malloc(sizeof(Mapa));

	// Le damos dimensiones al mapaCreado
	mapaCreado->filas = FILAS;
	mapaCreado->columnas = COLUMNAS;

	// Banderita para parar el ciclo de creacion de mapas hasta encontrar un mapa valido
	int mapaValido = 0;
	do{
		llenarMapa(mapaCreado);
		asignarPosiciones(mapaCreado);

		mapaValido = validarMapa(mapaCreado);
	}while(mapaValido==0);

	return mapaCreado;
}


// Funcion que mostrara el mapa por pantalla
void mostrarMapa(Mapa* mapita){

	// Informacion de las posiciones
	// Se mostrara la posicion del jugador y la del bot con su respectiva altura

	//Datos del jgador
	int jugadorFil = mapita->inicioJugador.fila;
	int jugadorCol = mapita->inicioJugador.columna;
	int jugadorAlt = mapita->tablero[jugadorFil][jugadorCol].altura;
	printf("DATOS JUGADOR: Posicion-> [%d][%d] / Altura-> %d m\n",jugadorFil,jugadorCol,jugadorAlt);

	// Datos del bot
	int botFil = mapita->inicioBot.fila;
	int botCol = mapita->inicioBot.columna;
	int botAlt = mapita->tablero[botFil][botCol].altura;
	printf("DATOS BOT: Posicion-> [%d][%d] / Altura-> %d m\n",botFil,botCol,botAlt);

	// printear mapa

	// Enumera las columnas
	printf("\n  ");
	for(int j=0;j<COLUMNAS;j++){
		printf(" %d ",j);
	}	
	printf("\n");

	// IMprime filas 
	for(int i=0;i<FILAS;i++){
		printf("%d ",i);
		for(int j=0;j<COLUMNAS;j++){
			Casilla aux = mapita->tablero[i][j];

			if (aux.idPosicion == 'J'){
				printf("[J]");
			}else if (aux.idPosicion == 'B'){
				printf("[B]");
			}else if (aux.esSalida == 1){
				printf("[S]");
			}else{
				printf(" %d ",aux.altura);
			}

		}
		printf("\n");
	}
	printf("\n");

}