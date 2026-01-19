#include <stdio.h>  // printf, scanf 
#include <stdlib.h> // rand, srand, system 
#include <time.h> // time(), para num aleatorios 
//archivos que tienen las funciones del juego
#include "tablero.h"  //manejo del tablero 
#include "jugador.h"
#include "ia.h"
#include "utilidades.h"
#include "dispositivos.h"

int main() {
    srand(time(NULL));

     // variables principales 
    Tablero tablero;   //mapa del juego 
    Jugador jugador;   //usuario
    Posicion ia;       //la pos del bot 

    //posiciones iniciales 
    Posicion inicioJugador; 
    Posicion inicioIA; 
    Posicion meta;


    //posiciones aleatorias 
    inicioJugador = posicionBordeAleatoria(); //devuleve una posicion en el borde, proviene de tablero.c

    do {
        inicioIA = posicionBordeAleatoria();
        //si sale la misma posicion igual al jugador, vuelve a generar la posicion 
    } while (inicioIA.x == inicioJugador.x && inicioIA.y == inicioJugador.y); 
     
    //se repide hasta que no cioncida con la posicion del usuario y de la ia 
    do {
        meta = posicionAleatoria(); //genera posicion cualquiera
    } while (
        (meta.x == inicioJugador.x && meta.y == inicioJugador.y) ||
        (meta.x == inicioIA.x && meta.y == inicioIA.y));


    //Generar tablero valido
    do {
        inicializarTablero(&tablero); //crea el mapa 
    } while (!existeCamino(tablero, inicioIA, meta)); //funcion verifica si hay un camino valido desde incio a la meta 

    tablero.meta = meta;//guarda la meta dentro del tablero 


    //Inicia jugador o IA
    inicializarJugador(&jugador, inicioJugador);
    ia = inicioIA;   //guarda posicion inicial ia 

    //Cara o sello
    int op;
    int moneda;
    int turnoJugador;

    printf("=== LANZAMIENTO DE MONEDA ===\n");
    printf("1) Cara\n");
    printf("2) Sello\n");
    printf("Elige: ");
    scanf("%d", &op);

    moneda = rand() % 2 + 1; //genera 1 o 2 aleatorio 

    if (moneda == 1)
        printf("\nSalio: Cara\n");
    else
        printf("\nSalio: Sello\n");

    if (op == moneda) {
        printf("Ganaste. Empiezas tu.\n");
        turnoJugador = 1;
    } else {
        printf("Perdiste. Empieza el bot.\n");
        turnoJugador = 0;
    }

    system("pause");


    //Juego por turnos, se ejecuta hasta que alguien gane 
    while (1) {
        limpiarPantalla();   //borra la consola 
        mostrarTablero(tablero, jugador.pos, ia);  //muestra el tablero con las posiciones jugador, ia, meta.

        // Verificar ganador, el primero que llega a la meta gana.
        if (jugador.pos.x == tablero.meta.x && jugador.pos.y == tablero.meta.y) {
            printf("\n¡GANASTE!\n");
            break;
        }

        if (ia.x == tablero.meta.x && ia.y == tablero.meta.y) {
            printf("\nGano la IA\n");
            break;
        }

        //turno del jugador
        if (turnoJugador) {
            if (menuTurnoJugador(&jugador, tablero) == -1) // -1 si el jugador decide rendirse 
                break;                                     // 0 sigue jugando 
            turnoJugador = 0;
        }
        //turno de la IA
        else {
            printf("\nTurno de la IA...\n");
            turnoIA(&ia, tablero);
            system("pause");
            turnoJugador = 1;
        }
    }

    return 0;
}
