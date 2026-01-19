#ifndef TURNOS_H
#define TURNOS_H

#include <stdbool.h>
#include <stddef.h>

/* Estados que puede devolver el turno */
typedef enum {
    TURNO_SIGUE = 0,
    TURNO_TERMINO = 1,
    JUEGO_TERMINO = 2
} TurnoEstado;

/* Acciones posibles en un turno */
typedef enum {
    ACCION_NINGUNA = 0,
    ACCION_MOVER = 1,
    ACCION_USAR_DISPOSITIVO = 2,
    ACCION_RENDIRSE = 3
} TurnoAccion;

/* Comando (acción + datos) */
typedef struct {
    TurnoAccion tipo;
    int x_dest;
    int y_dest;
    int dispositivo_id;
} TurnoComando;

/* Estado del turno actual */
typedef struct {
    int jugador_id;
    int acciones_consumidas;
    bool turno_finalizado;
} TurnoActual;

/* Callbacks hacia la lógica del juego */
typedef struct {
    bool (*intentar_mover)(
        void *juego,
        int jugador_id,
        int x_dest,
        int y_dest,
        char *err_msg,
        size_t err_cap
    );

    bool (*intentar_usar_dispositivo)(
        void *juego,
        int jugador_id,
        int dispositivo_id,
        char *err_msg,
        size_t err_cap
    );

    bool (*juego_terminado)(void *juego);

    void (*log_evento)(
        void *juego,
        int jugador_id,
        const char *evento
    );
} TurnoDevolucion;

void turnos_iniciar_turno(TurnoActual *turno, int jugador_id);

TurnoEstado turnos_aplicar_comando(
    TurnoActual *turno,
    void *juego,
    const TurnoDevolucion *dev,
    const TurnoComando *cmd,
    char *err_msg,
    size_t err_cap
);

#endif /* TURNOS_H */
