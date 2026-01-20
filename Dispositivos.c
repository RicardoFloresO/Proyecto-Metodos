#include "dispositivos.h"
#include <stdio.h>
#include <stdlib.h>

// Inicializacion

void inicializarDispositivos(Dispositivo d[], TipoDispositivo seleccionados[]) {
    for (int i = 0; i < 3; i++) {
        d[i].tipo = seleccionados[i];
        d[i].estado = DISP_DISPONIBLE;
    }
}

// Activacion general

int activarDispositivo(
    Dispositivo *d,
    Jugador *jugador,
    Jugador *oponente,
    Mapa *mapa
) {
    if (d->estado != DISP_DISPONIBLE)
        return 0;

    // Simulacion mini-juego (50% exito por ahora)
    int exito = rand() % 2;

    if (!exito) {
        d->estado = DISP_FALLADO;
        return 0;
    }

    switch (d->tipo) {
        case GAIUS:
            efectoGaius(mapa);
            break;
        case QUADRATUS:
            efectoQuadratus(oponente);
            break;
        case HYDRUS:
            efectoHydrus(oponente);
            break;
        case PHALANX:
            efectoPhalanx(jugador);
            break;
        case ARGUS:
            efectoArgus(jugador, oponente);
            break;
        default:
            break;
    }

    d->estado = DISP_USADO;
    return 1;
}

// Efectos

void efectoGaius(Mapa *mapa) {
    for (int i = 0; i < 3; i++) {
        int x = rand() % mapa->filas;
        int y = rand() % mapa->columnas;
        int delta = (rand() % 2) ? 1 : -1;

        if (mapa->altura[x][y] + delta >= mapa->alturaMin &&
            mapa->altura[x][y] + delta <= mapa->alturaMax) {
            mapa->altura[x][y] += delta;
        }
    }
}

void efectoQuadratus(Jugador *oponente) {
    int idx = rand() % 3;
    if (oponente->dispositivos[idx].estado == DISP_DISPONIBLE)
        oponente->dispositivos[idx].estado = DISP_BLOQUEADO;
}

void efectoHydrus(Jugador *oponente) {
    oponente->puedeMover = 0;
}

void efectoPhalanx(Jugador *jugador) {
    jugador->saltoExtra = 1;
}

void efectoArgus(Jugador *jugador, Jugador *oponente) {
    int i = rand() % 3;
    int j = rand() % 3;

    Dispositivo temp = jugador->dispositivos[i];
    jugador->dispositivos[i] = oponente->dispositivos[j];
    oponente->dispositivos[j] = temp;
}

