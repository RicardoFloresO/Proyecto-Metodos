
#ifndef DISPOSITIVOS_H
#define DISPOSITIVOS_H

#include "mapa.h"

// Tipos de dispositivos
typedef enum {
    GAIUS,
    QUADRATUS,
    HYDRUS,
    PHALANX,
    ARGUS,
    DISPOSITIVO_TOTAL
} TipoDispositivo;

// Estado del dispositivo
typedef enum {
    DISP_DISPONIBLE,
    DISP_BLOQUEADO,
    DISP_USADO,
    DISP_FALLADO
} EstadoDispositivo;

// Estructura dispositivo
typedef struct {
    TipoDispositivo tipo;
    EstadoDispositivo estado;
} Dispositivo;

// Estructura jugador mínima esperada
typedef struct {
    Posicion pos;
    Dispositivo dispositivos[3];
    int puedeMover;                // usado por HYDRUS
    int saltoExtra;                // usado por PHALANX
} Jugador;

// Inicializacion
void inicializarDispositivos(Dispositivo d[], TipoDispositivo seleccionados[]);

// Activacióo general
int activarDispositivo(
    Dispositivo *d,
    Jugador *jugador,
    Jugador *oponente,
    Mapa *mapa
);

// Efectos individuales
void efectoGaius(Mapa *mapa);
void efectoQuadratus(Jugador *oponente);
void efectoHydrus(Jugador *oponente);
void efectoPhalanx(Jugador *jugador);
void efectoArgus(Jugador *jugador, Jugador *oponente);

#endif
