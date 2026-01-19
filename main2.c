#include <stdio.h>  // printf, scanf 
#include <stdlib.h> // rand, srand, system 
#include <time.h> // time(), para num aleatorios 
//archivos que tienen las funciones del juego
#include "mapa.h"  
#include "jugador.h"
#include "bot.h"
//falta
//#include "utilidades.h"
//#include "dispositivos.h"

//funcion para limpiar pantalla
void limpiarPantalla(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    srand(time(NULL));

     // variables principales 
    Mapa* mapita = crearMapa();   //mapa del juego 
    Jugador jugador;   //usuario
    Bot bot;       // bot 
    Casilla salida;

    //posiciones iniciales 
    jugador.pos = mapita->inicioJugador; 
    bot.pos = mapita->inicioBot; 
    salida = mapita->salida;    

    inicializarJugador(&jugador,jugador.pos);
    iniciarBot(&bot,bot.pos);

    /*
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
    ia = inicioIA;   //guarda posicion inicial ia */

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

    if (moneda == 1){
        printf("\nSalio: Cara\n");
    }
    else{
        printf("\nSalio: Sello\n");
    }

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
        //limpiarPantalla();   //borra la consola 
        mostrarMapa(mapita);  //muestra el mapa con las posiciones jugador, ia, meta.

        // Verificar ganador, el primero que llega a la meta gana.
        if (jugador.pos.fila == mapita->salida.fila && jugador.pos.columna == mapita->salida.columna) {
            printf("\n¡GANASTE!\n");
            break;
        }

        if (bot.pos.fila == mapita->salida.fila && bot.pos.columna == mapita->salida.columna) {
            printf("\nGano la IA\n");
            break;
        }

        //turno del jugador
        if (turnoJugador) {
            if (menuTurnoJugador(&jugador, mapita) == -1){ // -1 si el jugador decide rendirse
                break;  
            } 
            if (menuTurnoJugador(&jugador, mapita) == 1){
                turnoJugador = 0;
            }
            
        }else { //turno bot
            printf("\nTurno del Bot...\n");
            turnoBot(&bot, &jugador, mapita);
            system("pause");
            turnoJugador = 1;
        }
    }
    free(mapita);
    return 0;
}
